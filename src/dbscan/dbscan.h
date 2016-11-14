#pragma once

namespace dbscan
{
	double EuclideanDistance(double A[], double B[], int size);
	int* DBScan(const double data[8][2], int rows, int cols, double epsilon, int minPts);
}