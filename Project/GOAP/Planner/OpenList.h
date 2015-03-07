#pragma once

#include <vector>
#include <memory>

class Node;

class OpenList{
public:
	void Add(const std::shared_ptr<Node>& node);
	std::shared_ptr<Node> PopBest();

private:
	std::vector<std::shared_ptr<Node>> m_Nodes;
};