#pragma once

#include <vector>

class PlannerNodeBase;

class AStarOpenList{
public:
	void				AddNode(PlannerNodeBase* node);
	void				Refresh(PlannerNodeBase* node);
	PlannerNodeBase*	GetNext();
	bool				HasNext();

private:
	std::vector<PlannerNodeBase*>	m_SortedNodes;
};
