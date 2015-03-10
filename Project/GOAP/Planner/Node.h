#pragma once

struct Node{
	enum class State {
		None,
		Open,
		Closed,
	};

	virtual ~Node(){}

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

	float m_Cost = 0.0f;
	float m_CostSoFar = 0.0f;			// G 
	float m_HeuristicCost = 0.0f;		// H
	float m_EstimatedTotalCost = 0.0f;	// F
	State m_State = State::None;
};