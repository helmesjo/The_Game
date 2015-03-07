#pragma once

class Node{
public:
	virtual ~Node(){}
	virtual bool IsEqual(const Node& node) const = 0;

	float FCost = 0.0f;
};