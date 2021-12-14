#include "work_with_user.h"
#include "Pipe.h"
#include "CS.h"
#include "CSCollection.h"
#include "PipeCollection.h"
#include <string>
#include <limits>
#include <iostream>
#include <unordered_map>


using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");
    PipeCollection newPipeCollection;
    CSCollection newCSColletion;
    unordered_map<int, Pipe> pipes = newPipeCollection.pipeCollection;
    unordered_map<int, CS> compressors;
    while (1)
    {
        cout << "\n\tMENU" << endl;
        cout << "1 - �������� �����" << endl;
        cout << "2 - �������� ��" << endl;
        cout << "3 - �������� ��� �������" << endl;
        cout << "4 - ������������� �����" << endl;
        cout << "5 - ������������� ��" << endl;
        cout << "6 - ���������" << endl;
        cout << "7 - ���������" << endl;
        cout << "8 - �������� �������������� ��" << endl;
        cout << "9 - �������� ��" << endl;
        cout << "10 - �������� �������������� ����" << endl;
        cout << "11 - �������� ����" << endl;
        cout << "0 - �����" << endl;
        switch (work_with_user::get_int_value(0, 11, "�������"))
        {
        case 1:
        {
            newPipeCollection.AddPipe();
            break;
        }
        case 2:
        {
            newCSColletion.AddCS();
            break;
        }
        case 3:
        {
            newPipeCollection.PrintPipe();
            newCSColletion.PrintCS();
            break;
        }
        case 4:
        {
            newPipeCollection.ChangePipe();
            break;
        }
        case 5:
        {
            newCSColletion.ChangeCS();
            break;
        }
        case 6:
        {
            if (newCSColletion.csCollection.empty() && newPipeCollection.pipeCollection.empty()) {
                cout << "�� ������� �������� ����� ����, ������ ��� ��� ���� ��� ��\n\n";
                break;
            }
            string file_name;
            cout << "������� ��� �����: ";
            getline(cin, file_name);
            work_with_user::Out_to_File(newPipeCollection.pipeCollection, newCSColletion.csCollection, file_name);
            break;
        }
        case 7:
        {
            string file_name;
            cout << "������� ��� �����: ";
            getline(cin, file_name);
            work_with_user::In_from_file(newPipeCollection.pipeCollection, newCSColletion.csCollection, file_name);
            break;
        }
        case 8:
        {
            newCSColletion.BatchChangeCS();
            break;
        }
        case 9:
        {
            newCSColletion.DeleteCS();
            break;
        }
        case 10:
        {
            newPipeCollection.BatchChangePipe();
            break;
        }
        case 11:
        {
            newPipeCollection.DeletePipe();
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