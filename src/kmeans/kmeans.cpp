#include "kmeans.h"
#include <algorithm>
#include <cfloat>
#include <climits>
#include <cstdbool>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <list>
#include <random>
#include <vector>

using namespace std;
namespace kmeans
{
	double EuclideanDistance(const vector<double> A, const vector<double> B)
	{
		if (A.size() != B.size())
			throw logic_error("Distance undefined for vectors of different lengths");

		double distance = 0;
		for (int i = 0; i < A.size(); i++)
			distance += pow(B[i] - A[i], 2);
		return sqrt(distance);
	}

	vector<int> KMeans(vector<vector<double>> data, int k, int maxIter)
	{
		if (k <= 0)
			throw invalid_argument("k must be a positive integer");
		if (maxIter <= 0)
			throw invalid_argument("maxIter must be a positive integer");
		if (data.size() <= 0)
			throw invalid_argument("data must contain at least one record");
		if (data[0].size() <= 0)
			throw invalid_argument("records must contain at least one column");

		int rows = data.size();
		int cols = data[0].size();

		vector<vector<double>> means(k);
		vector<int> clusters(rows, -1);
		vector<int> numPerCluster(k, 0);

		vector<double> minimums(cols, DBL_MAX);
		vector<double> maximums(cols, DBL_MIN);

		default_random_engine re;
		vector<uniform_real_distribution<double>> distribs(cols);

		// first calculate the range for each column
		for (auto record : data)
			for (int i = 0; i < cols; i++)
			{
				double val = record[i];
				if (val < minimums[i])
					minimums[i] = val;
				if (val > maximums[i])
					maximums[i] = val;
			}

		// create random number generator for each column in a record
		for (int i = 0; i < cols; i++)
			distribs[i] = uniform_real_distribution<double>(minimums[i] - 1, maximums[i] + 1);

		// initialize mean to random values
		for (int i = 0; i < k; i++)
		{
			means[i] = vector<double>(cols);
			for (int j = 0; j < cols; j++)
				means[i][j] = distribs[j](re);
		}
		bool updated;

		do
		{
			updated = false;

			// reset number of values in each cluster
			fill(numPerCluster.begin(), numPerCluster.end(), 0);

			// calculate distances to each mean and assign
			for (int i = 0; i < rows; i++) // for each record
			{
				double minDist = DBL_MAX;
				int cluster = -1;
				for (int j = 0; j < k; j++) // for each mean
				{
					// check if this mean is closer
					double dist = EuclideanDistance(data[i], means[j]);
					if (dist < minDist)
					{
						minDist = dist;
						cluster = j;
					}
				}

				// assign to nearest cluster
				numPerCluster[cluster]++;
				if (clusters[i] != cluster)
				{
					clusters[i] = cluster;
					updated = true;
				}
			}

			// recalculate means
			for (auto mean : means) // reset means
				fill(mean.begin(), mean.end(), 0.0);

			for (int i = 0; i < rows; i++) // sum all values
				for (int j = 0, cluster = clusters[i]; j < cols; j++)
					means[cluster][j] += data[i][j];

			for (int i = 0; i < k; i++) // divide each by number in group to get new mean
				for (int j = 0; j < cols; j++)
					means[i][j] /= numPerCluster[i];

		} while (updated && --maxIter > 0);

		return clusters;
	}
}