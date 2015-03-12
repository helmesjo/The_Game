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

	std::vector<std::shared_ptr<Node<T>>> getNeighbors(const Node<T>& node);
	float calculateHeuristicCost(const Node<T>& fromNode, const Node<T>& toNode) const;

private:
	const Y& m_Graphable;
	std::unordered_map<int, int> m_Nodes;
};

template<class T, class Y>
Graph<T, Y>::Graph(const Y& graphable):m_Graphable(graphable){
	//m_Nodes.insert({ 1, 1 });
	m_Nodes.insert({ 1, 1 });
	m_Nodes.find(1);
}
template<class T, class Y>
Graph<T, Y>::~Graph(){}
template<class T, class Y>
std::vector<std::shared_ptr<Node<T>>> Graph<T, Y>::getNeighbors(const Node<T>& node){
	auto tNeighbors = m_Graphable.getNeighbors(node.getObject());
	
	//m_Nodes.insert({ 1, 1 });
	//m_Nodes.find(1);

	std::vector<std::shared_ptr<Node<T>>> neighbors;
	std::shared_ptr<Node<T>> neighbor = nullptr;
	for (const T* obj : tNeighbors){
		//auto itr = m_Nodes.find(1);
		if (false == false){
			neighbor = nullptr;// itr->second;
		}
		else{
			neighbor = std::make_shared<Node<T>>(*obj);
			//derpa.push_back(neighbor);
			//m_Nodes.insert( std::make_pair<const T*, std::shared_ptr<Node<T>>(obj, neighbor) );
		}
		neighbors.push_back(neighbor);
	}
	
	return neighbors;
}
template<class T, class Y>
float Graph<T, Y>::calculateHeuristicCost(const Node<T>& fromNode, const Node<T>& toNode) const{
	return 0.0f;
}
