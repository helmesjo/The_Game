#pragma once

#include "Graph.h"
#include <vector>
#include <memory>

class PathNode;

class PathGraph : public Graph{
public:
	PathGraph(std::vector<std::shared_ptr<PathNode>> nodes);

	virtual std::vector<std::shared_ptr<Node>> GetNeighbors(const Node& node) const override;

private:
	std::vector<std::shared_ptr<PathNode>> m_Nodes;
};