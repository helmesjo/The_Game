#pragma once

#include <vector>
#include <memory>
#include <algorithm>

template<class T>
class Node;

template<class T>
class OpenList{
public:
	void add(const std::shared_ptr<Node<T>>& node);
	std::shared_ptr<Node<T>> popBest();
	const int size() const;
	void clear();

private:
	std::vector<std::shared_ptr<Node<T>>> m_Nodes;
};
/*
template<class T>
void OpenList<T>::add(const std::shared_ptr<Node<T>>& node){
	/*
	if (std::find(m_Nodes.begin(), m_Nodes.end(), node) != m_Nodes.end()){
		auto it = std::remove(m_Nodes.begin(), m_Nodes.end(), node);
		m_Nodes.erase(it, m_Nodes.end());
	}

	int index = 0;
	for (auto node2 : m_Nodes){
		if (node2->getEstimatedTotalCost() < node->getEstimatedTotalCost())
			break;
		++index;
	}

	m_Nodes.insert(m_Nodes.begin() + index, node);
	node->setState(State::Open);
	*
}
template<class T>
std::shared_ptr<Node<T>> OpenList<T>::popBest(){
	/*
	if (size() == 0)
		throw std::out_of_range("OpenList is empty!");

	auto node = m_Nodes.back();
	node->setState(Node::State::Closed);
	m_Nodes.pop_back();
	return node;
	*
	return nullptr;
}
template<class T>
const int OpenList<T>::size() const{
	//return m_Nodes.size();
	return 0;
}
template<class T>
void OpenList<T>::clear(){
	//m_Nodes.clear();
}
*/