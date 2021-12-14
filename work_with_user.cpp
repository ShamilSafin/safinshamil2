#include "work_with_user.h"
#include <iostream>
#include <string>

using namespace std; 

int work_with_user::get_int_value(int min_value, int max_value, string str)
{
    int value;
    for (;;) {
        std::cout << "\n" + str + " - integer (in " << min_value << " to " << max_value << "): ";
        if (!(cin >> value) || cin.get() != '\n')
        {
            cout << "Incorrect input!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if ((min_value <= value) && (value <= max_value)) return value;
    }
}

double work_with_user::get_double_value(int min_value, int max_value, string str)
{
    double value;
    while (true) {
        cout << "\n" + str + " - double (in " << min_value << " to " << max_value << "): ";
        cin >> value;
        if (value >= min_value && value <= max_value && cin.get() == '\n') {
            return value;
        }
        cout << "Incorrect input!" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

bool work_with_user::get_boolean_value(string str)
{
    string response;
    while (true)
    {
        cout << "\n" + str + " y or n: ";
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

std::string work_with_user::get_name_for_station()
{
    string name;
    cout << "\nEnter name of Compressor Station: ";
    getline(cin, name);
    return name;
}

void work_with_user::Out_to_File(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CS>& compressors, std::string& File_name) {
    std::ofstream out;
    out.open("/Users/leksm/Documents/hw/lab1/Badriev/" + File_name);
    if (!out.is_open()) {
        std::cout << "File didn't find \n";

    }
    if (!pipes.empty()) {
        out << "Pipe" << std::endl << pipes.size() << std::endl;
        for (const auto& item : pipes) {
            out << item.second;
        }
    }
    if (!compressors.empty()) {
        out << "CS" << std::endl << compressors.size() << std::endl;
        for (const auto& item : compressors) {
            out << item.second;
        }
    }
    std::cout << "Data is upload to file" << std::endl;
    out.close();
}

void work_with_user::In_from_file(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CS>& compressors, std::string& File_name) {
    std::ifstream in("/Users/leksm/Documents/hw/lab1/Badriev/" + File_name);
    if (!in.is_open()) {
        std::cout << "File didn't find" << std::endl;
        return;
    }
    else if (in.eof()) {
        std::cout << "File is empty" << std::endl;
        return;
    }
    std::string check;
    in >> check;
    if (check == "Pipe") {
        pipes.clear();
        int count_pipe;
        in >> count_pipe;
        for (int i = 0; i < count_pipe; ++i) {
            Pipe new_pipe(in);
            in >> new_pipe;
            pipes.insert({ new_pipe.get_id(), new_pipe });
        }
        if (!in.eof()) {
            in >> check;
        }
    }
    if (check == "CS") {
        compressors.clear();
        int count_cs;
        in >> count_cs;
        for (int i = 0; i < count_cs; ++i) {
            CS new_cs(in);
            in >> new_cs;
            compressors.insert({ new_cs.get_id(), new_cs });
        }
    }
    std::cout << "You download data from file\n" << std::endl;
    in.close();
}

