#include "Node.h"

void Node::setCostSoFar(const float cost){
	m_CostSoFar = cost;
}
float Node::getCostSoFar() const{
	return m_CostSoFar;
}
void Node::setHeuristicCost(const float cost){
	m_HeuristicCost = cost;
}
float Node::getHeuristicCost() const{
	return m_HeuristicCost;
}
float Node::getEstimatedTotalCost() const{
	return m_CostSoFar + m_HeuristicCost;
}
void Node::setState(const Node::State state){
	m_State = state;
}
Node::State Node::getState() const{
	return m_State;
}