#include "dbscan.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 1)
	{
		cout << "Usage: ./kmeans [filename]" << endl;
		return 0;
	}
	ifstream source(argv[1]);
	string line;
	vector<vector<double>> data;
	while (getline(source, line))
	{
		vector<double> record;
		stringstream lineStream(line);
		string cell;
		while (getline(lineStream, cell, ','))
			record.push_back(stod(cell));
		data.push_back(record);
	}
	source.close();

	int rows = data.size();
	cout << "DBSCAN Test Code" << endl;
	auto output = dbscan::DBScan(data, 5, 3);
	for (int i = 0; i < rows; i++)
		cout << data[i][0] << ", " << data[i][1] << "\t" << output[i] << endl;
	cout << endl;
	return 0;
}