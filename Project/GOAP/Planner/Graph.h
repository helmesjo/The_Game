#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

template<class T>
class Node;

template<class T>
struct IGraph{
	virtual ~IGraph(){}
	virtual std::vector<T*> getNeighbors(const T& node) const = 0;
	virtual float calculateHeuristicCost(const T& fromNode, const T& toNode) const = 0;
};

template<class T, class Y>
class Graph final{
public:
	Graph(const Y& graphable);
	~Graph();

	std::vector<Node<T>*> getNeighbors(const Node<T>& node) const;
	float calculateHeuristicCost(const Node<T>& fromNode, const Node<T>& toNode) const;

private:
	const Y& m_Graphable;
	std::unordered_map<const T*, std::unique_ptr<Node<T>>> m_Nodes;
};

template<class T, class Y>
Graph<T, Y>::Graph(const Y& graphable):m_Graphable(graphable){}
template<class T, class Y>
Graph<T, Y>::~Graph(){}
template<class T, class Y>
std::vector<Node<T>*> Graph<T, Y>::getNeighbors(const Node<T>& node) const{
	/*
	auto tNeighbors = m_Graphable->getNeighbors(node.getObject());

	std::vector<Node<T>> neighbors;
	Node<T>* neighbor = nullptr;
	for (T& obj : tNeighbors){
		if (m_Nodes.find(&obj) == m_Nodes.end()){
			std::unique_ptr<Node<T>> tmp = std::make_unique<Node<T>>(obj);
			m_Nodes.insert(&obj, std::move(tmp));
			neighbor = tmp.get;
		}
	}
	*/
	return std::vector<Node<T>>();
}
template<class T, class Y>
float Graph<T, Y>::calculateHeuristicCost(const Node<T>& fromNode, const Node<T>& toNode) const{
	return 0.0f;
}
