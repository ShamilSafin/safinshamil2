#include "CSCollection.h"
#include "work_with_user.h"
#include <iomanip>



//size_t CS::Max_ID = 0;

void CSCollection::AddCS()
{
	CS compressorStation;
	csCollection.emplace(compressorStation.id, compressorStation);

}

void CSCollection::ChangeCS()
{
	size_t changeId;
	bool query;
	std::cout << "����� ��������� ������������� �������: " << csCollection.size() << std::endl
		<< "Id ��������� ��� ��������������: ";
	for (const auto& el : csCollection)
		std::cout << el.first << "  ";
	std::cout << std::endl;
	if (csCollection.empty())
	{
		std::cout << "�� �� �������� �� ����� ������������� �������, �������������� ����������!" << std::endl;
		return;
	}
	while (true)
	{
		changeId = work_with_user::get_int_value(1, CS::Max_ID, "id of compressor station");
		if (csCollection.find(changeId) != csCollection.end())
		{
			std::cout << "���������� ����� � ������������� �������: " << csCollection[changeId].count_of_shops << std::endl;
			std::cout << "���������� ����� � ������ � ������ ������������� �������: " << csCollection[changeId].count_of_working_shops << std::endl;
			csCollection[changeId].change_count_of_working_shops();
		}
		query = work_with_user::get_boolean_value("\n\n���������� �������������� ������������� �������? (y/n)\n");
		if (query != true)
			break;
	}
}

void CSCollection::PrintCS()
{
	if (csCollection.empty())
	{
		cout << "\n� ��� ��� �������\n\n";
	}
	else
	{
		cout << "\n�� ����:";
		for (auto item : csCollection)
		{
			cout << item.second;
		}
	}
}


void CSCollection::PrintFilterCS()
{
	cout << "\n������������� �� ����:";
	for (const auto& id : vectorIdForFilter)
	{
		cout << csCollection[id];
	}
}

void CSCollection::FilterCS()
{
	std::cout << "\n\n�������� ����� ���� ��� ����������:" << std::endl
		<< "1. ������������� �� ��������" << std::endl
		<< "2. ������������� �� �������� ����������������� �����" << std::endl
		<< "3. ��������� ��� �������" << std::endl;
	while (true)
	{
		std::cout << "\n������� �������: ";
		switch (work_with_user::get_int_value(1, 3, "number"))
		{
		case 1:
		{
			std::string nameCS;
			nameCS = work_with_user::get_name_for_station();
			for (const auto& el : csCollection)
				if (el.second.name == nameCS)
					vectorIdForFilter.push_back(el.first);
			return;
		}
		case 2:
		{
			size_t lowPercent, upPercent, percent;
			lowPercent = work_with_user::get_int_value(0, 99, "\n������� ������ ������� ������� �������� ���������������� ����� � �� (����� ����� �� 0 �� 100");
			upPercent = work_with_user::get_int_value(lowPercent, 100, "\n������� ������� ������� ������� �������� ���������������� ����� � �� (����� ����� �� ������ ������� �� 100");
			for (const auto& el : csCollection)
			{
				percent = static_cast<size_t>(round((static_cast<double>(el.second.count_of_shops) - el.second.count_of_working_shops) / el.second.count_of_shops * 100));
				if (percent >= lowPercent && percent <= upPercent)
					vectorIdForFilter.push_back(el.first);
			}
			return;
		}
		case 3:
		{
			std::string nameCS;
			size_t lowPercent, upPercent, percent;
			nameCS = work_with_user::get_name_for_station();
			lowPercent = work_with_user::get_int_value(0, 99, "\n������� ������ ������� ������� �������� ���������������� ����� � �� (����� ����� �� 0 �� 100");
			upPercent = work_with_user::get_int_value(lowPercent, 100, "\n������� ������� ������� ������� �������� ���������������� ����� � �� (����� ����� �� ������ ������� �� 100");
			for (const auto& el : csCollection)
			{
				percent = static_cast<size_t>(round((static_cast<double>(el.second.count_of_shops) - el.second.count_of_working_shops) / el.second.count_of_shops * 100));
				if (el.second.name == nameCS && percent >= lowPercent && percent <= upPercent)
					vectorIdForFilter.push_back(el.first);
			}
			return;
		}
		default:
		{
			cout << "\n����� ������� ���� � ������, ���������� ����, ��������� ����\n";
			break;
		}
		}
	}
}

void CSCollection::DeleteCS()
{
	if (csCollection.empty())
	{
		cout << "\n�� �� �������� �� ���� ��, �������� ����������!\n";
		return;
	}
	bool query;
	query = work_with_user::get_boolean_value("\n������� 'y', ���� ������ ���������� �������� �� ����� ��, � 'n', ���� ������ ���������� �������� �������� �� �������:\n");
	if (query) 
	{
		std::cout << "\n\n����� ��: " << csCollection.size() << std::endl
			<< "Id ��������� ��� ��������: ";
		for (const auto& el : csCollection)
			std::cout << el.first << "  ";
		std::set<size_t> setIdForDelete = work_with_user::GetMultipleNumericValues<size_t>(
			"\n������� ����� ������ id ��, ������� ������ �� �������: ",
			"\n������, �� ����� ������������ ������, ��������� ���� ������!");
		for (const auto id : setIdForDelete)
		{
			if (csCollection.find(id) != csCollection.end())
			{
				csCollection.erase(id);
				cout << "������������� ������� � id = " + std::to_string(id) + " ���� �������!\n";
			}
			else
				cout << "������������� ������� � id = " + std::to_string(id) + " �� ���� ������� � ������ ���� ��!\n";
		}
	}
	else 
	{
		FilterCS();
		if (!vectorIdForFilter.empty())
		{
			std::cout << "\n\n��, ���������� ����� ����������: " << std::endl;
			PrintFilterCS();
			query = work_with_user::get_boolean_value("\n������� 'y', ���� ������ ������� ��� ��������������� ��, � 'n', ���� ������ ������� ����� �� ���:\n");
			if (query) 
			{
				for (const auto i : vectorIdForFilter)
					csCollection.erase(i);
				cout << "\n\n�� ������� �������!";
			}
			else 
			{
				std::set<size_t> setIdForDelete = work_with_user::GetMultipleNumericValues<size_t>(
					"\n������� ����� ������ id ��, ������� ������ �� �������: ",
					"\n������, �� ����� ������������ ������, ��������� ���� ������!");
				for (auto id : setIdForDelete)
				{
					auto it = std::find(vectorIdForFilter.begin(), vectorIdForFilter.end(), id);
					if (it != vectorIdForFilter.end())
					{
						csCollection.erase(id);
						cout << "������������� ������� � id = " + std::to_string(id) + " ���� �������!\n";
					}
					else
						cout << "������������� ������� � id = " + std::to_string(id) + " �� ���� ������� � ������ ���� ��!\n";
				}
			}
			vectorIdForFilter.clear();
		}
		else
			cout << "\n�� ������ ������� �� ���� ������� �� ����� ��!";
	}
	std::cout << std::endl;
	system("pause");
}

void CSCollection::BatchChangeCS()
{
	if (csCollection.empty())
	{
		cout << "\n�� �� �������� �� ����� ��, �������� �������������� ����������!\n";
		return;
	}
	bool query;
	query = work_with_user::get_boolean_value("\n������� 'y', ���� ������ ������������� ��� ��, � 'n', ���� ������ ����������� ������������ :\n");
	if (!query) // �������������� ����� ��
	{
		FilterCS();
		if (!vectorIdForFilter.empty())
		{
			PrintFilterCS();
			query = work_with_user::get_boolean_value("\n������� 'y', ���� ������ ��������������� ��� ��������������� ��, � 'n', ���� ������ ��������������� ������ ����� :\n");
			if (query) // �������������� ���� ��������������� ��
			{
				for (const auto& i : vectorIdForFilter)
				{
					std::cout << "\n\n������������� ������� ��� id " << csCollection[i].id << " ����� ����� ���������� �����: " << csCollection[i].count_of_shops << std::endl
						<< "���������� ����� � ������: " << csCollection[i].count_of_working_shops << std::endl;
					csCollection[i].count_of_working_shops = work_with_user::get_int_value(0, csCollection[i].count_of_shops, "������� ����� ���������� ����� � ������ ��� ������ �� (��� �� ������ ��������� ����� ���������� �����): ");
						cout << "������������� ������� � id = " + std::to_string(i) + " ���� ���������������!\n";
				}
				cout << "�� ���������������!";
			}
			else // �������������� �� �� id ����� ���������������
			{
				std::set<size_t> setIdForChange = work_with_user::GetMultipleNumericValues<size_t>(
					"\n������� ����� ������ id ��, ������� ������ �� ���������������: ",
					"\n������, �� ����� ������������ ������, ��������� ���� ������!");
				for (const auto id : setIdForChange)
				{
					auto it = std::find(vectorIdForFilter.begin(), vectorIdForFilter.end(), id);
					if (it != vectorIdForFilter.end())
					{
						std::cout << "\n\n������������� ������� ��� id " << csCollection[id].id << " ����� ����� ���������� �����: " << csCollection[id].count_of_shops << std::endl
							<< "���������� ����� � ������: " << csCollection[id].count_of_working_shops << std::endl;
						csCollection[id].count_of_working_shops = work_with_user::get_int_value(0, csCollection[id].count_of_shops, "������� ����� ���������� ����� � ������ ��� ������ �� (��� �� ������ ��������� ����� ���������� �����): ");
						cout << "\n������������� ������� � id = " + std::to_string(id) + " ���� ���������������!\n";
					}
					else
						cout << "\n������������� ������� � id = " + std::to_string(id) + " �� ���� ������� � ������ ��������������� ��!\n";
				}
			}
			vectorIdForFilter.clear();
		}
		else
			cout << "\n�� ������ ������� �� ���� ������� �� ����� �������!";
	}
	else // �������������� ���� ��
	{
		PrintCS();
		for (auto& el : csCollection)
		{
			std::cout << "\n\n������������� ������� ��� id " << el.first << " ����� ����� ���������� �����: " << el.second.count_of_shops << std::endl
				<< "���������� ����� � ������: " << el.second.count_of_working_shops << std::endl;
			el.second.count_of_working_shops = work_with_user::get_int_value(0, el.second.count_of_shops, "������� ����� ���������� ����� � ������ ��� ������ �� (��� �� ������ ��������� ����� ���������� �����): ");
			cout << "������������� ������� � id - " + std::to_string(el.first) + " �� ���� ������� � ������ ��������������� ��";
		}
		cout << "\n�� ���������������!";
	}
	vectorIdForFilter.clear();
	system("pause");
}
