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

std::vector<PathNode*> PathGraph::getNeighbors(const PathNode& node) const{
	std::vector<PathNode*> neighbors;

	for (auto node2 : m_Nodes){
		if (&node == node2.get())
			continue;
		
		float dist = calculateHeuristicCost(node, *node2);
		if (dist <= 1.0f)
			neighbors.push_back(node2.get());
	}

	return neighbors;
}
float PathGraph::calculateHeuristicCost(const PathNode& fromNode, const PathNode& toNode) const{
	int x1 = fromNode.getX();
	int x2 = toNode.getX();
	int y1 = fromNode.getY();
	int y2 = toNode.getY();
	// Calculate distance
	float distance = (float)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

	return distance;
}
