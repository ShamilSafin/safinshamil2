#pragma once
#include "Pipe.h"
#include "CS.h"
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <unordered_map>

using namespace std;

namespace work_with_user {
	int get_int_value(int min_value, int max_value, string str);
	double get_double_value(int min_value, int max_value, string str);
	bool get_boolean_value(string str);
	std::string get_name_for_station();
	void Out_to_File(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CS>& compressors, std::string& File_name);
	void In_from_file(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CS>& compressors, std::string& File_name);
	template <typename T>
	std::set<T> GetMultipleNumericValues(std::string textRequest, std::string textError);
}

template <typename T>
std::set<T> work_with_user::GetMultipleNumericValues(std::string textRequest, std::string textError)
{
    std::set<T> resultSet;
    T value;
    bool flag = true;
    while (flag)
    {
        flag = false;
        std::cout << textRequest;
        while (true)
        {
            std::cin >> value;
            if (std::cin.good())
                resultSet.insert(value);
            else
            {
                std::cout << textError;
                resultSet.clear();
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                flag = true;
                break;
            }
            if (std::cin.peek() == '\n')
                break;
        }
    }
    return resultSet;
}
