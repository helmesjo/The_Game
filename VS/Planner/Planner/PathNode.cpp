#include "PathNode.h"

PathNode::PathNode( int x, int y ):
	m_X(x),
	m_Y(y)
{

}

int PathNode::GetX()
{
	return m_X;
}

int PathNode::GetY()
{
	return m_Y;
}
