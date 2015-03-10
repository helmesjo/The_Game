#pragma once

struct Node{
	enum class State {
		Open,
		Closed,
	};

	virtual ~Node(){}

	void setCostSoFar(const float cost);
	float getCostSoFar() const;
	void setHeuristicCost(const float cost);
	float getHeuristicCost() const;
	float getEstimatedTotalCost() const;
	void setState(const State state);
	State getState() const;
	
private:

	float m_CostSoFar = 0.0f;
	float m_HeuristicCost = 0.0f;
	float m_EstimatedTotalCost = 0.0f;
	State m_State;
};