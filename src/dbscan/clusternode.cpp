#include "clusternode.h"
#include <memory>

using namespace std;
using namespace dbscan;

int ClusterNode::GetClusterId()
{
	return _clusterId;
}

void ClusterNode::SetClusterId(int id)
{
	_clusterId = id;
}

list<shared_ptr<ClusterNode>> ClusterNode::GetNeighbors()
{
	return _neighbors;
}

void ClusterNode::AddNeighbor(const shared_ptr<ClusterNode> neighbor)
{
	_neighbors.push_back(neighbor);
}