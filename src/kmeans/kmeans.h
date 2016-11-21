#pragma once

#include <climits>
#include <vector>

namespace kmeans
{
	double EuclideanDistance(const std::vector<double> A, const std::vector<double> B);
	std::vector<int> KMeans(std::vector<std::vector<double>>& data, int k, int maxIter = INT_MAX);
}
