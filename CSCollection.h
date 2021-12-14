#pragma once

#include <unordered_map>
#include <vector>
#include <fstream>
#include "CS.h"


class CSCollection
{
private:
	std::vector<size_t> vectorIdForFilter;
	void PrintFilterCS();
	void FilterCS();
public:
	std::unordered_map<int, CS> csCollection;
	void AddCS();
	void ChangeCS();
	void PrintCS();
	//void PrintTableCS();
	//void SaveToFile(std::ofstream&);
	//void DownloadFromFile(std::ifstream&);
	void DeleteCS();
	void BatchChangeCS();
};


