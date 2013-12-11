
#include "AStarPlanner.h"
#include "PathGraph.h"

int main(){
	char derp[10][10] = 
	{
		{'1','x','x','x','x'},
		{'x','x','x','x','x'},
		{'x','x','x','x','x'},
		{'x','x','x','x','x'},
		{'x','x','x','x','2'}
	};
	PathGraph* pathGraph = new PathGraph();
	AStarPlanner* planner = new AStarPlanner();
	PlannerPlan plan = planner->FindPlan(new PathNode(0,0), new PathNode(9, 9), pathGraph);

	return 0;
}