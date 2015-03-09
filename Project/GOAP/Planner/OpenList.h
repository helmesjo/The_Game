#pragma once

#include <vector>
#include <memory>

struct Node;

class OpenList{
public:
	void Add(const std::shared_ptr<Node>& node);
	std::shared_ptr<Node> PopBest();
	const int size() const;

private:
	std::vector<std::shared_ptr<Node>> m_Nodes;
};