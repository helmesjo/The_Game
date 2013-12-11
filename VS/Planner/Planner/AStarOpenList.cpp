#include "AStarOpenList.h"
#include "PlannerNodeBase.h"
#include <algorithm>
#include <functional>

void AStarOpenList::AddNode( PlannerNodeBase* node )
{
	node->State = PlannerNodeBase::OPEN;
	if(m_SortedNodes.empty()){
		m_SortedNodes.push_back(node);
		return;
	}
	
	// Insert at correct position (asc sorting)
	for(int i=m_SortedNodes.size()-1; i>0; i--){
		if(node->EstimatedTotalCost <= m_SortedNodes[i]->EstimatedTotalCost){
			m_SortedNodes.insert(m_SortedNodes.begin() + i + 1, node);
			return;
		}
	}
}
bool AStarOpenList::HasNext()
{
	return !m_SortedNodes.empty();
}
PlannerNodeBase* AStarOpenList::GetNext()
{
	if(!HasNext())
		return nullptr;

	PlannerNodeBase* node = m_SortedNodes.back();
	node->State = PlannerNodeBase::CLOSED;
	m_SortedNodes.pop_back();
	return node;
}
void AStarOpenList::Refresh( PlannerNodeBase* node )
{
	// Is it in the list?
	if(node->State != PlannerNodeBase::OPEN)
		return;

	// Should be efficient here since we only expect one node to be out of sync.
	std::sort(m_SortedNodes.begin(), m_SortedNodes.end());
}
