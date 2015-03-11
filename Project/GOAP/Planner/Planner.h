#pragma once

#include <vector>
#include <memory>

template<class T>
class Node;

template<class T>
struct Planner{
	virtual ~Planner(){}
	virtual std::vector<std::shared_ptr<Node<T>>> findPlan(const std::shared_ptr<Node<T>>& startNode, const std::shared_ptr<Node<T>>& endNode) = 0;
};