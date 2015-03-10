#include "PathGraph.h"
#include "PathNode.h"

#include <iostream>
#include <math.h>

using namespace std;

PathGraph::PathGraph(std::vector<std::shared_ptr<PathNode>> nodes)
	//:m_Nodes(nodes)
{
	for (auto node : m_Nodes)
		std::cout << node.get();

	m_Nodes = nodes;

	for (auto node : m_Nodes)
		std::cout << node.get();
}
PathGraph::PathGraph(const std::initializer_list<std::shared_ptr<PathNode>> nodes)
	:PathGraph(nodes)
{}

std::vector<std::shared_ptr<Node>> PathGraph::getNeighbors(const Node& node) const{
	auto& pathNode = (const PathNode&)node;

	std::vector<std::shared_ptr<Node>> neighbors;

	for (auto node2 : m_Nodes){
		if (&pathNode == node2.get())
			continue;

		int xDist = abs(pathNode.getX() - node2->getX());
		int yDist = abs(pathNode.getY() - node2->getY());

		if (xDist <= 1 && yDist <= 1)
			neighbors.push_back(node2);
	}

	return neighbors;
}
float PathGraph::calculateHeuristicCost(const Node& fromNode, const Node& toNode) const{
	auto& pathNodeFrom = dynamic_cast<const PathNode&>(fromNode);
	auto& pathNodeTo = dynamic_cast<const PathNode&>(toNode);

	float x1 = pathNodeFrom.getX();
	float x2 = pathNodeTo.getX();
	float y1 = pathNodeFrom.getY();
	float y2 = pathNodeTo.getY();
	// Calculate distance
	float distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

	return distance;
}
