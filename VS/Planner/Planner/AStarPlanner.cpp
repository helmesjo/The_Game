#include "AStarPlanner.h"
#include "PlannerPlan.h"
#include "PlannerNodeBase.h"
#include "PlannerGraphBase.h"

PlannerPlan AStarPlanner::FindPlan( PlannerNodeBase* startNode, PlannerNodeBase* endNode, PlannerGraphBase* graph )
{
	graph->Reset();
	m_OpenList.Clear();

	std::vector<PlannerNodeBase*> neighbors;

	// 1. Add startnode to openList
	m_OpenList.AddNode(startNode);

	// 2. Process openList until plan found, or openList empty.
	PlannerNodeBase* currentNode = nullptr;
	while(m_OpenList.HasNext()){
		currentNode = m_OpenList.GetNext();

		//currentNode->tempIsCurrent = true;

		//graph->DebugPrint();
		// Check if current node is goal
		if(graph->IsFinished(currentNode, endNode)){
			std::vector<PlannerNodeBase*> steps;
			PlannerNodeBase* parent = currentNode;
			while(parent){
				steps.push_back(parent);
				parent = parent->Parent;
			}

			//return PlannerPlan(std::move(std::vector<PlannerNodeBase*>()));
			//graph->DebugPrint();
			return graph->BuildPlan(steps);
		}

		// 3. Process each neighbor
		neighbors = graph->GetNeighbors(currentNode);
		for(PlannerNodeBase* neighbor : neighbors){
			//if(neighbor->State == PlannerNodeBase::CLOSED)
			//	continue;

			//neighbor->tempIsNeighbor = true;
			//graph->DebugPrint();
			//neighbor->tempIsNeighbor = false;

			// 4. Calculate cost so far (to compare if already in openList)
			float costSoFar = currentNode->CostSoFar + graph->CalculateCost(currentNode, neighbor);

			// 5. If this node is unvisited, or it's in the openList and is a better path, set data. Else skip.
			if(neighbor->State != PlannerNodeBase::NodeState::UNVISITED && costSoFar >= neighbor->CostSoFar)
				continue;
			else{
				neighbor->Parent = currentNode;
				neighbor->CostSoFar = costSoFar;
				neighbor->Heuristic = graph->CalculateHeuristic(neighbor, endNode);
				neighbor->EstimatedTotalCost = neighbor->CostSoFar + neighbor->Heuristic;
			}

			// 6. Add to openlist (if not already in list, in that case just re-sort CHANGED node only)
			if(neighbor->State == PlannerNodeBase::NodeState::UNVISITED)
				m_OpenList.AddNode(neighbor);
			else
				m_OpenList.Refresh(neighbor);
		}
		// tmp
		//currentNode->tempIsCurrent = false;
	}
	
	// No plan found, return empty
	return PlannerPlan(std::vector<PlannerNodeBase*>());
}