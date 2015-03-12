#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

template<class T>
class Node;

/*
template<class T>
struct IGraph{
	virtual ~IGraph(){}
	virtual std::vector<T*> getNeighbors(const T& node) const = 0;
	virtual float calculateHeuristicCost(const T& fromNode, const T& toNode) const = 0;
};
*/

template<class T, class Y>
class Graph final{
public:
	Graph(const Y& graphable);
	~Graph();

	Node<T>& getNode(const T& object);
	std::vector<Node<T>*> getNeighbors(const Node<T>& node);
	float calculateHeuristicCost(const Node<T>& fromNode, const Node<T>& toNode) const;

private:
	const Y& m_Graphable;
	std::unordered_map<const T*, std::shared_ptr<Node<T>>> m_Nodes;
};

template<class T, class Y>
Graph<T, Y>::Graph(const Y& graphable):m_Graphable(graphable){
}

template<class T, class Y>
Graph<T, Y>::~Graph(){}

template<class T, class Y>
Node<T>& Graph<T, Y>::getNode(const T& object){
	std::shared_ptr<Node<T>> node = nullptr;
	auto itr = m_Nodes.find(&object);
	if (itr != m_Nodes.end()){
		node = itr->second;
	}
	else{
		node = std::make_shared<Node<T>>(object);
		m_Nodes.insert({ &object, node });
	}

	return *node;
}

template<class T, class Y>
std::vector<Node<T>*> Graph<T, Y>::getNeighbors(const Node<T>& node){
	auto tNeighbors = m_Graphable.getNeighbors(node.getObject());
	
	std::vector<Node<T>*> neighbors;
	for (const T* obj : tNeighbors){
		Node<T>& neighbor = getNode(*obj);
		neighbors.push_back(&neighbor);
	}
	
	return neighbors;
}
template<class T, class Y>
float Graph<T, Y>::calculateHeuristicCost(const Node<T>& fromNode, const Node<T>& toNode) const{
	return 0.0f;
}
