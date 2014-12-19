#include "PathGraph.h"
#include <math.h>

#include <iostream>

PathGraph::PathGraph()
{
	char grid[WIDTH][HEIGHT] = {
		' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		' ', 'X', ' ', 'X', 'X', ' ', ' ', 'X', 'X', ' ', ' ', 'X', ' ', 'X', 'X', ' ', ' ', 'X', 'X', ' ',
		' ', 'X', ' ', 'X', ' ', ' ', ' ', 'X', ' ', ' ', ' ', 'X', ' ', 'X', ' ', ' ', ' ', 'X', ' ', ' ',
		' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',
		' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', ' ', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', ' ',
		' ', ' ', ' ', 'X', ' ', 'X', ' ', 'X', 'X', ' ', ' ', ' ', ' ', 'X', ' ', 'X', ' ', 'X', 'X', ' ',
		' ', 'X', 'X', 'X', ' ', 'X', ' ', 'X', ' ', ' ', ' ', 'X', 'X', 'X', ' ', 'X', ' ', 'X', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', 'X', ' ', ' ', ' ', ' ',
		' ', 'X', 'X', ' ', 'X', 'X', 'X', 'X', 'X', ' ', ' ', 'X', 'X', ' ', 'X', 'X', 'X', 'X', 'X', ' ',
		' ', 'X', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ',
		' ', 'X', ' ', 'X', 'X', ' ', ' ', 'X', 'X', ' ', ' ', 'X', ' ', 'X', 'X', ' ', ' ', 'X', 'X', ' ',
		' ', 'X', ' ', 'X', ' ', ' ', ' ', 'X', ' ', ' ', ' ', 'X', ' ', 'X', ' ', ' ', ' ', 'X', ' ', ' ',
		' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',
		' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', ' ', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', ' ',
		' ', ' ', ' ', 'X', ' ', 'X', ' ', 'X', 'X', ' ', ' ', ' ', ' ', 'X', ' ', 'X', ' ', 'X', 'X', ' ',
		' ', 'X', 'X', 'X', ' ', 'X', ' ', 'X', ' ', ' ', ' ', 'X', 'X', 'X', ' ', 'X', ' ', 'X', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ',
		' ', 'X', 'X', ' ', 'X', 'X', 'X', 'X', 'X', ' ', ' ', 'X', 'X', ' ', 'X', 'X', 'X', 'X', 'X', ' ',
		' ', 'X', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ',
	};
	for(int row=0; row<HEIGHT; row++){
		for(int column=0; column<WIDTH; column++){
			m_Grid[row][column] = grid[row][column];
			m_DefaultGrid[row][column] = grid[row][column];
		}
	}
}
PlannerPlan PathGraph::BuildPlan( std::vector<PlannerNodeBase*> nodes )
{
	PathNode* pathNode = nullptr;
	for(PlannerNodeBase* node : nodes){
		pathNode = (PathNode*)node;
		m_Grid[pathNode->GetY()][pathNode->GetX()] = '-';
	}

	for(int row=0; row<HEIGHT; row++){
		for(int column=0; column<WIDTH; column++){
			std::cout << m_Grid[row][column] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return PlannerPlan(nodes);
}
std::vector<PlannerNodeBase*> PathGraph::GetNeighbors(PlannerNodeBase* node)
{
	PathNode* pathNode = static_cast<PathNode*>(node);
	std::vector<PlannerNodeBase*> neighbors;

	int x = pathNode->GetX();
	int y = pathNode->GetY();

	// Find neighbors
	for(int row = std::max<int>(0, y-1); row <= std::min<int>(y+1, HEIGHT-1); row++){
		for(int column = std::max<int>(0, x-1); column <= std::min<int>(x+1, WIDTH-1); column++){
			if((row != y || column != x) && m_Grid[row][column] == ' '){
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

	float distance = std::hypotf((float)toPath->GetX() - fromPath->GetX(), (float)toPath->GetY() - fromPath->GetY());
	return distance;
}
float PathGraph::CalculateHeuristic( PlannerNodeBase* from, PlannerNodeBase* to )
{
	PathNode* fromPath = static_cast<PathNode*>(from);
	PathNode* toPath = static_cast<PathNode*>(to);
	// Only recalculate if no previous value is available

	float distance = std::hypotf((float)toPath->GetX() - fromPath->GetX(), (float)toPath->GetY() - fromPath->GetY());
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
	return;
	// Reset grid
	for(int row=0; row<HEIGHT; row++){
		for(int column=0; column<WIDTH; column++){
			m_Grid[row][column] = m_DefaultGrid[row][column];
		}
	}

	std::vector<PlannerNodeBase*> nodes = GetNodes();

	PathNode* path = nullptr;
	for(PlannerNodeBase* node : nodes){
		path = (PathNode*)node;

		if(node->tempIsCurrent){
			m_Grid[path->GetY()][path->GetX()] = '1';
			continue;
		}
		else if(node->tempIsNeighbor){
			m_Grid[path->GetY()][path->GetX()] = '2';
			continue;
		}

		switch (node->State)
		{
		case PlannerNodeBase::NodeState::CLOSED:
			m_Grid[path->GetY()][path->GetX()] = 'C';
			break;
		case PlannerNodeBase::NodeState::OPEN:
			m_Grid[path->GetY()][path->GetX()] = 'O';
			break;
		case PlannerNodeBase::NodeState::UNVISITED:
			m_Grid[path->GetY()][path->GetX()] = 'U';
			break;
		default:
			break;
		}
	}
	for(int row=0; row<HEIGHT; row++){
		for(int column=0; column<WIDTH; column++){
			std::cout << m_Grid[row][column] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
