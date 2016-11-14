#include <cmath>
#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <stack>
#include <vector>
#include <stdbool.h>
#include "dbscan.h"
#include "clusternode.h"

using namespace std;

namespace dbscan
{
	double EuclideanDistance(const double A[], const double B[], int dimensions)
	{
		double distance = 0;
		for (int i = 0; i < dimensions; i++)
			distance += pow(B[i] - A[i], 2);
		return sqrt(distance);
	}

	int* DBScan(const double data[8][2], int rows, int cols, double epsilon, int minPts)
	{
		auto nodes = vector<shared_ptr<ClusterNode>>(rows);
		auto clusters = new int[rows];

		for (int i = 0; i < rows; i++)
			nodes[i] = make_shared<ClusterNode>();

		// calculate the neighbors for each node
		for (int i = 0; i < rows; i++)
			for (int j = i + 1; j < rows; j++)
			{
				double dist = EuclideanDistance(data[i], data[j], cols);
				if (dist <= epsilon)
				{
					nodes[i]->AddNeighbor(nodes[j]);
					nodes[j]->AddNeighbor(nodes[i]);
				}
			}

		// Assign all points
		int clusterNum = 0;
		for (int i = 0; i < rows; i++)
		{
			// if already assigned or a not a core point, ignore
			if (nodes[i]->GetClusterId() != ClusterNode::Unassigned || nodes[i]->GetNeighbors().size() + 1 < minPts)
				continue;

			int id = clusterNum++;
			nodes[i]->SetClusterId(id);

			// use DFS to assign each point neighbor to the same cluster (expanding core points only)
			list<shared_ptr<ClusterNode>> visited;
			stack<shared_ptr<ClusterNode>> SeedSet;

			SeedSet.push(nodes[i]); // to expand the first node
			while (!SeedSet.empty())
			{
				// expanded node
				auto nodePtr = SeedSet.top();

				// remove from seed set
				SeedSet.pop();

				// set cluster id
				nodePtr->SetClusterId(id);

				// ignore previously visited
				bool previouslyVisited = false;
				for (auto vNode : visited)
					if (vNode == nodePtr) // compare addresses
					{
						previouslyVisited = true;
						break;
					}
				if (previouslyVisited)
					continue;

				// add to visited
				auto newPtr(nodePtr);
				visited.push_back(newPtr);

				// if core point, add all points to SeedSet
				auto neighbors = nodePtr->GetNeighbors();
				if (neighbors.size() + 1 >= minPts)
					for (auto nNode : neighbors)
						SeedSet.push(nNode);
			} // end while [seed set not empty]
		} // end for [each node to assign]

		// copy results to clusters array
		for (int i = 0; i < rows; i++)
		{
			clusters[i] = nodes[i]->GetClusterId();
		}

		return clusters;
	} // end DBSCAN
}