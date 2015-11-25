using System;

using NSubstitute;

namespace GOAP.Tests.Unit.GOAP
{
	internal static class GOAPUtil
	{
		internal static IAction CreateFakeAction()
		{
			var action = Substitute.For<IAction>();
			action.Parent = null;
            return action;
		}
	}
}