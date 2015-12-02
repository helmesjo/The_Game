using System;

using NSubstitute;

namespace GOAP.Tests.Unit.GOAP
{
	internal static class GOAPUtil
	{
		internal static IGOAPNode CreateFakeNode()
		{
			var state = CreateFakeWorldState();
			var action = CreateFakeAction();
			return CreateFakeNode(state, action);
		}

		internal static IAction CreateFakeAction()
		{
			var action = Substitute.For<IAction>();
			return action;
		}

		internal static IGOAPNode CreateFakeNode(IWorldState state)
		{
			var action = CreateFakeAction();
			return CreateFakeNode(state, action);
		}
		internal static IGOAPNode CreateFakeNode(IWorldState state, IAction action)
		{
			var node = Substitute.For<IGOAPNode>();
			node.Parent.Returns(x=>null);
			node.State.Returns(state);
            return node;
		}

		internal static IWorldState CreateFakeWorldState(params IWorldStateProperty[] properties)
		{
			var state = Substitute.For<IWorldState>();
			state.Properties.Returns(properties);
			state.IsPropertySame(Arg.Any<IWorldStateProperty>()).Returns(info => {
				var prop = info.Arg<IWorldStateProperty>();
				foreach (var property in state.Properties)
					if (property.IsSame(prop))
						return true;
				return false;
			});
			state.doesSatisfy(Arg.Any<IWorldState>()).Returns(info => {
				var passedState = info.Arg<IWorldState>();
				foreach (var prop in state.Properties)
					if (!passedState.IsPropertySame(prop))
						return false;
				return true;
			});
			return state;
		}

		internal static IWorldStateProperty CreateFakeStateProperty(string key, bool value)
		{
			var property = Substitute.For<IWorldStateProperty>();
			property.Key.Returns(key);
			property.Value.Returns(value);
			property.IsSame(Arg.Any<IWorldStateProperty>()).Returns(p => {
				var arg = p.Arg<IWorldStateProperty>();
				return property.Key == arg.Key && property.Value == arg.Value;
			});
			return property;
		}
	}
}