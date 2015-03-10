#include "OpenList.h"
#include "Node.h"
#include <algorithm>

void OpenList::add(const std::shared_ptr<Node>& node){
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
	node->setState(Node::State::Open);
}
std::shared_ptr<Node> OpenList::popBest(){
	if (size() == 0)
		throw std::out_of_range("OpenList is empty!");

	auto node = m_Nodes.back();
	node->setState(Node::State::Closed);
	m_Nodes.pop_back();
	return node;
}
const int OpenList::size() const{
	return m_Nodes.size();
}
void OpenList::clear(){
	m_Nodes.clear();
}