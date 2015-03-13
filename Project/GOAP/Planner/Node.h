#pragma once

#include <memory>

namespace Planner{

	enum class State {
		None,
		Open,
		Closed,
	};

	template<class T>
	class Node final{
	public:

		Node(const T& object);
		~Node();

		const T& getObject() const;
		void setParent(Node<T>* parentNode);
		Node<T>* getParent() const;
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

		const T& m_Object;
		Node<T>* m_Parent = nullptr;
		float m_Cost = 1.0f;
		float m_CostSoFar = 0.0f;			// G 
		float m_HeuristicCost = 0.0f;		// H
		State m_State = State::None;
	};

	template<class T>
	Node<T>::Node(const T& object)
		:m_Object(object)
	{}
	template<class T>
	Node<T>::~Node(){}
	template<class T>
	const T& Node<T>::getObject() const{
		return m_Object;
	}
	template<class T>
	void Node<T>::setParent(Node<T>* parentNode){
		m_Parent = parentNode;
	}
	template<class T>
	Node<T>* Node<T>::getParent() const{
		return m_Parent;
	}
	template<class T>
	void Node<T>::setCost(const float cost){
		m_Cost = cost;
	}
	template<class T>
	float Node<T>::getCost() const{
		return m_Cost;
	}
	template<class T>
	void Node<T>::setCostSoFar(const float cost){
		m_CostSoFar = cost;
	}
	template<class T>
	float Node<T>::getCostSoFar() const{
		return m_CostSoFar;
	}
	template<class T>
	void Node<T>::setHeuristicCost(const float cost){
		m_HeuristicCost = cost;
	}
	template<class T>
	float Node<T>::getHeuristicCost() const{
		return m_HeuristicCost;
	}
	template<class T>
	float Node<T>::getEstimatedTotalCost() const{
		return m_CostSoFar + m_HeuristicCost;
	}
	template<class T>
	void Node<T>::setState(const State state){
		m_State = state;
	}
	template<class T>
	State Node<T>::getState() const{
		return m_State;
	}

}