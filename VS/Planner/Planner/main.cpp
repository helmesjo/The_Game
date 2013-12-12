
#include "AStarPlanner.h"
#include "PathGraph.h"

int main(){
	PathGraph* pathGraph = new PathGraph();
	AStarPlanner* planner = new AStarPlanner();

	PlannerNodeBase *startNode = pathGraph->GetReusableNode(0, [](){
		return new PathNode(0, 0);
	});
	PlannerNodeBase *endNode = pathGraph->GetReusableNode(pathGraph->HEIGHT*pathGraph->HEIGHT-1+pathGraph->WIDTH-1, [pathGraph](){
		return new PathNode(pathGraph->WIDTH-1, pathGraph->HEIGHT-1);
	});

	pathGraph->DebugPrint();
	PlannerPlan plan = planner->FindPlan(startNode, endNode, pathGraph);
	pathGraph->DebugPrint();

	return 0;
}