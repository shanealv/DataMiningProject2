#pragma once

#include <cstdbool>
#include <list>
#include <memory>

namespace dbscan
{
	class ClusterNode
	{
	private:
		int _clusterId = -1;
		std::list<std::shared_ptr<ClusterNode>> _neighbors;
	public:
		// methods
		int GetClusterId();
		void SetClusterId(int id);

		std::list<std::shared_ptr<ClusterNode>>& GetNeighbors();
		void AddNeighbor(const std::shared_ptr<ClusterNode>& neighbor);

		/// constants
		static const int Unassigned = -1;
	};
}