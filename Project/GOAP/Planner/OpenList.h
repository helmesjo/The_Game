#pragma once

#include <vector>
#include <memory>
#include <algorithm>

namespace Planner{
	template<class T>
	class Node;

	template<class T>
	class OpenList{
	public:
		void add(Node<T>& node);
		Node<T>& popBest();
		const int size() const;
		void clear();

	private:
		std::vector<Node<T>*> m_Nodes;
	};

	template<class T>
	void OpenList<T>::add(Node<T>& node){
		if (std::find(m_Nodes.begin(), m_Nodes.end(), &node) != m_Nodes.end()){
			auto it = std::remove(m_Nodes.begin(), m_Nodes.end(), &node);
			m_Nodes.erase(it, m_Nodes.end());
		}

		int index = 0;
		for (auto node2 : m_Nodes){
			if (node2->getEstimatedTotalCost() < node.getEstimatedTotalCost())
				break;
			++index;
		}

		m_Nodes.insert(m_Nodes.begin() + index, &node);
		node.setState(State::Open);
	}
	template<class T>
	Node<T>& OpenList<T>::popBest(){
		if (size() == 0)
			throw std::out_of_range("OpenList is empty!");

		auto node = m_Nodes.back();
		node->setState(State::Closed);
		m_Nodes.pop_back();
		return *node;
	}
	template<class T>
	const int OpenList<T>::size() const{
		return m_Nodes.size();
	}
	template<class T>
	void OpenList<T>::clear(){
		m_Nodes.clear();
	}

}