#include "kmeans.h"
#include <cstdlib>
#include <cstring>
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

	char * filename = NULL;
	bool hasHeader = false;
	int maxIter = INT_MAX;
	int k = 5;
	int opt, val;

	while ((opt = getopt(argc, argv, "-hk:m:")) != -1)
	{
		switch (opt)
		{
		case '\1':
			if (filename != NULL)
			{
				delete[] filename;
				filename = NULL;
			}
			filename = new char[strlen(optarg) + 1];
			strcpy(filename, optarg);
			break;
		case 'h':
			hasHeader = true;
			break;
		case 'k':
			val = atoi(optarg);
			if (val < 1)
			{
				cerr << "invalid value of k" << endl;
				return 0;
			}
			k = val;
			break;
		case 'm':
			val = atoi(optarg);
			if (val < 1)
			{
				cerr << "invalid value of m" << endl;
				return 0;
			}
			maxIter = val;
			break;
		case '?': cerr << "Invalid Flag" << endl; break;
		}
	}

	if (filename == NULL)
	{
		cerr << "no file specifed";
		return 0;
	}
	if (k < 1)
	{
		cerr << "invalid value for k";
		return 0;
	}

	cout << filename << " " << k << " " << hasHeader << endl;

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

	// print data 
	//cout << "Group | Data" << endl;
	auto output = kmeans::KMeans(data, k, maxIter);
	//for (int i = 0; i < rows; i++)
	//{
	//	cout << output[i] << " | ";
	//	for (auto feature : data[i])
	//		cout << feature << " ";
	//	cout << endl;
	//}
	//cout << endl;

	// print summary
	auto totals = vector<int>(k, 0);
	for (int i = 0; i < rows; i++)
	{
		int group = output[i];
		totals[group]++;
	}

	cout << "Group" << "\t" << "# instances" << endl;
	for (int i = 0; i < k; i++)
	{
		cout << i << "\t" << totals[i] << endl;
	}

	return 0;
}