#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <algorithm> 

using namespace std;

struct truba
{
	int id;
	double dlina;
	double diametr;
	bool remont;
};

struct KS
{
	int id;
	string name;
	int kolich;
	int kolichrab;
	double ifect;
};

HANDLE myHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void PrintTitle(string textTitle)
{
	SetConsoleTextAttribute(myHandle, FOREGROUND_RED);
	cout << textTitle << endl;
};

void print_menu()
{
	system("cls");
	cout << "1) Dobavit trubu" << endl
		<< "2) Dobavit KS" << endl
		<< "3) Prosmotr vseh object" << endl
		<< "4) Redactor trubi" << endl
		<< "5) Redactor KS" << endl
		<< "6) Sahranit" << endl
		<< "7) Zagruzit" << endl
		<< "8) Vihod" << endl;
}

double GetValue(int min_value, int max_value, string str)
{
	double value;
	for (;;) 
	{
		cout << " Vvidide " + str + " (ot " << min_value << " do " << max_value << "): ";
		if (!(cin >> value) || cin.get() != '\n')
		{
			cout << "Cho ti vvel!" << endl;
			cin.clear();
			cin.ignore(5000, '\n');
		}
		else if ((min_value <= value) && (value <= max_value)) 
		return value;
	}
}


bool Getrep()
{
	string vibor;
	while (true)
	{
		vibor = _getch();
		if (vibor == "y")
		{
			return true;
		}
		else if (vibor == "n")
		{
			return false;
		}
	}
}


bool Probel(string str)
{
	int i = 0;
	while (i != size(str))
	{
		if (str[i] != ' ')
			return true;
		++i;
	}
	return false;
};

string getname()
{
	string nameKS;
	while (true)
	{
		getline(cin, nameKS);
		if (nameKS != "" && Probel(nameKS) && size(nameKS) <= 10)
		return nameKS;
	}

};

truba newtruba(int id)
{ 
	    truba z;
		z.id = id;
		z.dlina = GetValue(400,1000, "dlina");
		z.diametr = GetValue(500,1200, "diametr");
		z.remont = Getrep();
		return z;
}

void ramochka(char c, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		cout << c;
	}
	cout << endl;
};

void tablichatruba(vector <truba>& vectortrubs)
{
	ramochka('/', 131);
	cout << "|" << setw(20) << "Id" << setw(30) << "Dlina" << setw(30) << "Diametr" << setw(30) << "Remont" << setw(20) << "|" << endl;
	ramochka('/', 131);
	for (size_t i = 0; i < vectortrubs.size(); i++)
	{
		cout << "|" << setw(20) << vectortrubs[i].id << setw(30) << vectortrubs[i].dlina << setw(30) << vectortrubs[i].diametr << setw(30) << (vectortrubs[i].remont == true ? "true" : "false") << setw(20) << "|" << endl;
	}
	ramochka('/', 131);
};


void tablichaKS(vector <KS>& vectorKSs)
{
	ramochka('/', 172);
	cout << "|" << setw(20) << "Id" << setw(30) << "Name" << setw(30) << "ObchieKolichestvo" << setw(30) << "ObchieKolichestvoRabota" << setw(30) << "Iffectivnost" << setw(30) << "|" << endl;
	ramochka('/', 172);
	for (size_t i = 0; i < vectorKSs.size(); i++)
	{
		cout << "|" << setw(20) << vectorKSs[i].id << setw(30) << vectorKSs[i].name << setw(30) << vectorKSs[i].kolich << setw(30) << vectorKSs[i].kolichrab << setw(30) << vectorKSs[i].ifect << setw(30) << "|" << endl;
	}
	ramochka('/', 172);
};

KS newKS(int id)
{
	KS f;
	f.id = id;
	f.name = getname();
	f.kolich = GetValue(1,20,"VsegoKS");
	f.kolichrab = GetValue(0,20,"VsegoKSrabotat");
	f.ifect = GetValue(1,100,"Iffect");
	return f;
}

int get_var(int count) 
{
	int variant;
	std::cin >> variant;
	
	while (variant < 1) 
	{
		std::cout<<"Necorektno. Vvidite drugoe chislo: ";
		std::cin >> variant;
	}

	return variant;
}

void Redactortrub(vector <truba>& vectortrubs)
{
	size_t tipid;
	bool query;
	cout << "Всего добавлено труб: " << size(vectortrubs) << endl;
	if (size(vectortrubs) == 0)
	{
		cout << "Oshipka, net trubi"<<endl;
		ProverEnter();
		return;
	}
	while (true)
	{
		tipid = GetValue(1, size(vectortrubs), "Id");
		cout << "Iznochalno:" << (vectortrubs[tipid - 1].remont == true ? "V remonte" : "Ne v remonte") << endl;
		vectortrubs[tipid - 1].remont = Getrep();
		query = Getrep();
		if (query != true)
			break;
	}
};

void RedactorKS(vector <KS>& vectorKSs)
{
	size_t tipid;
	bool pravda;
	cout << "Всего добавлено компрессорных станций: " << size(vectorKSs) << endl;
	if (size(vectorKSs) == 0)
	{
		cout << "Oshipka, net stanchii";
		ProverEnter();
		return;
	}
		while (true)
		{
			tipid = GetValue(1,size(vectorKSs),"Id");
			cout << "Obchie kolichestvo KS " << vectorKSs[tipid - 1].kolich << endl;
			cout << "Obchie kolichestvo KS rabotat: " << vectorKSs[tipid - 1].kolichrab << endl;
			vectorKSs[tipid - 1].kolichrab = GetValue(0, vectorKSs[tipid - 1].kolichrab,"");
			pravda = Getrep();
			if (pravda != true)
				break;
		}
	
};

void Savef(vector <truba>& vectortrubs, vector <KS>& vectorKSs)
{
	ofstream fout;
	string path = "data.txt";
	fout.open(path);
	size_t percent = 0;
	if (fout.is_open())
	{
		for (size_t i = 0; i < size(vectortrubs); i++)
		{
			fout << vectortrubs[i].id << endl
				<< vectortrubs[i].dlina << endl
				<< vectortrubs[i].diametr << endl
				<< vectortrubs[i].remont << endl;
		}
		for (size_t i = 0; i < size(vectorKSs); i++)
		{
			fout << vectorKSs[i].id << endl
				<< vectorKSs[i].name << endl
				<< vectorKSs[i].kolich << endl
				<< vectorKSs[i].kolichrab << endl
				<< vectorKSs[i].ifect << endl;
		}
		while (percent <= 100)
		{
			cout << "\t\t\t\t" << "    Progres " << percent++ << "%";
			cout << '\r';
			Sleep(20);
		}
	}
};

void Zagruzka(truba pipeline, KS station)
{
	ifstream inf("data.txt");

	if (!inf)
	{
		cerr << "Nu chto-to slomno" << endl;
		exit(1);
	}
	else if (inf.peek() == -1)
	{
		cout << "\ndata.txt pust\n";
	}
	else
	{
		inf >> pipeline.id;
		inf >> pipeline.dlina;
		inf >> pipeline.diametr;
		inf >> pipeline.remont;
		inf >> station.id;
		getline(inf, station.name);
		inf.ignore(5000, '\n');
		inf >> station.kolich;
		inf >> station.kolichrab;
		inf >> station.ifect;
	}
}

void ProverEnter()
{
	char c;
	cout << "\t\t\t\t\tVihodim otsuda cherez Enter";
	c = _getch();
	if (c == 13) 
	exit(0);
};

int menu()
{
	char variant;
	SetConsoleTitle(L"Laba №1, Safin Shamil, AA-20-05");
	print_menu();
	vector <truba> vectortruba;
	vector <KS> vectorKS;
	variant = _getch();
	while (true)
	{
		switch (variant)
		{
		case '1':
		{
			system("CLS");
			PrintTitle("\t\t\t\tTRUBA");
			truba NewTruba = newtruba(size(vectortruba) + 1);
			vectortruba.push_back(NewTruba);
			break;
		}

		case '2':
		{
			system("CLS");
			PrintTitle("\t\t\t\tKS");
			KS NewComSta = newKS(size(vectorKS) + 1);
			vectorKS.push_back(NewComSta);
			break;
		}
		case '3':
		{
			system("ClS");
			PrintTitle("\n\t\t\t\tTabliza trubi\n");
			tablichatruba(vectortruba);
			PrintTitle("\n\n\n\n\t\t\t\t\t\t\t\tTabliza KS\n");
			tablichaKS(vectorKS);
			ProverEnter();
			break;
		}
		case '4':
		{
			system("CLS");
			PrintTitle("\n\t\t\t\tRedactor Trub\n");
			Redactortrub(vectortruba);
			break;
		}
		case'5':
		{
			system("CLS");
			PrintTitle("\n\t\t\t\tRedactor KS\n");
			RedactorKS(vectorKS);
			break;
		}
		case '6':
		{
			system("CLS");
			PrintTitle("\n\t\t\t\tSave Danie\n");
			Savef(vectortruba, vectorKS);
			break;
		}

		case '7':
		{
			system("CLS");
			Zagruzka(newtruba(size(vectortruba) + 1), newKS(size(vectorKS) + 1));
			break;
		}
		case '0':
		{
			system("CLS");
			PrintTitle("\n\tPoka Poka");
			Sleep(3000);
			return 0;
			break;
		}
		}
		system("CLS");
	}
	return 0;
};