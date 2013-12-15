#include <iostream>
#include "AStarPlanner.h"
#include "PathGraph.h"
#include "HTimer.h"

#include <windows.h>

const int ITERATIONS = 1;

int main(){
	PathGraph* pathGraph = new PathGraph();
	AStarPlanner* planner = new AStarPlanner();

	PlannerNodeBase *startNode = pathGraph->GetReusableNode(0, [](){
		return new PathNode(0, 0);
	});
	PlannerNodeBase *endNode = pathGraph->GetReusableNode(pathGraph->HEIGHT*pathGraph->HEIGHT-1+pathGraph->WIDTH-1, [pathGraph](){
		return new PathNode(pathGraph->WIDTH-1, pathGraph->HEIGHT-1);
	});

	HTimer timer;
	timer.Start();
	//for(int i=0; i<ITERATIONS; i++)
		PlannerPlan plan = planner->FindPlan(startNode, endNode, pathGraph);
	std::cout<< "Time(ms): " << timer.Stop() / ITERATIONS << std::endl;
	//	pathGraph->DebugPrint();

	int x;
	std::cin>>x;

	return 0;
}