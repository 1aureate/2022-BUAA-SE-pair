#include "pch.h"
#include "CppUnitTest.h"
#include "sp.h"
#include <iostream>
#include <vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PairTest
{
	TEST_CLASS(PairTest)
	{
	public:
		class ParamHandlerTestCase {
		public:
			int argc;
			char** argv; 
			Type stdType;
			char stdSpecializedHead;
			char stdSpecializedTail;
			bool stdAllowCircle;
			bool stdSameHead;
			ParamHandlerTestCase(int argc, char* argv[], Type stdType,
				char stdSpecializedHead, char stdSpecializedTail,
				bool stdAllowCircle, bool stdSameHead) :
				argc(argc), stdType(stdType), stdSpecializedHead(stdSpecializedHead),
				stdSpecializedTail(stdSpecializedTail), stdAllowCircle(stdAllowCircle),
				stdSameHead(stdSameHead) {
				this->argv = argv;
			}

		};
		TEST_METHOD(TestParamHandler)
		{
			/*
			int argc;
			char* argv[20]; // ���20������
			Type stdTypes;
			char stdSpecializedHead;
			char stdSpecializedTail;
			bool stdAllowCircle;
			bool stdSameHead;
			*/
			std::vector<ParamHandlerTestCase> testCases;

			// test for -n -w -m -c
			char* argv1[] = { "pair.exe", "-n", "test1.txt" };
			testCases.push_back(ParamHandlerTestCase(3, argv1, Type::CHAIN_NUM, -1, -1, false, false));

			char* argv2[] = { "pair.exe", "-w", "test2.txt" };
			testCases.push_back(ParamHandlerTestCase(3, argv2, Type::WORD_NUM, -1, -1, false, false));

			char* argv3[] = { "pair.exe", "-m", "test1.txt" }; // -m ֻ�ܵ�������
			testCases.push_back(ParamHandlerTestCase(3, argv3, Type::WORD_NUM, -1, -1, false, true));

			char* argv4[] = { "pair.exe", "-c", "test1.txt" };
			testCases.push_back(ParamHandlerTestCase(3, argv4, Type::CHAR_NUM, -1, -1, false, false));

			// test for -h and -t
			char* argv5[] = { "pair.exe", "-h", "w", "-n", "test1.txt" };
			testCases.push_back(ParamHandlerTestCase(5, argv5, Type::CHAIN_NUM, 'w', -1, false, false));

			char* argv6[] = { "pair.exe", "-n", "test1.txt", "-t", "q" };
			testCases.push_back(ParamHandlerTestCase(5, argv6, Type::CHAIN_NUM, -1, 'q', false, false));

			char* argv7[] = { "pair.exe", "-h", "w", "-n", "test1.txt", "-t", "q" };
			testCases.push_back(ParamHandlerTestCase(7, argv7, Type::CHAIN_NUM, 'w', 'q', false, false));

			char* argv8[] = { "pair.exe", "-h", "w", "-w", "test1.txt", "-t", "q" };
			testCases.push_back(ParamHandlerTestCase(7, argv8, Type::WORD_NUM, 'w', 'q', false, false));

			char* argv9[] = { "pair.exe", "-h", "w", "-c", "test1.txt", "-t", "q" };
			testCases.push_back(ParamHandlerTestCase(7, argv9, Type::CHAR_NUM, 'w', 'q', false, false));

			// test for -r




			int len = testCases.size();

			for (int i = 0; i < len; i++) {
				try {
					auto testCase = testCases[i];
					ParamHandler ph(testCase.argc, testCase.argv);
					Type t = ph.getType();

					bool ans = t == testCase.stdType;
					Assert::IsTrue(ans);
					Assert::AreEqual(ph.ifSpecializedHead(), testCase.stdSpecializedHead);
					Assert::AreEqual(ph.ifSpecializedTail(), testCase.stdSpecializedTail);
					Assert::AreEqual(ph.allowCircle(), testCase.stdAllowCircle);
					Assert::AreEqual(ph.sameHead(), testCase.stdSameHead);
				}
				catch (ParamException e) {
					std::cout << "Catched ParamException in " << i;
				}
			}

			
			/*#define TESTCASE_NUM 5
			
			char* argv[TESTCASE_NUM][100] = {
				{ "pair.exe", "-n", "test1.txt" }, 
				{"pair.exe", "-m", "test2.txt"},
				{"pair.exe", ""}
			};
			int argc[TESTCASE_NUM] = { 3 };

			Type stdTypes[TESTCASE_NUM] = { Type::CHAIN_NUM };
			char stdSpecializedHead[TESTCASE_NUM] = { -1 };
			char stdSpecializedTail[TESTCASE_NUM] = { -1 };
			bool stdAllowCircle[TESTCASE_NUM] = { false };
			bool stdSameHead[TESTCASE_NUM] = { false };

			for (int i = 0; i < TESTCASE_NUM; i++) {
				try {
					ParamHandler ph(argc[i], argv[i]);
					Type t = ph.getType();

					bool ans = t == stdTypes[i];
					Assert::IsTrue(ans);
					Assert::AreEqual(ph.ifSpecializedHead(), stdSpecializedHead[i]);
					Assert::AreEqual(ph.ifSpecializedTail(), stdSpecializedTail[i]);
					Assert::AreEqual(ph.allowCircle(), stdAllowCircle[i]);
					Assert::AreEqual(ph.sameHead(), stdSameHead[i]);
				}
				catch (ParamException e) {
					std::cout << "Catched ParamException in " << i;
				}
			}*/
		}
	};
}
