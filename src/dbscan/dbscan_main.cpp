#include "dbscan.h"
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
		cout << "Usage: ./dbscan.exe [options] file" << endl;
		cout << "Options:" << endl;
		cout << "\t-e <number>\tEpsilon, the maximum distance for two adjacent nodes to be in the same cluster (default 5)" << endl;
		cout << "\t-h\t\tSkips first line of input file (for files with header information)" << endl;
		cout << "\t-m <number>\tMinimum Points, the fewest number of points needed to declare a cluster (default 3)" << endl;
		cout << "Example:\t./dbscan -e 5 -h -m 2 testData.csv" << endl;
		return 0;
	}

	char * filename = NULL;
	bool hasHeader = false;
	double eps = 5, tempDbl;
	int minPts = 3, tempInt;
	int opt;

	while ((opt = getopt(argc, argv, "-e:hm:")) != -1)
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
		case 'e':
			tempDbl = stod(optarg);
			if (tempDbl <= 0.0)
			{
				cerr << "invalid value of epsilon" << endl;
				return 0;
			}
			eps = tempDbl;
			break;
		case 'h':
			hasHeader = true;
			break;
		case 'm':
			tempInt = stoi(optarg);
			if (tempInt < 1)
			{
				cerr << "invalid value of m" << endl;
				return 0;
			}
			minPts = tempInt;
			break;
		case '?': cerr << "Invalid Flag" << endl; break;
		}
	}

	if (filename == NULL)
	{
		cerr << "no file specifed";
		return 0;
	}
	if (eps <= 0.0)
	{
		cerr << "invalid value for epsilon";
		return 0;
	}
	if (minPts < 1)
	{
		cerr << "invalid value for minPts";
		return 0;
	}

	cout << filename << " Epsilon=" << eps << " MinPts=" << minPts << " HasHeader=" << hasHeader << endl;

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
		try 
		{ 
			while (getline(lineStream, cell, ','))
				record.push_back(stod(cell));
		}
		catch ( ... ) {
			// ignore bad lines
			continue;
		};
		data.push_back(record);
	}
	source.close();

	int rows = data.size();
	
	// figure out how many groups there were
	int numGroups = -1;
	auto output = dbscan::DBScan(data, eps, minPts, numGroups);

	if (numGroups == -1)
	{
		cout << "No Clusters Founds" << endl;
		return 0;
	}
	
	// Print Summary
	vector<int> totals (numGroups, 0);
	for (int i = 0; i < rows; i++)
	{
		int group = (*output)[i];
		totals[group]++;
	}

	cout << "Cluster" << "\t" << "# instances" << endl;
	cout << "All\t" << rows << endl;
	for (int i = 0; i < numGroups; i++)
	{
		cout << i << "\t" << totals[i] << endl;
	}

	return 0;
}