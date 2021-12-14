#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#ifndef CS_H
#define CS_H

class CS {
private:
    int id;
public:
    static int Max_ID;
    string name;
    int count_of_shops;
    int count_of_working_shops;
    double efficiency;
    CS();
    int get_id() const;
    void set_id(int new_id_value);
    void change_count_of_working_shops();
    explicit CS(std::ifstream& in);
    friend std::ostream& operator << (std::ostream& out, const CS& cs);
    friend std::ofstream& operator << (std::ofstream& f_out, const CS& cs);
    friend std::ifstream& operator >> (std::ifstream& f_in, CS& cs); 
    friend class CSCollection;

};

#endif // !CS_H