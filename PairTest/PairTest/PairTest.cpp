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
			bool stdNoSameHead;
			ParamHandlerTestCase(int argc, char* argv[], Type stdType,
				char stdSpecializedHead, char stdSpecializedTail,
				bool stdAllowCircle, bool stdSameHead) :
				argc(argc), stdType(stdType), stdSpecializedHead(stdSpecializedHead),
				stdSpecializedTail(stdSpecializedTail), stdAllowCircle(stdAllowCircle),
				stdNoSameHead(stdSameHead) {
				this->argv = argv;
			}

		};
		TEST_METHOD(TestParamHandler)
		{
			/*
			int argc;
			char* argv[20]; 最多20个参数
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
			char* argv3[] = { "pair.exe", "-m", "test1.txt" }; // -m 不与其他的共存
			testCases.push_back(ParamHandlerTestCase(3, argv3, Type::WORD_NUM, -1, -1, false, true));
			char* argv4[] = { "pair.exe", "-c", "test1.txt" };
			testCases.push_back(ParamHandlerTestCase(3, argv4, Type::CHAR_NUM, -1, -1, false, false));

			// test for -h and -t
			char* argv5[] = { "pair.exe", "-h", "a", "-n", "test1.txt" };
			testCases.push_back(ParamHandlerTestCase(5, argv5, Type::CHAIN_NUM, 'a', -1, false, false));
			char* argv6[] = { "pair.exe", "-n", "test1.txt", "-t", "q" };
			testCases.push_back(ParamHandlerTestCase(5, argv6, Type::CHAIN_NUM, -1, 'q', false, false));
			char* argv7[] = { "pair.exe", "-h", "a", "-n", "test1.txt", "-t", "q" };
			testCases.push_back(ParamHandlerTestCase(7, argv7, Type::CHAIN_NUM, 'a', 'q', false, false));
			char* argv8[] = { "pair.exe", "-h", "a", "-w", "test1.txt", "-t", "q" };
			testCases.push_back(ParamHandlerTestCase(7, argv8, Type::WORD_NUM, 'a', 'q', false, false));
			char* argv9[] = { "pair.exe", "-h", "a", "-c", "test1.txt", "-t", "q" };
			testCases.push_back(ParamHandlerTestCase(7, argv9, Type::CHAR_NUM, 'a', 'q', false, false));

			// test for -r
			char* argv10[] = { "pair.exe", "-r", "-n", "test1.txt" };
			testCases.push_back(ParamHandlerTestCase(4, argv10, Type::CHAIN_NUM, -1, -1, true, false));
			char* argv11[] = { "pair.exe", "-n", "-r", "test1.txt" };
			testCases.push_back(ParamHandlerTestCase(4, argv11, Type::CHAIN_NUM, -1, -1, true, false));
			char* argv12[] = { "pair.exe", "-r", "-w", "test1.txt" };
			testCases.push_back(ParamHandlerTestCase(4, argv12, Type::WORD_NUM, -1, -1, true, false));
			char* argv13[] = { "pair.exe", "-w", "-r", "test1.txt" };
			testCases.push_back(ParamHandlerTestCase(4, argv13, Type::WORD_NUM, -1, -1, true, false));
			char* argv14[] = { "pair.exe", "-r", "-c", "test1.txt" };
			testCases.push_back(ParamHandlerTestCase(4, argv14, Type::CHAR_NUM, -1, -1, true, false));
			char* argv15[] = { "pair.exe", "-c", "-r", "test1.txt" };
			testCases.push_back(ParamHandlerTestCase(4, argv15, Type::CHAR_NUM, -1, -1, true, false));


			// test for exceptions
			char* argv16[] = { "pair.exe", "test1.txt" };
			testCases.push_back(ParamHandlerTestCase(2, argv16, Type::CHAR_NUM, -1, -1, true, false));
			char* argv17[] = { "pair.exe" };
			testCases.push_back(ParamHandlerTestCase(1, argv17, Type::CHAR_NUM, -1, -1, true, false));
			char* argv18[] = { "pair.exe", "-n" };
			testCases.push_back(ParamHandlerTestCase(2, argv18, Type::CHAR_NUM, -1, -1, true, false));


			auto len = testCases.size();
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
					Assert::AreEqual(ph.noSameHead(), testCase.stdNoSameHead);
				}
				catch (ParamException e) {
					std::cout << "Catched ParamException in " << i;
				}
			}
		}

		TEST_METHOD(TestInputHandler) {
			class InputHandlerTestCase {
			public:
				std::string input;
				std::vector<std::string> stdOutput;
				InputHandlerTestCase(std::string input, std::vector<std::string> stdOutput) : 
					input(input), stdOutput(stdOutput) {} 
				
			};

			InputsHandler ih;
			std::vector<InputHandlerTestCase> testCases;

			testCases.push_back(InputHandlerTestCase("wo shi yi ge sha bi", 
				{"wo", "shi", "yi", "ge", "sha", "bi"}));
			testCases.push_back(InputHandlerTestCase("wo",
				{ "wo" }));
			testCases.push_back(InputHandlerTestCase("",
				{}));
			testCases.push_back(InputHandlerTestCase("wo&shi$yi/ge*sha@bi",
				{ "wo", "shi", "yi", "ge", "sha", "bi" }));
			testCases.push_back(InputHandlerTestCase("wo&a&shi*s*yi0i0ge sha bi",
				{ "wo", "shi", "yi", "ge", "sha", "bi" }));
			testCases.push_back(InputHandlerTestCase("Wo sHi yI GE sha Bi",
				{ "wo", "shi", "yi", "ge", "sha", "bi" }));

			auto len = testCases.size();
			for (int i = 0; i < len; i++) {
				auto testCase = testCases[i];
				auto output = ih.extractWords(testCase.input);
				
				auto outputLen = output.size();
				if (outputLen != testCase.stdOutput.size()) {
					int forDebug;
					forDebug = 100;
				}
				Assert::AreEqual(outputLen, testCase.stdOutput.size());
				for (int j = 0; j < outputLen; j++) {
					if (output[j].content != testCase.stdOutput[j]) {
						int forDebug;
						forDebug = 100;
					}
					Assert::IsTrue(output[j].content == testCase.stdOutput[j]);
				}
			}
		}
	};
}
