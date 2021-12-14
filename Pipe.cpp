#pragma once
#include "work_with_user.h"
#include "Pipe.h"
#include <string>
#include <fstream>
#include <iostream>


int Pipe::Max_ID = 0;

Pipe::Pipe() {
    id = ++Max_ID;
    diameter = work_with_user::get_int_value(100, 1420, "�������");
    length = work_with_user::get_double_value(50, 1234, "�����");
    under_repair = work_with_user::get_boolean_value("����� � ������� (�� ��� ���)");
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
    under_repair = work_with_user::get_boolean_value("����� � ������� (�� ��� ���)");
}

std::ostream& operator << (std::ostream& out, const Pipe& pipe) {
    out << std::endl << "id �����: " << pipe.get_id() << std::endl
        << "������� �����: " << pipe.diameter << std::endl
        << "����� �����: " << pipe.length << std::endl;
    if (pipe.under_repair) {
        out << "� �������" << std::endl;
    }
    else {
        out << "�� � �������" << std::endl;
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