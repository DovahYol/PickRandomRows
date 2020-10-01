// PickRandomRows.cpp : Defines the entry point for the application.
//

#include "PickRandomRows.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <set>

using namespace std;

int Str2Int(const string& p_str) {
	stringstream ss(p_str);
	int ans;
	ss >> ans;
	return ans;
}
int main(int argc, char* argv[])
{
	if (argc < 5) {
		cout << "PickRandomRows inName outName randRowNum originalRowNum" << endl;
		return 0;
	}
	string inName = argv[1];
	string outName = argv[2];
	string randRowNumStr = argv[3];
	string originalRowNumStr = argv[4];
	int randRowNum, originalRowNum;

	randRowNum = Str2Int(randRowNumStr);
	originalRowNum = Str2Int(originalRowNumStr);

	cout << "Expect to choose " << randRowNum << " lines from " << originalRowNum << "lines." << endl;

	vector<int> vec(randRowNum);
	srand((unsigned)time(NULL));
	for (int i = 0; i < randRowNum; i++) {
		vec[i] = rand() % originalRowNum;
	}
	
	set<int> my_set(vec.begin(), vec.end());
	
	cout << "Expect to choose" << my_set.size() << " lines after unique." << endl;

	ifstream inFile(inName, ifstream::binary);
	ofstream outFile(outName, ofstream::binary);
	
	int counter = 0;
	for (int i = 0; i < originalRowNum; i++) {
		int rowNum;
		inFile.read(reinterpret_cast<char*>(&rowNum), 4);
		vector<int8_t> vec(rowNum);
		inFile.read(reinterpret_cast<char*>(vec.data()), rowNum * sizeof(int8_t));

		if (my_set.count(i) > 0) {
			outFile.write(reinterpret_cast<char*>(&rowNum), 4);
			outFile.write(reinterpret_cast<char*>(vec.data()), rowNum * sizeof(int8_t));
			counter++;
		}
	}

	if (my_set.size() != counter) {
		cout << "Get wrong number of records, Expected: " << my_set.size() << " Acually: " << counter << endl;
		return 1;
	}

	return 0;
}
