#pragma once
#include <string>
#include <fstream>
#include <iostream>

class Pipe
{
private:
	int id;
public:
	static int Max_ID;
	int diameter;
	double length;
	bool under_repair;
	Pipe();
	int get_id() const;
	void set_id(int ID);
	void switch_repair();

	explicit Pipe(std::ifstream& in);
	friend std::ostream& operator << (std::ostream& out, const Pipe& pipe);
	friend std::ofstream& operator << (std::ofstream& f_out, const Pipe& pipe);
	friend std::ifstream& operator >> (std::ifstream& f_in, Pipe& pipe);
	friend class PipeCollection;
};