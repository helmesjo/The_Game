#include "PathNode.h"

PathNode::PathNode( const int x, const int y):
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