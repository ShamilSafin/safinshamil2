#pragma once
#include "work_with_user.h"
#include "Pipe.h"
#include <string>
#include <fstream>
#include <iostream>


int Pipe::Max_ID = 0;

Pipe::Pipe() {
    id = ++Max_ID;
    diameter = work_with_user::get_int_value(100, 1420, "диаметр");
    length = work_with_user::get_double_value(50, 1234, "длина");
    under_repair = work_with_user::get_boolean_value("Труба в ремонте (да или нет)");
}

int Pipe::get_id() const
{
    return id;
}

void Pipe::set_id(int new_id_value)
{
    id = new_id_value;
}

void Pipe::switch_repair()
{
    under_repair = work_with_user::get_boolean_value("Труба в ремонте (да или нет)");
}

std::ostream& operator << (std::ostream& out, const Pipe& pipe) {
    out << std::endl << "id Трубы: " << pipe.get_id() << std::endl
        << "Диаметр трубы: " << pipe.diameter << std::endl
        << "Длина трубы: " << pipe.length << std::endl;
    if (pipe.under_repair) {
        out << "в ремонте" << std::endl;
    }
    else {
        out << "не в ремонте" << std::endl;
    }
    return out;
}


std::ofstream& operator << (std::ofstream& f_out, const Pipe& pipe) {
    f_out << pipe.get_id() << std::endl << pipe.diameter << std::endl
        << pipe.length << std::endl;
    f_out << pipe.under_repair << std::endl;
    return f_out;
}

std::ifstream& operator >> (std::ifstream& f_in, Pipe& pipe) {
    int x, buf = 0;
    f_in >> x >> std::ws;
    if (buf <= x) {
        buf = x;
        Pipe::Max_ID = x;
    }
    pipe.set_id(x);
    f_in >> pipe.length;
    f_in >> pipe.diameter;
    f_in >> pipe.under_repair;
    f_in >> std::ws;
    return f_in;
}

Pipe::Pipe(std::ifstream& in) {
    length = 0;
    diameter = 0;
    under_repair = false;
}