#pragma once

#include <memory>

struct Node{
	enum class State {
		None,
		Open,
		Closed,
	};

	virtual ~Node(){}

	void setParent(const std::weak_ptr<Node>& parentNode);
	const std::weak_ptr<Node> getParent() const;
	void setCost(const float cost);
	float getCost() const;
	void setCostSoFar(const float cost);
	float getCostSoFar() const;
	void setHeuristicCost(const float cost);
	float getHeuristicCost() const;
	float getEstimatedTotalCost() const;
	void setState(const State state);
	State getState() const;
	
private:

	std::weak_ptr<Node>	m_Parent;
	float m_Cost = 1.0f;
	float m_CostSoFar = 0.0f;			// G 
	float m_HeuristicCost = 0.0f;		// H
	State m_State = State::None;
};