#pragma once

#include <vector>
#include <memory>

struct Node;

class OpenList{
public:
	void add(const std::shared_ptr<Node>& node);
	std::shared_ptr<Node> popBest();
	const int size() const;
	void clear();

private:
	std::vector<std::shared_ptr<Node>> m_Nodes;
};