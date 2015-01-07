#pragma once

class Node{
public:
	virtual ~Node(){}
	
};

inline bool operator==(const Node& lhs, const Node& rhs){ return true; }
inline bool operator!=(const Node& lhs, const Node& rhs){ return !operator==(lhs, rhs); }
inline bool operator< (const Node& lhs, const Node& rhs){ return true; }
inline bool operator> (const Node& lhs, const Node& rhs){ return  operator< (rhs, lhs); }
inline bool operator<=(const Node& lhs, const Node& rhs){ return !operator> (lhs, rhs); }
inline bool operator>=(const Node& lhs, const Node& rhs){ return !operator< (lhs, rhs); }