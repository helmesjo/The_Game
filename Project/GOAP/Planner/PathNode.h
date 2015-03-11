#pragma once

#include "Node.h"
#include "Graph.h"

class PathNode{
public:
	PathNode(const int x, const int y);

	int getX() const;
	int getY() const;

private:
	int m_X = 0;
	int m_Y = 0;
};