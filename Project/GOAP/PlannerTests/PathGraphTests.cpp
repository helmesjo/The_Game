#include "gmock\gmock.h"
#include <vector>
#include <memory>

#include "StarPlanner.h"
#include "PathNode.h"
#include "PathGraph.h"

using namespace std;

bool IsSame(const Node& node, shared_ptr<Node>& node2){
	return &node == node2.get();
}

TEST(PathGraph, GetNeighborsOneNodeReturnsTwoNeighbors){
	vector<shared_ptr<PathNode>> nodes;
	auto node1 = std::make_shared<PathNode>(0, 0);
	auto node2 = std::make_shared<PathNode>(0, 1);
	auto node3 = std::make_shared<PathNode>(1, 0);
	nodes.push_back(node1);
	//nodes.push_back(node2);
	//nodes.push_back(node3);

	Node& tmpNode = *node1;

	bool same = &tmpNode == node1.get();
	bool same2 = IsSame(*node1, (shared_ptr<Node>)node1);

	PathGraph pathGraph(nodes);

	auto neighbors = pathGraph.GetNeighbors(*node1);

	ASSERT_EQ(neighbors.size(), 2);
}

