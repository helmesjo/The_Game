#include "AStarPlanner.h"
#include "PlannerPlan.h"
#include "PlannerNodeBase.h"
#include "IPlannerGraph.h"

PlannerPlan AStarPlanner::FindPlan( PlannerNodeBase* startNode, PlannerNodeBase* endNode, IPlannerGraph* graph )
{
	std::vector<PlannerNodeBase*> neighbors;

	// 1. Add startnode to openList
	m_OpenList.AddNode(startNode);

	// 2. Process openList until plan found, or openList empty.
	while(m_OpenList.HasNext()){
		PlannerNodeBase* currentNode = m_OpenList.GetNext();
		// Check if current node is goal
		if(graph->IsFinished(currentNode))
			return PlannerPlan(std::vector<PlannerNodeBase*>());

		// 3. Process each neighbor
		neighbors = graph->GetNeighbors(currentNode);
		for(PlannerNodeBase* neighbor : neighbors){
			if(neighbor->State == PlannerNodeBase::CLOSED)
				continue;

			// 4. Calculate cost so far (to compare if already in openList)
			float costSoFar = currentNode->CostSoFar + graph->CalculateCost(currentNode, neighbor);

			// 5. If this node is unvisited, or it's in the openList and is a better path, set data. Else skip.
			if(neighbor->State != PlannerNodeBase::UNVISITED && costSoFar >= neighbor->CostSoFar)
				continue;
			else{
				neighbor->Parent = currentNode;
				neighbor->CostSoFar = costSoFar;
				neighbor->Heuristic = graph->CalculateHeuristic(neighbor, endNode);
				neighbor->EstimatedTotalCost = neighbor->CostSoFar + neighbor->Heuristic;
			}

			// 6. Add to openlist (if not already in list, in that case just re-sort CHANGED node only)
			if(neighbor->State == PlannerNodeBase::UNVISITED)
				m_OpenList.AddNode(neighbor);
			else
				m_OpenList.Refresh(neighbor);
		}
	}
	
	// No plan found, return empty
	return PlannerPlan(std::vector<PlannerNodeBase*>());
}