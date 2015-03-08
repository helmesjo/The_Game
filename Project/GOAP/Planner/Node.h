#pragma once

struct Node{
	virtual ~Node(){}
	//virtual bool IsEqual(const Node& node) const = 0;

	float EstimatedTotalCost = 0.0f;
};