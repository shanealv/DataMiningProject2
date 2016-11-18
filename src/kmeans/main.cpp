#include "kmeans.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		cout << "Usage: ./kmeans [filename]" << endl;
		return 0;
	}

	char * filename = argv[argc - 1];
	bool hasHeader = false;
	int opt, k = 5;

	while (getopt(argc, argv, "h") != -1) hasHeader = true;
	while ((opt = getopt(argc, argv, "k")) != -1) k = atoi(argv[opt]);
	cout << k << endl;
	cin >> k;
	if (k < 1)
	{
		cout << "invalid value for k";
		return 0;
	}

	ifstream source(filename);
	string line;
	vector<vector<double>> data;
	while (getline(source, line))
	{
		if (hasHeader)
		{
			hasHeader = false;
			continue;
		}
		vector<double> record;
		stringstream lineStream(line);
		string cell;
		while (getline(lineStream, cell, ','))
			record.push_back(stod(cell));
		data.push_back(record);
	}
	source.close();

	int rows = data.size();

	cout << "Group | Data" << endl;
	auto output = kmeans::KMeans(data, k);
	for (int i = 0; i < rows; i++)
	{
		cout << output[i] << " | ";
		for (auto feature : data[i])
			cout << feature << " ";
		cout << endl;
	}
	cout << endl;
	return 0;
}