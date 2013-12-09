#include "IPlannerGraph.h"
#include "PathNode.h"
#include "PlannerPlan.h"

#include <vector>


template<int width, int height>
class PathGraph : IPlannerGraph{
public:
	PathGraph(char* map[width][height]);

#pragma region IPlannerGraph
	virtual PlannerPlan							BuildPlan(std::vector<PlannerNodeBase*> nodes);
	virtual std::vector<PlannerNodeBase*>		GetNeighbors(PlannerNodeBase* node);
	virtual float								CalculateCost(PlannerNodeBase *from, PlannerNodeBase* to);
	virtual float								CalculateHeuristic( PlannerNodeBase* from, PlannerNodeBase* to );
	virtual bool								IsFinished(PlannerNodeBase* node);
#pragma endregion IPlannerGraph

private:
	// temp stuff
	char* m_PathMap[width][height];
};