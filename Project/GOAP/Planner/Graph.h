#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

/* C++17 (?)
auto concept IGraph<typename T>{
	std::vector<T*> getNeighbors(const T& node) const;
	float calculateHeuristicCost(const T& fromNode, const T& toNode) const;
};
*/

namespace Planner{
	template<class T>
	class Node;

	template<class T, class Y>
	class Graph final{
	public:
		Graph(const Y& graphable);
		~Graph();

		Node<T>& getNode(const T& object);
		std::vector<Node<T>*> getNeighbors(const Node<T>& node);
		float calculateHeuristicCost(const Node<T>& fromNode, const Node<T>& toNode) const;
		bool isPlanDone(const T& obj1, const T& obj2) const;

	private:
		const Y& m_Graphable;
		std::unordered_map<const T*, std::unique_ptr<Node<T>>> m_Nodes;
	};

	template<class T, class Y>
	Graph<T, Y>::Graph(const Y& graphable) :m_Graphable(graphable){}

	template<class T, class Y>
	Graph<T, Y>::~Graph(){}

	template<class T, class Y>
	Node<T>& Graph<T, Y>::getNode(const T& object){
		Node<T>* node = nullptr;
		auto itr = m_Nodes.find(&object);
		if (itr != m_Nodes.end()){
			node = itr->second.get();
		}
		else{
			auto newNode = std::make_unique<Node<T>>(object);
			node = newNode.get();
			m_Nodes.insert({ &object, std::move(newNode) });
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

	template<class T, class Y>
	bool Graph<T, Y>::isPlanDone(const T& obj1, const T& obj2) const{
		return &obj1 == &obj2;
	}

}