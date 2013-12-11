#include "PathGraph.h"
#include <math.h>

PathGraph::PathGraph()
{

}
PlannerPlan PathGraph::BuildPlan( std::vector<PlannerNodeBase*> nodes )
{
	return PlannerPlan(nodes);
}
std::vector<PlannerNodeBase*> PathGraph::GetNeighbors(PlannerNodeBase* node)
{
	PathNode* pathNode = static_cast<PathNode*>(node);
	std::vector<PlannerNodeBase*> neighbors;

	PathNode* test = (PathNode*)GetReusableNode(0, [](){
		return new PathNode(0, 0);
	});

	return neighbors;
}
float PathGraph::CalculateCost( PlannerNodeBase *from, PlannerNodeBase* to )
{
	PathNode* fromPath = static_cast<PathNode*>(from);
	PathNode* toPath = static_cast<PathNode*>(to);
	// Only recalculate if no previous value is available

	float distance = fabs((float)toPath->GetX() - fromPath->GetX() + toPath->GetY() - fromPath->GetY());
	return distance;
}
float PathGraph::CalculateHeuristic( PlannerNodeBase* from, PlannerNodeBase* to )
{
	PathNode* fromPath = static_cast<PathNode*>(from);
	PathNode* toPath = static_cast<PathNode*>(to);
	// Only recalculate if no previous value is available

	float distance = fabs((float)toPath->GetX() - fromPath->GetX() + toPath->GetY() - fromPath->GetY());
	return distance;
}
bool PathGraph::IsFinished( PlannerNodeBase* node, PlannerNodeBase* endNode)
{
	PathNode* pathNodeCurrent = static_cast<PathNode*>(node);
	PathNode* pathNodeTo = static_cast<PathNode*>(endNode);

	return (pathNodeCurrent->GetX() == pathNodeTo->GetX() && pathNodeCurrent->GetY() == pathNodeTo->GetY());
}