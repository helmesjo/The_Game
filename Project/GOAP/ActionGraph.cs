using System;
using System.Linq;
using System.Collections.Generic;
using GOAP.Planner;

namespace GOAP
{
	public class ActionGraph : IGraph
	{
		private IGOAPNode[] nodes = new IGOAPNode[0];

		public ActionGraph(params IGOAPNode[] nodes)
		{
			this.nodes = nodes;
        }

		public INode[] BuildPlan(INode endNode)
		{
			var plan = new Stack<INode>();

			while(endNode != null)
			{
				plan.Push(endNode);
				endNode = endNode.Parent;
			}

			return plan.ToArray();
        }

		public float CalculateCost(INode node1, INode node2)
		{
			return 1f;
		}

		public float CalculateEstimatedCost(INode node1, INode node2)
		{
			var goapNode1 = node1 as IGOAPNode;
			var goapNode2 = node2 as IGOAPNode;
			int counter = 0;
			var node2State = goapNode2.State;
			foreach (var property in goapNode1.State.Properties)
			{
				if (!node2State.IsPropertySame(property))
					++counter;
			}
			return counter;
		}

		public INode[] GetNeighbors(INode node)
		{
			var action = node as IGOAPNode;

			var actionsSatisfyingPrecondition = new HashSet<INode>();

			foreach(var action2 in nodes)
				if (action2.SatisfiesPrecondition(action.State))
					actionsSatisfyingPrecondition.Add(action2);

			return actionsSatisfyingPrecondition.ToArray();
		}

		public bool HasNode(INode node)
		{
			return nodes.Contains(node);
		}

		public bool IsDone(INode currentNode, INode endNode)
		{
			var goapNode1 = currentNode as IGOAPNode;
			var goapNode2 = endNode as IGOAPNode;
			return goapNode1.State.doesSatisfy(goapNode2.State);
		}
	}
}