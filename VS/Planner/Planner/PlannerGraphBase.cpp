#include "PlannerGraphBase.h"

//template<typename NodeType>
PlannerNodeBase* PlannerGraphBase::GetReusableNode(const int id, const std::function<PlannerNodeBase*()>& createNode){
	auto itr = m_NodeTable.find(id);

	PlannerNodeBase* node = nullptr;
	if(itr == m_NodeTable.end()){
		node = createNode();
		m_NodeTable.insert(std::make_pair(id, node));
	}
	else
		node = itr->second;

	return node;
}