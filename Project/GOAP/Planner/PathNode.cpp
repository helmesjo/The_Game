#include "PathNode.h"

PathNode::PathNode(const int x, const int y)
	: m_X(x),
	m_Y(y)
{}

int PathNode::getX() const{
	return m_X;
}
int PathNode::getY() const{
	return m_Y;
}

/*
bool PathNode::IsEqual(const Node& node) const{
	return false;
}
*/