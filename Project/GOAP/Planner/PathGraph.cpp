#include "PathGraph.h"
#include "PathNode.h"

#include <iostream>
#include <math.h>

using namespace std;

PathGraph::PathGraph(std::vector<std::shared_ptr<PathNode>> nodes)
	:m_Nodes(nodes)
{}
PathGraph::PathGraph(const std::initializer_list<std::shared_ptr<PathNode>> nodes)
	:m_Nodes(nodes)
{}

std::vector<std::shared_ptr<Node>> PathGraph::getNeighbors(const Node& node) const{
	auto& pathNode = (const PathNode&)node;

	std::vector<std::shared_ptr<Node>> neighbors;

	for (auto node2 : m_Nodes){
		if (&pathNode == node2.get())
			continue;
		
		float dist = calculateHeuristicCost(node, *node2);
		if (dist <= 1.0f)
			neighbors.push_back(node2);
	}

	return neighbors;
}
float PathGraph::calculateHeuristicCost(const Node& fromNode, const Node& toNode) const{
	auto& pathNodeFrom = dynamic_cast<const PathNode&>(fromNode);
	auto& pathNodeTo = dynamic_cast<const PathNode&>(toNode);

	int x1 = pathNodeFrom.getX();
	int x2 = pathNodeTo.getX();
	int y1 = pathNodeFrom.getY();
	int y2 = pathNodeTo.getY();
	// Calculate distance
	float distance = (float)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

	return distance;
}
