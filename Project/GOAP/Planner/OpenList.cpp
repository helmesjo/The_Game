#include "OpenList.h"
#include "Node.h"

void OpenList::Add(const std::shared_ptr<Node>& node){
	int index = 0;
	for (auto node2 : m_Nodes){
		if (node2->EstimatedTotalCost < node->EstimatedTotalCost)
			break;
		++index;
	}

	m_Nodes.insert(m_Nodes.begin() + index, node);
}
std::shared_ptr<Node> OpenList::PopBest(){
	if (size() == 0)
		throw std::out_of_range("OpenList is empty!");

	auto node = m_Nodes.back();
	m_Nodes.pop_back();
	return node;
}
const int OpenList::size() const{
	return m_Nodes.size();
}