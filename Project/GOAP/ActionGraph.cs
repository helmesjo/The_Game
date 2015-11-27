using System;
using System.Linq;
using System.Collections.Generic;
using GOAP.Planner;

namespace GOAP
{
	public class ActionGraph : IGraph
	{
		private IAction[] actions = new IAction[0];

		public ActionGraph(params IAction[] actions)
		{
			this.actions = actions;
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

		public float CalculateCost(INode action1, INode action2)
		{
			return 1f;
		}

		public float CalculateEstimatedCost(INode action1, INode action2)
		{
			throw new NotImplementedException();
		}

		public INode[] GetNeighbors(INode node)
		{
			var action = node as IAction;

			var actionsSatisfyingPrecondition = new HashSet<INode>();

			foreach(var action2 in actions)
				if (action2.SatisfiesPrecondition(action.Precondition))
					actionsSatisfyingPrecondition.Add(action2);

			return actionsSatisfyingPrecondition.ToArray();
		}

		public bool HasNode(INode node)
		{
			return actions.Contains(node);
		}

		public bool IsDone(INode currentNode, INode endNode)
		{
			throw new NotImplementedException();
		}
	}
}