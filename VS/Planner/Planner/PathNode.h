#pragma once

#include "PlannerNodeBase.h"

class PathNode : public PlannerNodeBase{
public:
	PathNode(int x, int y);

	int GetX();
	int GetY();
private:
	int m_X;
	int m_Y;
};