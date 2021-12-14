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
	std::cout << "Всего добавлено компрессорных станций: " << csCollection.size() << std::endl
		<< "Id доступные для редактирования: ";
	for (const auto& el : csCollection)
		std::cout << el.first << "  ";
	std::cout << std::endl;
	if (csCollection.empty())
	{
		std::cout << "Вы не добавили ни одной компрессорной станции, редактирование недоступно!" << std::endl;
		return;
	}
	while (true)
	{
		changeId = work_with_user::get_int_value(1, CS::Max_ID, "id of compressor station");
		if (csCollection.find(changeId) != csCollection.end())
		{
			std::cout << "Количество цехов у компрессорной станции: " << csCollection[changeId].count_of_shops << std::endl;
			std::cout << "Количество цехов в работе у данной компрессорной станции: " << csCollection[changeId].count_of_working_shops << std::endl;
			csCollection[changeId].change_count_of_working_shops();
		}
		query = work_with_user::get_boolean_value("\n\nПродолжаем редактирование компрессорных станций? (y/n)\n");
		if (query != true)
			break;
	}
}

void CSCollection::PrintCS()
{
	if (csCollection.empty())
	{
		cout << "\nУ вас нет станций\n\n";
	}
	else
	{
		cout << "\nКС инфо:";
		for (auto item : csCollection)
		{
			cout << item.second;
		}
	}
}


void CSCollection::PrintFilterCS()
{
	cout << "\nФильтрованные КС инфо:";
	for (const auto& id : vectorIdForFilter)
	{
		cout << csCollection[id];
	}
}

void CSCollection::FilterCS()
{
	std::cout << "\n\nВыберите пункт меню для фильтрации:" << std::endl
		<< "1. Отфильтровать по названию" << std::endl
		<< "2. Отфильтровать по проценту незадействованных цехов" << std::endl
		<< "3. Применить оба фильтра" << std::endl;
	while (true)
	{
		std::cout << "\nВведите команду: ";
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
			lowPercent = work_with_user::get_int_value(0, 99, "\nВведите нижнюю границу фильтра процента незадейстованных цехов у КС (число целое от 0 до 100");
			upPercent = work_with_user::get_int_value(lowPercent, 100, "\nВведите верхнюю границу фильтра процента незадейстованных цехов у КС (число целое от нижней границы до 100");
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
			lowPercent = work_with_user::get_int_value(0, 99, "\nВведите нижнюю границу фильтра процента незадейстованных цехов у КС (число целое от 0 до 100");
			upPercent = work_with_user::get_int_value(lowPercent, 100, "\nВведите верхнюю границу фильтра процента незадейстованных цехов у КС (число целое от нижней границы до 100");
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
			cout << "\nТакой команды нету в списке, приведённом выше, повторите ввод\n";
			break;
		}
		}
	}
}

void CSCollection::DeleteCS()
{
	if (csCollection.empty())
	{
		cout << "\nВы не добавили ни одну КС, удаление недоступно!\n";
		return;
	}
	bool query;
	query = work_with_user::get_boolean_value("\nВведите 'y', если хотите произвести удаление по одной КС, и 'n', если хотите произвести пакетное удаление по фильтру:\n");
	if (query) 
	{
		std::cout << "\n\nВсего КС: " << csCollection.size() << std::endl
			<< "Id доступные для удаления: ";
		for (const auto& el : csCollection)
			std::cout << el.first << "  ";
		std::set<size_t> setIdForDelete = work_with_user::GetMultipleNumericValues<size_t>(
			"\nВведите через пробел id КС, которые хотели бы удалить: ",
			"\nОшибка, вы ввели недопустимый формат, повторите ввод заново!");
		for (const auto id : setIdForDelete)
		{
			if (csCollection.find(id) != csCollection.end())
			{
				csCollection.erase(id);
				cout << "Компрессорная станция с id = " + std::to_string(id) + " была удалена!\n";
			}
			else
				cout << "Компрессорная станция с id = " + std::to_string(id) + " не была найдена в списке всех КС!\n";
		}
	}
	else 
	{
		FilterCS();
		if (!vectorIdForFilter.empty())
		{
			std::cout << "\n\nКС, полученные после фильтрации: " << std::endl;
			PrintFilterCS();
			query = work_with_user::get_boolean_value("\nВведите 'y', если хотите удалить все отфильтрованные КС, и 'n', если хотите удалить часть из них:\n");
			if (query) 
			{
				for (const auto i : vectorIdForFilter)
					csCollection.erase(i);
				cout << "\n\nКС Успешно удалены!";
			}
			else 
			{
				std::set<size_t> setIdForDelete = work_with_user::GetMultipleNumericValues<size_t>(
					"\nВведите через пробел id КС, которые хотели бы удалить: ",
					"\nОшибка, вы ввели недопустимый формат, повторите ввод заново!");
				for (auto id : setIdForDelete)
				{
					auto it = std::find(vectorIdForFilter.begin(), vectorIdForFilter.end(), id);
					if (it != vectorIdForFilter.end())
					{
						csCollection.erase(id);
						cout << "Компрессорная станция с id = " + std::to_string(id) + " была удалена!\n";
					}
					else
						cout << "Компрессорная станция с id = " + std::to_string(id) + " не была найдена в списке всех КС!\n";
				}
			}
			vectorIdForFilter.clear();
		}
		else
			cout << "\nПо вашему фильтру не было найдено ни одной КС!";
	}
	std::cout << std::endl;
	system("pause");
}

void CSCollection::BatchChangeCS()
{
	if (csCollection.empty())
	{
		cout << "\nВы не добавили ни одной КС, пакетное редактирование недоступно!\n";
		return;
	}
	bool query;
	query = work_with_user::get_boolean_value("\nВведите 'y', если хотите редактировать все КС, и 'n', если только определённое подмножество :\n");
	if (!query) // Редактирование части КС
	{
		FilterCS();
		if (!vectorIdForFilter.empty())
		{
			PrintFilterCS();
			query = work_with_user::get_boolean_value("\nВведите 'y', если хотите отредактировать все отфильтрованные КС, и 'n', если хотите отредактировать только часть :\n");
			if (query) // Редактирование всех отфильтрованных КС
			{
				for (const auto& i : vectorIdForFilter)
				{
					std::cout << "\n\nКомпрессорная станция под id " << csCollection[i].id << " имеет общее количество цехов: " << csCollection[i].count_of_shops << std::endl
						<< "Количество цехов в работе: " << csCollection[i].count_of_working_shops << std::endl;
					csCollection[i].count_of_working_shops = work_with_user::get_int_value(0, csCollection[i].count_of_shops, "Введите новое количество цехов в работе для данной КС (оно не должно превышать общее количество цехов): ");
						cout << "Компрессорная станция с id = " + std::to_string(i) + " была отредактирована!\n";
				}
				cout << "КС отредактированы!";
			}
			else // Редактирование КС по id среди отфильтрованных
			{
				std::set<size_t> setIdForChange = work_with_user::GetMultipleNumericValues<size_t>(
					"\nВведите через пробел id КС, которые хотели бы отредактировать: ",
					"\nОшибка, вы ввели недопустимый формат, повторите ввод заново!");
				for (const auto id : setIdForChange)
				{
					auto it = std::find(vectorIdForFilter.begin(), vectorIdForFilter.end(), id);
					if (it != vectorIdForFilter.end())
					{
						std::cout << "\n\nКомпрессорная станция под id " << csCollection[id].id << " имеет общее количество цехов: " << csCollection[id].count_of_shops << std::endl
							<< "Количество цехов в работе: " << csCollection[id].count_of_working_shops << std::endl;
						csCollection[id].count_of_working_shops = work_with_user::get_int_value(0, csCollection[id].count_of_shops, "Введите новое количество цехов в работе для данной КС (оно не должно превышать общее количество цехов): ");
						cout << "\nКомпрессорная станция с id = " + std::to_string(id) + " была отредактирована!\n";
					}
					else
						cout << "\nКомпрессорная станция с id = " + std::to_string(id) + " не была найдена в списке отфильтрованных КС!\n";
				}
			}
			vectorIdForFilter.clear();
		}
		else
			cout << "\nПо вашему фильтру не было найдено ни одной станции!";
	}
	else // Редактирование всех КС
	{
		PrintCS();
		for (auto& el : csCollection)
		{
			std::cout << "\n\nКомпрессорная станция под id " << el.first << " имеет общее количество цехов: " << el.second.count_of_shops << std::endl
				<< "Количество цехов в работе: " << el.second.count_of_working_shops << std::endl;
			el.second.count_of_working_shops = work_with_user::get_int_value(0, el.second.count_of_shops, "Введите новое количество цехов в работе для данной КС (оно не должно превышать общее количество цехов): ");
			cout << "Компрессорная станция с id - " + std::to_string(el.first) + " не была найдена в списке отфильтрованных КС";
		}
		cout << "\nКС отредактированы!";
	}
	vectorIdForFilter.clear();
	system("pause");
}
