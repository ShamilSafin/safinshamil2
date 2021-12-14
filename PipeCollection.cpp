#include "PipeCollection.h"
#include "work_with_user.h"
#include <iomanip>

void PipeCollection::AddPipe()
{
	Pipe pipe;
	pipeCollection.emplace(pipe.id, pipe);
}

void PipeCollection::ChangePipe()
{
	size_t changeId;
	bool query;
	std::cout << "����� ��������� ����: " << pipeCollection.size() << std::endl
		<< "Id ��������� ��� ��������������: ";
	for (const auto& el : pipeCollection)
		std::cout << el.first << "  ";
	std::cout << std::endl;
	if (pipeCollection.empty())
	{
		std::cout << "�� �� �������� �� ����� �����, �������������� ����������!" << std::endl;
		return;

	}
	while (true)
	{
		changeId = work_with_user::get_int_value(1, Pipe::Max_ID, "id of Pipe");
		if (pipeCollection.find(changeId) != pipeCollection.end())
		{
			std::cout << "����������� ��������� �����: "
				<< (pipeCollection[changeId].under_repair ? "� �������" : "�� � �������")
				<< std::endl;
			pipeCollection[changeId].switch_repair();
		}
		else
			std::cout << "�� ���������� id �� ������� �� ����� �����!!!!" << std::endl;
		query = work_with_user::get_boolean_value("\n\n���������� �������������� ������������� �������? (y/n)\n");
		if (query != true)
			break;
	}
}

void PipeCollection::PrintPipe()
{
	if (pipeCollection.empty())
	{
		cout << "\n� ��� ��� ����\n";
	}
	else
	{
		cout << "\nPipe info:";
		for (auto item : pipeCollection)
		{
			cout << item.second;
		}
	}
}


void PipeCollection::FilterPipe()
{
	bool query;
	query = work_with_user::get_boolean_value("������� ��������� ����� ��� �������: � - � �������, n - �� � �������");
	for (const auto& el : pipeCollection)
		if (el.second.under_repair == query)
			vectorIdForFilter.push_back(el.first);
}

void PipeCollection::PrintFilterPipe()
{
	cout << "\n������������� ����� ����:";
	for (const auto& id : vectorIdForFilter)
	{
		cout << pipeCollection[id];
	}
}


void PipeCollection::DeletePipe()
{
	if (pipeCollection.empty())
	{
		cout << "�� �� �������� �� ����� �����, �������� ����������!";
		return;
	}
	bool query;
	query = work_with_user::get_boolean_value("\n������� 'y', ���� ������ ���������� �������� �� ����� �����, � 'n', ���� ������ ���������� �������� �������� �� �������:\n");
	if (query)  // �������� �� ����� �����
	{
		std::cout << "\n\n����� ����: " << pipeCollection.size() << std::endl
			<< "Id ��������� ��� ��������: ";
		for (const auto& el : pipeCollection)
			std::cout << el.first << "  ";
		std::set<size_t> setIdForDelete = work_with_user::GetMultipleNumericValues<size_t>(
			"\n������� ����� ������ id ����, ������� ������ �� �������: ",
			"\n������, �� ����� ������������ ������, ��������� ���� ������!");
		for (const auto id : setIdForDelete)
		{
			if (pipeCollection.find(id) != pipeCollection.end())
			{
				pipeCollection.erase(id);
				cout << "����� � id = " + std::to_string(id) + " ���� �������!\n";
			}
			else
				cout << "����� � id = " + std::to_string(id) + " �� ���� ������� � ������ ���� ����!\n";
		}
	}
	else // �������� ��������
	{
		FilterPipe();
		if (!vectorIdForFilter.empty())
		{
			std::cout << "\n\n�����, ���������� ����� ����������:" << std::endl;
			PrintFilterPipe();
			query = work_with_user::get_boolean_value("\n������� 'y', ���� ������ ������� ��� ��������������� �����, � 'n', ���� ����� �� ���:\n");
			if (query) // ������� ��� ��������������� �����
			{
				for (const auto& i : vectorIdForFilter)
					pipeCollection.erase(i);
				cout << "\n����� ���� ������� �������!";
			}
			else // ������� ����� ��������������� ����
			{
				std::set<size_t> setIdForDelete = work_with_user::GetMultipleNumericValues<size_t>(
					"\n������� ����� ������ id ����, ������� ������ �� �������: ",
					"\n������, �� ����� ������������ ������, ��������� ���� ������!");
				for (auto id : setIdForDelete)
				{
					auto it = std::find(vectorIdForFilter.begin(), vectorIdForFilter.end(), id);
					if (it != vectorIdForFilter.end())
					{
						pipeCollection.erase(id);
						cout << "����� � id = " + std::to_string(id) + " ���� �������!\n";
					}
					else
						cout << "����� � id = " + std::to_string(id) + " �� ���� ������� � ������ ��������������� ����!\n";
				}
				}
			vectorIdForFilter.clear();
		}
		else
		cout << "\n�� ������ ������� �� ���� ������� �� ����� �����!";
	}
	std::cout << std::endl;
	system("pause");
}


void PipeCollection::BatchChangePipe()
{
	if (pipeCollection.empty())
	{
		cout << "\n�� �� �������� �� ����� �����, �������� �������������� ����������!";
		return;
	}
	bool query;
	bool repairStatus;
	query = work_with_user::get_boolean_value("\n������� 'y', ���� ������ ������������� ��� �����, � 'n', ���� ������ ����������� ������������:\n");
	if (!query) // �������� ��������������
	{
		FilterPipe();
		if (!vectorIdForFilter.empty())
		{
			PrintFilterPipe();
			query = work_with_user::get_boolean_value("\n������� 'y', ���� ������ ��������������� ��� ��������������� �����, � 'n', ���� ������ ��������������� ������ ����� :\n");
			if (!query) // ������������� ��� ��������������� �����
			{
				std::set<size_t> setIdForChange = work_with_user::GetMultipleNumericValues<size_t>(
					"\n������� ����� ������ id ����, ������� ������ �� ���������������: ",
					"\n������, �� ����� ������������ ������, ��������� ���� ������!");
				repairStatus = work_with_user::get_boolean_value("\n\n������� ����� ��������� ��� ��������� ����, ���� � �������, �� ������� 'y', ���� �� � �������, �� 'n': ");
				for (const auto id : setIdForChange)
				{
					auto it = std::find(vectorIdForFilter.begin(), vectorIdForFilter.end(), id);
					if (it != vectorIdForFilter.end())
					{
						pipeCollection[id].under_repair = repairStatus;
						cout << "����� � id = " + std::to_string(id) + " ���� ���������������!\n";
					}
					else
						cout << "����� � id = " + std::to_string(id) + " �� ���� ������� � ������ ��������������� ����\n";
				}
			}
			else // ��������������� ����� ��������������� ����
			{
				repairStatus = work_with_user::get_boolean_value("\n\n������� ����� ��������� ��� ��������� ����, ���� � �������, �� ������� 'y', ���� �� � �������, �� 'n': ");
				for (const auto& i : vectorIdForFilter)
					pipeCollection[i].under_repair = repairStatus;
				cout << "\n����� ���������������!";
			}
		}
		else
			cout << "\n�� ������ ������� �� ���� ������� �� ����� �����!";
		vectorIdForFilter.clear();
	}
	else // �������������� ���� ����
	{
		PrintPipe();
		repairStatus = work_with_user::get_boolean_value("\n\n������� ����� ��������� ��� ��������� ����, ���� � �������, �� ������� 'y', ���� �� � �������, �� 'n': ");
		for (auto& el : pipeCollection)
			el.second.under_repair = repairStatus;
		cout << "\n����� ���������������!";
	}
	system("pause");
}
