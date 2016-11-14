#include "dbscan.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int rows = 8;
	int cols = 2;
	double data[8][2] =
	{
		{ 0,0 },
		{ 1,1 },
		{ 7,0 },
		{ 10, 0},
		{ 11, 1 },
		{ 10, 5 },
		{ 2,3 },
		{ 2,2 }
	};

	cout << "DBSCAN Test Code" << endl;
	auto output = dbscan::DBScan(data, rows, cols, 5, 3);
	for (int i = 0; i < rows; i++)
		cout << data[i][0] << ", " << data[i][1] << "\t" << output[i] << endl;
	cout << endl;
	return 0;
}