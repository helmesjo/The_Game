#pragma once

#include <vector>

class PlannerNodeBase;

class PlannerPlan{
public:
	PlannerPlan(std::vector<PlannerNodeBase*>);

	bool						HasNext();
	virtual PlannerNodeBase*	GetNext();
	virtual PlannerNodeBase*	GetCurrent();
	int							Length();

protected:
	int							m_CurrentIndex;
	std::vector<PlannerNodeBase*>	m_Plan;
};