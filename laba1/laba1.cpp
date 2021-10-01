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
	std::cout << "Truba\nId: ";
	std::cin >> z.id;
	std::cout << "Dlina: ";
	std::cin >> z.dlina;
	std::cout << "Diametr: ";
	std::cin >> z.diametr;
	std::cout << "Sostoinie: ";
	std::cin >> z.remont;

	KS f;
	std::cout << "\nKS \nId: ";
	std::cin >> f.id;
	std::cout << "Name: ";
	std::cin >> f.name;
	std::cout << "Общее количество цехов: ";
	std::cin >> f.kolich;
	std::cout << "Общее количество рабочующих цехов: ";
	std::cin >> f.kolichrab;
	std::cout << "Эффективность: ";
	std::cin >> f.ifect;
	return 0;
}
void print_menu()
{
	system("cls");
	cout << "Dobavit trubu" << endl;
	cout << "Dobavit KS"<<endl;
	cout << "Prosmotr vseh object" << endl;
	cout << "Redactor trubi" << endl;
	cout << "Redactor KS" << endl;
	cout << "Sahranit" << endl;
	cout << "Zagruzit" << endl;
	cout << "Vihod" << endl;
}

int menu;
do {
	print_menu();
	variant = cin << a;
	switch (variant)
	{
	case 1:
		//
		break;
	case 2:
		//
		break;
	}
}
