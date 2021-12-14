#include "CS.h"
#include "work_with_user.h"
#include <iostream>
#include <string>

int CS::Max_ID = 0;

CS::CS()
{
	id = ++Max_ID;
    //std::cout << "\nEnter name of Compressor Station: "; //вынести в верификацию
    //getline(cin, name); //вынести в верификацию
    name = work_with_user::get_name_for_station();
    count_of_shops = work_with_user::get_int_value(0, 20, "количество цехов");
    count_of_working_shops = work_with_user::get_int_value(0, count_of_shops, "количество цехов в работе");
    efficiency = work_with_user::get_double_value(0, 100, "эффективность");
}

int CS::get_id() const
{
    return id;
}

void CS::set_id(int new_id_value) 
{
    id = new_id_value;
}

void CS::change_count_of_working_shops() 
{
    count_of_working_shops = work_with_user::get_int_value(0, count_of_shops, "количество цехов в работе");
}

std::ostream& operator << (std::ostream& out, const CS& cs) {
    out << std::endl << "id КС: " << cs.get_id() << std::endl << "CS name: " << cs.name << std::endl
        << "Количество цехов КС: " << cs.count_of_shops
        << std::endl << "Количество работающих цехов КС: " << cs.count_of_working_shops
        << std::endl << "Эффективность КС: " << cs.efficiency << std::endl;
    return out;
}

std::ofstream& operator << (std::ofstream& f_out, const CS& cs) {
    f_out << cs.get_id() << std::endl << cs.name << std::endl << cs.count_of_shops
        << std::endl << cs.count_of_working_shops << std::endl
        << cs.efficiency << std::endl;
    return f_out;
}

std::ifstream& operator >> (std::ifstream& f_in, CS& cs) {
    int x;
    f_in >> x >> std::ws;
    if (CS::Max_ID <= x) {
        CS::Max_ID = x;
    }
    cs.set_id(x);
    getline(f_in, cs.name);
    f_in >> cs.count_of_shops;
    f_in >> cs.count_of_working_shops;
    f_in >> cs.efficiency;
    f_in >> std::ws;
    return f_in;
}

CS::CS(std::ifstream& in) {
    name = "";
    count_of_shops = 0;
    count_of_working_shops = 0;
    efficiency = 0;
}