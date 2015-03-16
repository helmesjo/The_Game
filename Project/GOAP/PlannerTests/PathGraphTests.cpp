#include "gmock\gmock.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include "StarPlanner.h"
#include "PathNode.h"
#include "PathGraph.h"

using namespace std;
using namespace Planner;

TEST(PathGraph, GetNeighbors_PassCenterNode_ReturnsStraightNeighbors){
	// Arrange
	auto node1 = std::make_shared<PathNode>(0, 0);
	auto node2 = std::make_shared<PathNode>(0, 1);
	auto node3 = std::make_shared<PathNode>(1, 0);
	auto node4 = std::make_shared<PathNode>(-1, 0);
	auto node5 = std::make_shared<PathNode>(0, -1);
	auto node6 = std::make_shared<PathNode>(1, 1);
	auto node7 = std::make_shared<PathNode>(-1, 1);
	auto node8 = std::make_shared<PathNode>(1, -1);
	auto node9 = std::make_shared<PathNode>(-1, -1);
	vector<shared_ptr<PathNode>> nodes;
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
	auto neighbors = pathGraph.getNeighbors(*node1);

	// Assert
	ASSERT_EQ(neighbors.size(), 4);
}
TEST(PathGraph, CalculateHeuristicCost_PassTwoValidNodes_ReturnsEstimatedDistance){
	auto node1 = std::make_shared<PathNode>(0, 0);
	auto node2 = std::make_shared<PathNode>(4, 3);
	PathGraph pathGraph({ node1, node2 });

	float heuristicCost = pathGraph.calculateHeuristicCost(*node1, *node2);

	ASSERT_EQ(heuristicCost, 5);
}
TEST(PathGraph, FindPlan_PassSimpleRoute_ReturnsCorrectPlan){
	auto startNode = make_shared<PathNode>(0, 0);
	auto node1 = make_shared<PathNode>(1, 0);
	auto node2 = make_shared<PathNode>(2, 0);
	auto node3 = make_shared<PathNode>(3, 0);
	auto node4 = make_shared<PathNode>(3, 1);
	auto node5 = make_shared<PathNode>(3, 2);
	auto endNode = make_shared<PathNode>(3, 3);
	PathGraph pathGraph({ startNode, node1, node2, node3, node4, node5, endNode });
	StarPlanner<PathNode, PathGraph> planner(pathGraph);

	auto nodes = planner.findPlan(*startNode, *endNode);

	ASSERT_EQ(nodes.size(), 7);
	ASSERT_TRUE(nodes[0] == startNode.get());
	ASSERT_TRUE(nodes[1] == node1.get());
	ASSERT_TRUE(nodes[2] == node2.get());
	ASSERT_TRUE(nodes[3] == node3.get());
	ASSERT_TRUE(nodes[4] == node4.get());
	ASSERT_TRUE(nodes[5] == node5.get());
	ASSERT_TRUE(nodes[6] == endNode.get());
}
TEST(PathGraph, FindPlan_PassComplexRoute_ReturnsCorrectPlan){
	// Arrange
	const std::string map[10][10] = 
	{
		" ", " ", "S", " ", "X", "E", " ", " ", " ", " ",
		" ", "X", "X", "X", "X", " ", " ", " ", " ", " ",
		" ", "X", " ", " ", "X", " ", "X", "X", "X", " ",
		" ", "X", " ", " ", " ", " ", "X", " ", " ", " ",
		" ", "X", "X", "X", "X", "X", "X", " ", "X", " ",
		" ", "X", " ", " ", "X", " ", "X", " ", "X", "X",
		" ", " ", " ", "X", "X", " ", "X", " ", " ", " ",
		" ", "X", " ", "X", " ", " ", "X", "X", " ", " ",
		" ", "X", " ", " ", " ", " ", " ", "X", "X", " ",
		" ", " ", " ", "X", " ", "X", " ", " ", " ", " ",
	};

	std::shared_ptr<PathNode> startNode = nullptr;
	std::shared_ptr<PathNode> endNode = nullptr;
	std::vector<std::shared_ptr<PathNode>> nodes;

	for (int column = 0; column < 10; ++column){
		for (int row = 0; row < 10; ++row){
			if (map[row][column] == "S")
				startNode = std::make_shared<PathNode>(column, row);
			else if (map[row][column] == "E")
				endNode = std::make_shared<PathNode>(column, row);
			else if (map[row][column] != "X")
				nodes.push_back(std::make_shared<PathNode>(column, row));
		}
	}
	nodes.insert(nodes.begin(), startNode);
	nodes.push_back(endNode);
	PathGraph graph(nodes);
	StarPlanner<PathNode, PathGraph> planner(graph);
	// Act
	auto plan = planner.findPlan(*startNode, *endNode);

	// Assert
	for (int column = 0; column < 10; ++column){
		std::cout << " ";
		for (int row = 0; row < 10; ++row){
			std::cout << " ";
			std::cout << std::endl;
		}
	}
}