using System;

using NUnit.Framework;
using NSubstitute;
using GOAP.Planner;

namespace GOAP.Tests.Unit.Planner
{
	[TestFixture]
	class OpenListTests
	{
		[Test]
		public void AddOrRefresh_PassNewNode_AddsTheNode()
		{
			var plannerList = CreateOpenList();
			var node = PlannerUtil.CreateFakeNode();

			plannerList.AddOrRefresh(node);

			Assert.IsTrue(false);
		}

		private static IPlannerList CreateOpenList()
		{
			throw new NotImplementedException();
		}
	}
}
