#pragma once
#include <unordered_map>
#include <vector>
#include <fstream>
#include "Pipe.h"

class PipeCollection
{
private:
	std::vector<size_t> vectorIdForFilter;
	void PrintFilterPipe();
	void FilterPipe();
public:
	std::unordered_map<int, Pipe> pipeCollection;
	void AddPipe();
	void ChangePipe();
	void PrintPipe();
	//void PrintTablePipes();
	//void SaveToFile(std::ofstream&);
	//void DownloadFromFile(std::ifstream&);
	void DeletePipe();
	void BatchChangePipe();
};

