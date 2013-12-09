#include "PlannerPlan.h"


PlannerPlan::PlannerPlan(std::vector<PlannerNodeBase*> steps){
	m_Plan = steps;
}
bool PlannerPlan::HasNext(){
	return m_CurrentIndex+1 < m_Plan.size();
}
PlannerNodeBase* PlannerPlan::GetNext()
{
	if(HasNext())
		return m_Plan[++m_CurrentIndex];
	else
		return nullptr;
}
PlannerNodeBase* PlannerPlan::GetCurrent()
{
	return m_Plan[m_CurrentIndex];
}
int PlannerPlan::Length()
{
	return m_Plan.size();
}