#pragma once

#include "Node.h"

class PathNode : public Node{
public:
	PathNode(const int x, const int y);

	//virtual bool IsEqual(const Node& node) const override;
	int getX() const;
	int getY() const;

private:
	int m_X = 0;
	int m_Y = 0;
};