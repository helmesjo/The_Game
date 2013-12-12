#include "PathGraph.h"
#include <math.h>

#include <iostream>

PathGraph::PathGraph()
{
	char grid[WIDTH][HEIGHT] = {
		'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x',
		'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x',
		'x', 'x', 'x', 'x', 'w', 'x', 'x', 'x', 'x', 'x',
		'x', 'x', 'x', 'x', 'w', 'x', 'x', 'x', 'x', 'x',
		'x', 'x', 'x', 'x', 'w', 'x', 'x', 'x', 'x', 'x',
		'x', 'x', 'x', 'x', 'w', 'x', 'x', 'x', 'x', 'x',
		'x', 'x', 'x', 'x', 'w', 'x', 'x', 'x', 'x', 'x',
		'x', 'x', 'x', 'x', 'w', 'x', 'x', 'x', 'x', 'x',
		'x', 'x', 'x', 'x', 'w', 'x', 'x', 'x', 'x', 'x',
		'x', 'x', 'x', 'x', 'w', 'x', 'x', 'x', 'x', 'x',
	};
	for(int row=0; row<HEIGHT; row++){
		for(int column=0; column<WIDTH; column++){
			m_Grid[row][column] = grid[row][column];
		}
	}
}
PlannerPlan PathGraph::BuildPlan( std::vector<PlannerNodeBase*> nodes )
{
	PathNode* pathNode = nullptr;
	for(PlannerNodeBase* node : nodes){
		pathNode = (PathNode*)node;
		m_Grid[pathNode->GetY()][pathNode->GetX()] = 'O';
	}

	return PlannerPlan(nodes);
}
std::vector<PlannerNodeBase*> PathGraph::GetNeighbors(PlannerNodeBase* node)
{
	PathNode* pathNode = static_cast<PathNode*>(node);
	std::vector<PlannerNodeBase*> neighbors;

	int x = pathNode->GetX();
	int y = pathNode->GetY();

	// Find neighbors
	for(int row = std::max<int>(0, x-1); row <= std::min<int>(x+1, WIDTH); row++){
		for(int column = std::max<int>(0, y-1); column <= std::min<int>(y+1, HEIGHT); column++){
			if(row != x || column != y || m_Grid[column][row] != 'w'){
				PathNode* neighbor = (PathNode*)GetReusableNode((row*WIDTH)+column, [column, row](){
					return new PathNode(column, row);
				});
				neighbors.push_back(neighbor);
			}
		}
	}

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

void PathGraph::DebugPrint()
{
	for(int row=0; row<HEIGHT; row++){
		for(int column=0; column<WIDTH; column++){
			std::cout << m_Grid[row][column] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
