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
	std::cout << "Всего добавлено труб: " << pipeCollection.size() << std::endl
		<< "Id доступные для редактирования: ";
	for (const auto& el : pipeCollection)
		std::cout << el.first << "  ";
	std::cout << std::endl;
	if (pipeCollection.empty())
	{
		std::cout << "Вы не добавили ни одной трубы, редактирование недоступно!" << std::endl;
		return;

	}
	while (true)
	{
		changeId = work_with_user::get_int_value(1, Pipe::Max_ID, "id of Pipe");
		if (pipeCollection.find(changeId) != pipeCollection.end())
		{
			std::cout << "Изначальное состояние трубы: "
				<< (pipeCollection[changeId].under_repair ? "в ремонте" : "не в ремонте")
				<< std::endl;
			pipeCollection[changeId].switch_repair();
		}
		else
			std::cout << "По указанному id не найдено ни одной трубы!!!!" << std::endl;
		query = work_with_user::get_boolean_value("\n\nПродолжаем редактирование компрессорных станций? (y/n)\n");
		if (query != true)
			break;
	}
}

void PipeCollection::PrintPipe()
{
	if (pipeCollection.empty())
	{
		cout << "\nУ вас нет труб\n";
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
	query = work_with_user::get_boolean_value("Введите состояние трубы для фильтра: у - в ремонте, n - не в ремонте");
	for (const auto& el : pipeCollection)
		if (el.second.under_repair == query)
			vectorIdForFilter.push_back(el.first);
}

void PipeCollection::PrintFilterPipe()
{
	cout << "\nФильтрованные трубы инфо:";
	for (const auto& id : vectorIdForFilter)
	{
		cout << pipeCollection[id];
	}
}


void PipeCollection::DeletePipe()
{
	if (pipeCollection.empty())
	{
		cout << "Вы не добавили ни одной трубы, удаление недоступно!";
		return;
	}
	bool query;
	query = work_with_user::get_boolean_value("\nВведите 'y', если хотите произвести удаление по одной трубе, и 'n', если хотите произвести пакетное удаление по фильтру:\n");
	if (query)  // Удаление по одной трубе
	{
		std::cout << "\n\nВсего Труб: " << pipeCollection.size() << std::endl
			<< "Id доступные для удаления: ";
		for (const auto& el : pipeCollection)
			std::cout << el.first << "  ";
		std::set<size_t> setIdForDelete = work_with_user::GetMultipleNumericValues<size_t>(
			"\nВведите через пробел id труб, которые хотели бы удалить: ",
			"\nОшибка, вы ввели недопустимый формат, повторите ввод заново!");
		for (const auto id : setIdForDelete)
		{
			if (pipeCollection.find(id) != pipeCollection.end())
			{
				pipeCollection.erase(id);
				cout << "Труба с id = " + std::to_string(id) + " была удалена!\n";
			}
			else
				cout << "Труба с id = " + std::to_string(id) + " не была найдена в списке всех труб!\n";
		}
	}
	else // Пакетное удаление
	{
		FilterPipe();
		if (!vectorIdForFilter.empty())
		{
			std::cout << "\n\nТрубы, полученные после фильтрации:" << std::endl;
			PrintFilterPipe();
			query = work_with_user::get_boolean_value("\nВведите 'y', если хотите удалить все отфильтрованные трубы, и 'n', если часть из них:\n");
			if (query) // Удалить все отфильтрованные трубы
			{
				for (const auto& i : vectorIdForFilter)
					pipeCollection.erase(i);
				cout << "\nТрубы были успешно удалены!";
			}
			else // Удалить часть отфильтрованных труб
			{
				std::set<size_t> setIdForDelete = work_with_user::GetMultipleNumericValues<size_t>(
					"\nВведите через пробел id труб, которые хотели бы удалить: ",
					"\nОшибка, вы ввели недопустимый формат, повторите ввод заново!");
				for (auto id : setIdForDelete)
				{
					auto it = std::find(vectorIdForFilter.begin(), vectorIdForFilter.end(), id);
					if (it != vectorIdForFilter.end())
					{
						pipeCollection.erase(id);
						cout << "Труба с id = " + std::to_string(id) + " была удалена!\n";
					}
					else
						cout << "Труба с id = " + std::to_string(id) + " не была найдена в списке отфильтрованных труб!\n";
				}
				}
			vectorIdForFilter.clear();
		}
		else
		cout << "\nПо вашему фильтру не было найдено ни одной трубы!";
	}
	std::cout << std::endl;
	system("pause");
}


void PipeCollection::BatchChangePipe()
{
	if (pipeCollection.empty())
	{
		cout << "\nВы не добавили ни одной трубы, пакетное редактирование недоступно!";
		return;
	}
	bool query;
	bool repairStatus;
	query = work_with_user::get_boolean_value("\nВведите 'y', если хотите редактировать все трубы, и 'n', если только определённое подмножество:\n");
	if (!query) // Пакетное редактирование
	{
		FilterPipe();
		if (!vectorIdForFilter.empty())
		{
			PrintFilterPipe();
			query = work_with_user::get_boolean_value("\nВведите 'y', если хотите отредактировать все отфильтрованные трубы, и 'n', если хотите отредактировать только часть :\n");
			if (!query) // Редактировать все отфильтрованные трубы
			{
				std::set<size_t> setIdForChange = work_with_user::GetMultipleNumericValues<size_t>(
					"\nВведите через пробел id труб, которые хотели бы отредактировать: ",
					"\nОшибка, вы ввели недопустимый формат, повторите ввод заново!");
				repairStatus = work_with_user::get_boolean_value("\n\nУкажите новое состояние для выбранных труб, если в ремонте, то введите 'y', если не в ремонте, то 'n': ");
				for (const auto id : setIdForChange)
				{
					auto it = std::find(vectorIdForFilter.begin(), vectorIdForFilter.end(), id);
					if (it != vectorIdForFilter.end())
					{
						pipeCollection[id].under_repair = repairStatus;
						cout << "Труба с id = " + std::to_string(id) + " была отредактирована!\n";
					}
					else
						cout << "Труба с id = " + std::to_string(id) + " не была найдена в списке отфильтрованных труб\n";
				}
			}
			else // Отредактировать часть отфильтрованных труб
			{
				repairStatus = work_with_user::get_boolean_value("\n\nУкажите новое состояние для выбранных труб, если в ремонте, то введите 'y', если не в ремонте, то 'n': ");
				for (const auto& i : vectorIdForFilter)
					pipeCollection[i].under_repair = repairStatus;
				cout << "\nТрубы отредактированы!";
			}
		}
		else
			cout << "\nПо вашему фильтру не было найдено ни одной трубы!";
		vectorIdForFilter.clear();
	}
	else // Редактирование всех труб
	{
		PrintPipe();
		repairStatus = work_with_user::get_boolean_value("\n\nУкажите новое состояние для выбранных труб, если в ремонте, то введите 'y', если не в ремонте, то 'n': ");
		for (auto& el : pipeCollection)
			el.second.under_repair = repairStatus;
		cout << "\nТрубы отредактированы!";
	}
	system("pause");
}
