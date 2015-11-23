using System;
using System.Collections.Generic;

using C5;

namespace GOAP.Planner
{
	public class OpenList : IPlannerList
	{
		private class NodeComparer : IComparer<INode>
		{
			public int Compare(INode x, INode y)
			{
				if (x.EstimatedTotalCost == y.EstimatedTotalCost)
					return 0;
				if (x.EstimatedTotalCost < y.EstimatedTotalCost)
					return -1;
				else
					return 1;
			}
		}

		IntervalHeap<INode> nodes = new IntervalHeap<INode>(new NodeComparer());

		public void Add(INode node)
		{
			nodes.Add(node);
        }

		public bool HasNext()
		{
			return nodes.Count > 0;
		}

		public INode PopNext()
		{
			return nodes.DeleteMin();
		}

		public bool HasNode(INode node)
		{
			return nodes.Exists(n => n.Equals(node));
		}
	}
}