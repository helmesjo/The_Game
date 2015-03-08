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

TEST(PathGraph, GetNeighborsOneNodeReturnsEightNeighbors){
	// Arrange
	vector<shared_ptr<PathNode>> nodes;
	auto node1 = std::make_shared<PathNode>(0, 0);
	auto node2 = std::make_shared<PathNode>(0, 1);
	auto node3 = std::make_shared<PathNode>(1, 0);
	auto node4 = std::make_shared<PathNode>(-1, 0);
	auto node5 = std::make_shared<PathNode>(0, -1);
	auto node6 = std::make_shared<PathNode>(1, 1);
	auto node7 = std::make_shared<PathNode>(-1, 1);
	auto node8 = std::make_shared<PathNode>(1, -1);
	auto node9 = std::make_shared<PathNode>(-1, -1);
	nodes.push_back(node1);
	nodes.push_back(node2);
	nodes.push_back(node3);
	nodes.push_back(node4);
	nodes.push_back(node5);
	nodes.push_back(node6);
	nodes.push_back(node7);
	nodes.push_back(node8);
	nodes.push_back(node9);
	PathGraph pathGraph(nodes);

	// Act
	auto neighbors = pathGraph.GetNeighbors(*node1);

	// Assert
	ASSERT_EQ(neighbors.size(), 8);
}

