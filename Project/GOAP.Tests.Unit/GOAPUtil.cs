using System;

using NSubstitute;

namespace GOAP.Tests.Unit.GOAP
{
	internal static class GOAPUtil
	{
		internal static IGOAPNode CreateFakeNode()
		{
			var state = CreateFakeWorldState();
			return CreateFakeNode(state);
		}
		internal static IGOAPNode CreateFakeNode(IWorldState state)
		{
			var action = Substitute.For<IGOAPNode>();
			action.Parent.Returns(x=>null);
			action.State.Returns(state);
            return action;
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