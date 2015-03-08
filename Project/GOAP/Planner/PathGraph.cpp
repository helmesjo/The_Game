#include "PathGraph.h"
#include "PathNode.h"

#include <iostream>

PathGraph::PathGraph(std::vector<std::shared_ptr<PathNode>> nodes)
	//:m_Nodes(nodes)
{
	for (auto node : m_Nodes)
		std::cout << node.get();

	m_Nodes = nodes;

	for (auto node : m_Nodes)
		std::cout << node.get();
}

std::vector<std::shared_ptr<Node>> PathGraph::GetNeighbors(const Node& node) const{
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