#include "IStarPlanner.h"
#include "AStarOpenList.h"

class AStarPlanner : IStarPlanner{
public:
	virtual PlannerPlan FindPlan( PlannerNodeBase* startNode, PlannerNodeBase* endNode, IPlannerGraph* graph );

private:
	AStarOpenList	m_OpenList;
};