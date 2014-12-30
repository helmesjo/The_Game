#include "AStarOpenList.h"
#include "PlannerNodeBase.h"
#include <algorithm>
#include <functional>

void AStarOpenList::AddNode( PlannerNodeBase* node )
{
	node->State = PlannerNodeBase::NodeState::OPEN;

	// If no nodes available, or if it's cost is greater than first (worst) node, add to beginning
	if(m_SortedNodes.empty() || m_SortedNodes.back()->EstimatedTotalCost <= node->EstimatedTotalCost){
		m_SortedNodes.insert(m_SortedNodes.begin(), node);
		return;
	}
	
	// Insert at correct position (asc sorting)
	int counter = 0;
	for(PlannerNodeBase* other : m_SortedNodes){
		if(node->EstimatedTotalCost <= other->EstimatedTotalCost){
			m_SortedNodes.insert(m_SortedNodes.end()-counter, node);
			return;
		}
		counter++;
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
	node->State = PlannerNodeBase::NodeState::CLOSED;
	m_SortedNodes.pop_back();
	return node;
}
void AStarOpenList::Refresh( PlannerNodeBase* node )
{
	// Is it in the list?
	if(node->State != PlannerNodeBase::NodeState::OPEN)
		return;

	// Should be efficient here since we only expect one node to be out of sync.
	std::sort(m_SortedNodes.begin(), m_SortedNodes.end());
}
void AStarOpenList::Clear()
{
	m_SortedNodes.clear();
}
