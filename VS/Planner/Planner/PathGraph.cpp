#include "PathGraph.h"

template<int width, int height>
PathGraph::PathGraph(char* map[width][height]):
	m_PathMap(map)
{
// 	{
// 		{'1','2','3','4','5'},
// 		{'1','2','3','4','5'},
// 		{'1','2','3','4','5'},
// 		{'1','2','3','4','5'},
// 		{'1','2','3','4','5'}
// 	}
	
}
template<int width, int height>
PlannerPlan PathGraph<width, height>::BuildPlan( std::vector<PlannerNodeBase*> nodes )
{
	return PlannerPlan(nodes);
}
template<int width, int height>
std::vector<PlannerNodeBase*> PathGraph::GetNeighbors(PlannerNodeBase* node)
{
	return std::vector<PlannerNodeBase*>();
}
template<int width, int height>
float PathGraph::CalculateHeuristic( PlannerNodeBase* from, PlannerNodeBase* to )
{
	// Only recalculate if no previous value is available

	return -1.0f;
}
template<int width, int height>
bool PathGraph<width, height>::IsFinished( PlannerNodeBase* node )
{
	return true;
}