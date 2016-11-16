#include "kmeans.h"
#include <algorithm>
#include <cstdbool>
#include <functional>
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

	vector<int> KMeans(vector<vector<double>> data, int k)
	{
		int rows = data.size();
		int cols = data[0].size();

		vector<vector<double>> means(k);
		vector<int> clusters(rows, -1);
		vector<int> numPerCluster(k, 0);

		vector<double> minimums(cols, DBL_MAX);
		vector<double> maximums(cols, DBL_MIN);

		default_random_engine re;
		vector<uniform_real_distribution<double>> unifs(cols);

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
			unifs[i] = uniform_real_distribution<double> unif(minimums[i], maximums[i]);

		// initialize mean to random values
		for (int i = 0; i < k; i++)
		{
			means[i] = vector<double>(cols);
			for (int j = 0; j < cols; j++)
				means[i][j] = unifs[i](re);
		}

		bool updated;

		do
		{
			updated = false;

			// reset number of values in each cluster
			fill(numPerCluster.begin(), numPerCluster.end(), 0);

			// calculate distances to each mean and assign
			for (auto record : data)
			{
				double minDist = DBL_MAX;
				for (int i = 0; i < k; i++)
				{
					double dist = EuclideanDistance(data[i], means[i]);
					if (dist < minDist)
					{
						minDist = dist;
						numPerCluster[i]++;
						
						// if the cluster is different, set updated flag to true
						if (clusters[i] != i)
						{
							clusters[i] = i;
							updated = true;
						}
					}
				}
			}

			// recalculate means
			for (auto mean : means) // reset means
				fill(mean.begin(), mean.end(), 0.0);

			for (int i = 0; i < rows; i++) // sum all values
				transform(means[clusters[i]].begin(), means[clusters[i]].end(), data[i].begin(), data[i].end(), plus<double>());

			for (int i = 0; i < k; i++) // divide each by number in group to get new mean
				transform(means[i].begin(), means[i].end(), means[i].begin(), bind1st(divides<double>(), numPerCluster[i]));

		} while (updated);

		return clusters;
	}
}