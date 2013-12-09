#include "AStarOpenList.h"
#include "PlannerNodeBase.h"

void AStarOpenList::AddNode( PlannerNodeBase* node )
{
	node->State = PlannerNodeBase::OPEN;
	if(m_SortedNodes.empty())
		m_SortedNodes.push_back(node);
	
	// Insert at correct position (asc sorting)
	for(int i=m_SortedNodes.size()-1; i>0; i--){
		if(node->EstimatedTotalCost <= m_SortedNodes[i]->EstimatedTotalCost){
			m_SortedNodes.insert(m_SortedNodes.begin() + i + 1, node);
			break;
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
	if(node->State != PlannerNodeBase::OPEN)
		return;

	Update nodes position in list!
}
