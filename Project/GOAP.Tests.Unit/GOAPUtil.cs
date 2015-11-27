using System;

using NSubstitute;

namespace GOAP.Tests.Unit.GOAP
{
	internal static class GOAPUtil
	{
		internal static IAction CreateFakeAction(params IWorldState[] preconditions)
		{
			var action = Substitute.For<IAction>();
			action.Parent = null;
			action.Precondition = preconditions;
            return action;
		}

		internal static IWorldState CreateFakeWorldState()
		{
			throw new NotImplementedException();
		}
	}
}