﻿using System.Collections;

namespace GOAP.Planner
{
	public interface IPlannerList
	{
		void AddOrUpdate(INode node);
		bool HasNext();
		INode PopNext();
		bool HasNode(INode node);
		void Clear();
	}
}