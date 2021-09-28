#include <iostream>
#include <string>

struct truba
{
	double id;
	double dlina;
	double diametr;
	bool remont;
};

struct KS
{
	double id;
	std::string name;
	double kolich;
	double kolichrab;
	double ifect;
};
int main()
{
	truba z;
	std::cout << "Id: ";
	std::cin >> z.id;
	std::cout << "Dlina: ";
	std::cin >> z.dlina;
	std::cout << "Diametr: ";
	std::cin >> z.diametr;
	std::cout << "Состояние: ";
	std::cin >> z.remont;
}

int main2()
{
	KS z;
	std::cout << "Id: ";
	std::cin >> z.id;
	std::cout << "Name: ";
	std::cin >> z.name;
	std::cout << "Общее количество цехов: ";
	std::cin >> z.kolich;
	std::cout << "Общее количество рабочующих цехов: ";
	std::cin >> z.kolichrab;
	std::cout << "Эффективность: ";
	std::cin >> z.ifect;
}
