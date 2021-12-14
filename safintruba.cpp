#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

int get_int_value(int min_value, int max_value, string str)
{
    int value;
    for (;;) {
        std::cout << "\nEnter " + str + " - integer (in " << min_value << " to " << max_value << "): ";
        if (!(cin >> value) || cin.get() != '\n')
        {
            cout << "Incorrect input!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if ((min_value <= value) && (value <= max_value)) return value;
    }
}

double get_double_value(int min_value, int max_value, string str)
{
    double value;
    while (true) {
        cout << "\nEnter " + str + " - double (in " << min_value << " to " << max_value << "): ";
        cin >> value;
        if (value >= min_value && value <= max_value && cin.get() == '\n') {
            return value;
        }
        cout << "Incorrect input!" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

bool get_boolean_value(string str)
{
    string response;
    while (true)
    {
        cout << "\nEnter " + str + " y or n: ";
        getline(cin, response);
        if (response == "y")
        {
            return true;
        }
        else if (response == "n")
        {
            return false;
        }
    }
}

struct Pipe
{
    int id;
    int diameter;
    double length;
    bool under_repair;
};

struct Compressor_Station
{
    int id;
    string name;
    int count_of_shops;
    int count_of_working_shops;
    double efficiency;
};

Compressor_Station CreateCS()
{
    Compressor_Station CS; 
    CS.id = 0;

    std::cout << "\nEnter name of Compressor Station: ";
    getline(cin, CS.name);

    CS.count_of_shops = get_int_value(0, 20, "count of shops");

    CS.count_of_working_shops = get_int_value(0, CS.count_of_shops, "count of working shops");

    CS.efficiency = get_double_value(0, 100, "efficiency");
    return CS;
}

Pipe CreatePipe()
{
    Pipe p;
    p.id = 0;
    p.diameter = get_int_value(100, 1420, "diameter");
    p.length = get_double_value(50, 1234, "length");
    p.under_repair = get_boolean_value("Pipeline under repair");
    return p;
}

void PrintPipe(const Pipe& p)
{
    cout << "\n\t\tPipe " << "\nid: " << p.id
        << "\nLength: " << p.length
        << "\ndiameter: " << p.diameter
        << "\nUnder repair: " << p.under_repair << endl << endl;
}

void PrintCS(const Compressor_Station& cs)
{
    cout << "\n\t\tCOMPRESSOR STATION " << "\nid: " << cs.id
        << "\nname: " << cs.name
        << "\nCount of shops: " << cs.count_of_shops
        << "\nCount of working shops: " << cs.count_of_working_shops
        << "\nEfficiency: " << cs.efficiency << endl;
}

void Save_objects(const Pipe pipeline, const Compressor_Station station)
{
    ofstream outf("save.txt");
    if (!outf)
    {
        cerr << "Uh oh, save.txt could not be opened for writing!" << endl;
        return;
    }
    if (pipeline.id != -1)
    {
        outf << "Pipeline" << endl
            << pipeline.id << endl
            << pipeline.diameter << endl
            << pipeline.length << endl
            << pipeline.under_repair << endl;
        cout << "\nSuccesfully saved pipe\n";
    }

    if (station.id != -1)
    {
        outf << "Station" << endl
            << station.id << endl
            << station.name << endl
            << station.count_of_shops << endl
            << station.count_of_working_shops << endl
            << station.efficiency << endl << endl;
        cout << "\nSuccesfully saved compressor station\n";
    }
    
    if (pipeline.id == -1 && station.id == -1)
    {
        cout << "\nNo objects to save\n";
    }
}

void Load_objects(Pipe& pipeline, Compressor_Station& station)
{
    ifstream inf("save.txt");
    if (!inf || inf.peek() == -1 )
    {
        cout << "\nNo enough save\n";
        return;
    }

    string title;
    while (getline(inf, title))
    {
        if (title == "Station")
        {
            inf >> station.id;
            inf.ignore(10000, '\n');
            getline(inf, station.name);
            inf >> station.count_of_shops;
            inf >> station.count_of_working_shops;
            inf >> station.efficiency;
            cout << "\nSuccesfully loaded station!\n";
        }
        else if (title == "Pipeline")
        {
            inf >> pipeline.id;
            inf >> pipeline.diameter;
            inf >> pipeline.length;
            inf >> pipeline.under_repair;
            cout << "\nSuccesfully loaded pipeline!\n";
        }
    }
}

void switch_repair(Pipe &pipeline)
{
    pipeline.under_repair = get_boolean_value("Pipeline under repair");
}

void Change_station(Compressor_Station &station)
{
    station.count_of_working_shops = get_int_value(0, station.count_of_shops, "count of working shops");
}

int main()
{
    Pipe p;
    p.id = -1;
    Compressor_Station cs;
    cs.id = -1;
    int iChoise = 0;
    while (1)
    {
        cout << "\n\tMENU" << endl;
        cout << "1 - Add pipeline" << endl;
        cout << "2 - Add CS" << endl;
        cout << "3 - Viewing all objects" << endl;
        cout << "4 - Edit a Pipe" << endl;
        cout << "5 - Edit a CS" << endl;
        cout << "6 - Save" << endl;
        cout << "7 - Load" << endl;
        cout << "0 - Exit" << endl;
        switch (get_int_value(0, 7, "number"))
        {
        case 1:
        {
            p = CreatePipe();
            break;
        }
        case 2:
        {
            cs = CreateCS();
            break;
        }
        case 3:
        {
            if (cs.id != -1)
            {
                PrintCS(cs);
            }
            if (p.id != -1)
            {
                PrintPipe(p);
            }
            if (p.id == -1 && cs.id == -1)
            {
                cout << "\nNo more objects :)\n";
            }
            break;
        }
        case 4:
        {
            if (p.id != -1)
            {
                switch_repair(p);
            }
            else
            {
                cout << "\nNo enough pipeline :)\n";
            }
            break;
        }
        case 5:
        {
            if (cs.id != -1)
            {
                Change_station(cs);
            }
            else
            {
                cout << "\nNo enough compressor station :)\n";
            }
            break;
        }
        case 6:
        {
            Save_objects(p, cs);
            break;
        }
        case 7:
        {
            Load_objects(p, cs);
            break;
        }
        case 0:
        {
            return 0;
        }
        }
    }
    return 0;
}