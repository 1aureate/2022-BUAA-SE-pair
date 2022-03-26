#include "pch.h"
#include "CppUnitTest.h"
#include "sp.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PairTest
{
	TEST_CLASS(PairTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int argc = 3;
			char* argv[] = { "pair.exe", "-n", "test1.txt" };
			ParamHandler paramHandler(argc, argv);
			Type t = paramHandler.getType();
			bool ans = t == Type::CHAIN_NUM;
			Assert::IsTrue(ans);
			Assert::IsFalse(paramHandler.ifSpecializedHead() != -1);
			Assert::IsFalse(paramHandler.ifSpecializedTail() != -1);
			Assert::IsFalse(paramHandler.allowCircle());
			Assert::IsFalse(paramHandler.sameHead());
		}
	};
}
