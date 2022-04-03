#include "pch.h"
#include "CppUnitTest.h"
#include "sp.h"
#include <iostream>
#include <vector>
#include "../../pair_dll/pair_dll/dllmain.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PairTest {
	TEST_CLASS(ParamHandlerTest) {
	public:
		TEST_METHOD(testConsoleArgMode)
		{
			class TestCase {
			public:
				int argc;
				char** argv;
				Type stdType;
				char stdSpecializedHead;
				char stdSpecializedTail;
				bool stdAllowCircle;
				bool stdNoSameHead;
				std::string stdFilename;
				TestCase(int argc, char* argv[], Type stdType,
					char stdSpecializedHead, char stdSpecializedTail,
					bool stdAllowCircle, bool stdSameHead, std::string stdFilename) :
					argc(argc), stdType(stdType), stdSpecializedHead(stdSpecializedHead),
					stdSpecializedTail(stdSpecializedTail), stdAllowCircle(stdAllowCircle),
					stdNoSameHead(stdSameHead), stdFilename(stdFilename) {
					this->argv = argv;
				}

			};
			/*
			int argc;
			char* argv[20]; 最多20个参数
			Type stdTypes;
			char stdSpecializedHead;
			char stdSpecializedTail;
			bool stdAllowCircle;
			bool stdSameHead;
			*/
			std::vector<TestCase> testCases;

			// test for -n -w -m -c
			char* argv1[] = { "pair.exe", "-n", "test1.txt" };
			testCases.push_back(TestCase(3, argv1, Type::CHAIN_NUM, 0, 0, false, false, "test1.txt"));
			char* argv2[] = { "pair.exe", "-w", "test1.txt" };
			testCases.push_back(TestCase(3, argv2, Type::WORD_NUM, 0, 0, false, false, "test1.txt"));
			char* argv3[] = { "pair.exe", "-m", "test1.txt" }; // -m 不与其他的共存
			testCases.push_back(TestCase(3, argv3, Type::WORD_NUM, 0, 0, false, true, "test1.txt"));
			char* argv4[] = { "pair.exe", "-c", "test1.txt" };
			testCases.push_back(TestCase(3, argv4, Type::CHAR_NUM, 0, 0, false, false, "test1.txt"));

			// test for -h and -t
			char* argv5[] = { "pair.exe", "-h", "a", "-n", "test1.txt" };
			testCases.push_back(TestCase(5, argv5, Type::CHAIN_NUM, 'a', 0, false, false, "test1.txt"));
			char* argv6[] = { "pair.exe", "-n", "test1.txt", "-t", "q" };
			testCases.push_back(TestCase(5, argv6, Type::CHAIN_NUM, 0, 'q', false, false, "test1.txt"));
			char* argv7[] = { "pair.exe", "-h", "a", "-n", "test1.txt", "-t", "q" };
			testCases.push_back(TestCase(7, argv7, Type::CHAIN_NUM, 'a', 'q', false, false, "test1.txt"));
			char* argv8[] = { "pair.exe", "-h", "a", "-w", "test1.txt", "-t", "q" };
			testCases.push_back(TestCase(7, argv8, Type::WORD_NUM, 'a', 'q', false, false, "test1.txt"));
			char* argv9[] = { "pair.exe", "-h", "a", "-c", "test1.txt", "-t", "q" };
			testCases.push_back(TestCase(7, argv9, Type::CHAR_NUM, 'a', 'q', false, false, "test1.txt"));
			// test for -r
			char* argv10[] = { "pair.exe", "-r", "-n", "test1.txt" };
			testCases.push_back(TestCase(4, argv10, Type::CHAIN_NUM, 0, 0, true, false, "test1.txt"));
			char* argv11[] = { "pair.exe", "-n", "-r", "test1.txt" };
			testCases.push_back(TestCase(4, argv11, Type::CHAIN_NUM, 0, 0, true, false, "test1.txt"));
			char* argv12[] = { "pair.exe", "-r", "-w", "test1.txt" };
			testCases.push_back(TestCase(4, argv12, Type::WORD_NUM, 0, 0, true, false, "test1.txt"));
			char* argv13[] = { "pair.exe", "-w", "-r", "test1.txt" };
			testCases.push_back(TestCase(4, argv13, Type::WORD_NUM, 0, 0, true, false, "test1.txt"));
			char* argv14[] = { "pair.exe", "-r", "-c", "test1.txt" };
			testCases.push_back(TestCase(4, argv14, Type::CHAR_NUM, 0, 0, true, false, "test1.txt"));
			char* argv15[] = { "pair.exe", "-c", "-r", "test1.txt" };
			testCases.push_back(TestCase(4, argv15, Type::CHAR_NUM, 0, 0, true, false, "test1.txt"));
			char* argv155[] = { "pair.exe", "-c", "-r", "test1" };
			testCases.push_back(TestCase(4, argv155, Type::CHAR_NUM, 0, 0, true, false, "test1.txt"));


			// test for exceptions
			char* argv16[] = { "pair.exe", "test1.txt" };
			testCases.push_back(TestCase(2, argv16, Type::CHAR_NUM, 0, 0, true, false, "test1.txt"));
			char* argv17[] = { "pair.exe" };
			testCases.push_back(TestCase(1, argv17, Type::CHAR_NUM, 0, 0, true, false, "test1.txt"));
			char* argv18[] = { "pair.exe", "-n" };
			testCases.push_back(TestCase(2, argv18, Type::CHAR_NUM, 0, 0, true, false, "test1.txt"));


			auto len = testCases.size();
			for (int i = 0; i < len; i++) {
				try {
					auto testCase = testCases[i];
					ParamHandler ph(testCase.argc, testCase.argv);
					Type t = ph.getType();

					bool ans = t == testCase.stdType;
					Assert::IsTrue(ans);
					Assert::AreEqual(ph.specializedHead(), testCase.stdSpecializedHead);
					Assert::AreEqual(ph.specializedTail(), testCase.stdSpecializedTail);
					Assert::AreEqual(ph.allowCircle(), testCase.stdAllowCircle);
					Assert::AreEqual(ph.noSameHead(), testCase.stdNoSameHead);
					Assert::AreEqual(ph.getFileName(), testCase.stdFilename);
				}
				catch (ParamException e) {
					std::cout << "Catched ParamException in " << i;
				}
				catch (FileIllegalException e) {

				}
				catch (ExistsLoopException e) {

				}
			}
		}
		TEST_METHOD(testDirectArgMode) {
			class DirectArgModeTestCase {
			public:
				Type type;
				char head;
				char tail;
				bool enable_loop;
				bool noSameHead;
				DirectArgModeTestCase(Type type, char head, char tail, bool enable_loop, bool noSameHead) :
					type(type), head(head), tail(tail), enable_loop(enable_loop), noSameHead(noSameHead) {}
			};
			std::vector<DirectArgModeTestCase> testCases;
			testCases.push_back(DirectArgModeTestCase(Type::CHAIN_NUM, 'q', 'a', true, true));
			testCases.push_back(DirectArgModeTestCase(Type::WORD_NUM, 0, 0, true, true));
			testCases.push_back(DirectArgModeTestCase(Type::CHAR_NUM, 0, 0, false, false));

			for (auto testCase : testCases) {
				ParamHandler p(testCase.type, testCase.head, testCase.tail, testCase.enable_loop, testCase.noSameHead);
				if (p.getType() != testCase.type) {
					Assert::IsTrue(false);
				}
				Assert::AreEqual(p.specializedHead(), testCase.head);
				Assert::AreEqual(p.specializedTail(), testCase.tail);
				Assert::AreEqual(p.allowCircle(), testCase.enable_loop);
				Assert::AreEqual(p.noSameHead(), testCase.noSameHead);
			}

		}
	};

	TEST_CLASS(InputHandlerTest) {
	public:
		TEST_METHOD(testExtractWords) {
			class ExtractWordsTestCase {
			public:
				std::string input;
				std::vector<std::string> stdOutput;
				ExtractWordsTestCase(std::string input, std::vector<std::string> stdOutput) :
					input(input), stdOutput(stdOutput) {}

			};

			InputsHandler ih;
			std::vector<ExtractWordsTestCase> testCases;
			testCases.push_back(ExtractWordsTestCase("wo shi yi ge sha bi",
				{ "wo", "shi", "yi", "ge", "sha", "bi" }));

			testCases.push_back(ExtractWordsTestCase("wo",
				{ "wo" }));
			testCases.push_back(ExtractWordsTestCase("a",
				{}));
			testCases.push_back(ExtractWordsTestCase("a a a",
				{}));
			testCases.push_back(ExtractWordsTestCase("a&a&a&aa",
				{ "aa" }));
			testCases.push_back(ExtractWordsTestCase("wo&shi$yi/ge*sha@bi",
				{ "wo", "shi", "yi", "ge", "sha", "bi" }));
			testCases.push_back(ExtractWordsTestCase("wo&a&shi*s*yi0i0ge sha bi",
				{ "wo", "shi", "yi", "ge", "sha", "bi" }));
			testCases.push_back(ExtractWordsTestCase("Wo sHi yI GE sha Bi",
				{ "wo", "shi", "yi", "ge", "sha", "bi" }));


			auto len = testCases.size();
			for (int i = 0; i < len; i++) {
				auto testCase = testCases[i];
				auto output = ih.extractWords(testCase.input);

				auto outputLen = output.size();
				Assert::AreEqual(outputLen, testCase.stdOutput.size());
				for (int j = 0; j < outputLen; j++) {
					Assert::IsTrue(output[j] == testCase.stdOutput[j]);
				}
			}
		}

		TEST_METHOD(testHandle) {
			class HanderTestCase {
			public:
				std::string filename;
				std::vector<std::string> stdOutput;
				HanderTestCase(std::string filename, std::vector<std::string> stdOutput) :
					filename(filename), stdOutput(stdOutput) {}
			};
			std::vector<HanderTestCase> testCases;
			testCases.push_back(HanderTestCase("test.txt", { "woox", "xoom", "moot", "tooq", "hjjk", "klla", "assd", "dffg" }));

			InputsHandler ih;

			for (auto testCase : testCases) {
				auto output = ih.handle("..\\..\\PairTest\\" + testCase.filename);
				size_t len = output.size();
				Assert::AreEqual(len, testCase.stdOutput.size());
				for (size_t i = 0; i < len; i++) {
					Assert::IsTrue(output[i].compare(testCase.stdOutput[i]) == 0);
				}
			}
		}
	};

	TEST_CLASS(WordListHandlerTest) {
	public:
		TEST_METHOD(testGenChainsAll) {
			class GenChainsAllTestCase {
			public:
				ParamHandler* ph;
				std::vector<Word> words;
				int stdChainNum;
				GenChainsAllTestCase(ParamHandler* ph, std::vector<Word> words, int stdChainNum) :
					ph(ph), words(words), stdChainNum(stdChainNum) {}
			};
			std::vector<GenChainsAllTestCase> testCases;
			char* argv1[] = { "pair.exe", "-n", "test1.txt" };
		}

	};

	TEST_CLASS(DLLTest) {
	public:
		TEST_METHOD(testGenChainsAllPython) {
			class GenChainsAllPythonTestCase {
			public:
				char* words;
				std::string stdOutput;
				GenChainsAllPythonTestCase(char* words, std::string stdOutput) 
					: words(words), stdOutput(stdOutput) {}
			};

			char* words = "hello world!Ops& stupid!a";
			char* result = new char[200000];
			char* error_msg = new char[200000];
			int size = gen_chains_all_python(words, &result, &error_msg);
			Assert::IsTrue(size != 0);
		}
		TEST_METHOD(testGenChainWordPython) {
			char* words = "Element Heaven Table Teach Talk";
			char* result = new char[200000];
			char* error_msg = new char[2000];
			int size = gen_chain_word_python(words, &result, 0, 0, false, &error_msg);
			Assert::IsTrue(size != 0);
		}
		TEST_METHOD(testGenChainWordUniquePython) {
			
		}
		TEST_METHOD(testGenChainCharPython) {
			
		}
		TEST_METHOD(testGenChainsAll) {
			class GenChainsAllTestCase {
			public:
				char* words[100];
				int len;
				int stdChainNum;
				GenChainsAllTestCase(char* words[], int len, int stdChainNum)
					: len(len), stdChainNum(stdChainNum) {
					for (int i = 0; i < len; i++) {
						this->words[i] = words[i];
					}
				}
			};
			std::vector<GenChainsAllTestCase> testCases;
			char* words1[] = { "woo", "oom", "moon", "noox" };
			testCases.push_back(GenChainsAllTestCase(words1, 4, 6));
			char* words2[] = { "Algebra", "Apple", "Zoo", "Elephant", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf", "Trick", "Pseudopseudohypoparathyroidism"};
			testCases.push_back(GenChainsAllTestCase(words2, 12, 8));
			char* words3[] = { "woo"};
			testCases.push_back(GenChainsAllTestCase(words3, 1, 0));
			char* words4[1] = {};
			testCases.push_back(GenChainsAllTestCase(words4, 0, 0));

			auto result = new char* [10000];
			for (auto& testCase : testCases) {
				int chainNum = gen_chains_all(testCase.words, testCase.len, result);
				Assert::AreEqual(chainNum, testCase.stdChainNum);
			}
		}

		TEST_METHOD(testGenChainWord) {
			class GenChainWordTestCase {
			public:
				char* words[100];
				int len;
				char head;
				char tail;
				bool enable_loop;
				int stdChainNum;
				GenChainWordTestCase(char* words[], int len, char head, char tail, bool enable_loop, int stdChainNum)
					: len(len), head(head), tail(tail), enable_loop(enable_loop), stdChainNum(stdChainNum) {
					for (int i = 0; i < len; i++) {
						this->words[i] = words[i];
					}
				}
			};
			std::vector<GenChainWordTestCase> testCases;
			char* words3[] = { "woo" };
			testCases.push_back(GenChainWordTestCase(words3, 1, 0, 0, false, 0));
			char* words1[] = { "woo", "oom", "moon", "noox" };
			testCases.push_back(GenChainWordTestCase(words1, 4, 0, 0, false, 4));
			testCases.push_back(GenChainWordTestCase(words1, 4, 'w', 0, false, 4));
			testCases.push_back(GenChainWordTestCase(words1, 4, 'o', 0, false, 3));
			testCases.push_back(GenChainWordTestCase(words1, 4, 'n', 0, false, 0));
			testCases.push_back(GenChainWordTestCase(words1, 4, 0, 'x', false, 4));
			testCases.push_back(GenChainWordTestCase(words1, 4, 0, 'n', false, 3));
			testCases.push_back(GenChainWordTestCase(words1, 4, 0, 'o', false, 0));
			char* words2[] = { "Algebra", "Apple", "Zoo", "Elephant", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf", "Trick", "Pseudopseudohypoparathyroidism" };
			testCases.push_back(GenChainWordTestCase(words2, 12, 0, 0, false, 4));
			
			char* words4[1] = {};
			testCases.push_back(GenChainWordTestCase(words4, 0, 0, 0, false, 0));
			char* words5[] = { "woo", "oom", "moow" };
			testCases.push_back(GenChainWordTestCase(words5, 3, 0, 0, false, -3));
			testCases.push_back(GenChainWordTestCase(words5, 3, 0, 0, true, 3));
			testCases.push_back(GenChainWordTestCase(words5, 3, 'w', 0, true, 3));
			testCases.push_back(GenChainWordTestCase(words5, 3, 'o', 0, true, 3));
			testCases.push_back(GenChainWordTestCase(words5, 3, 'm', 0, true, 3));
			testCases.push_back(GenChainWordTestCase(words5, 3, 0, 'o', true, 3));
			testCases.push_back(GenChainWordTestCase(words5, 3, 0, 'm', true, 3));
			testCases.push_back(GenChainWordTestCase(words5, 3, 0, 'w', true, 3));

			if (true) {
				int i = 0;
				i++;
			}
			auto result = new char* [10000];
			for (auto& testCase : testCases) {
				int chainNum = gen_chain_word(testCase.words, testCase.len, result, testCase.head, testCase.tail, testCase.enable_loop);
				Assert::AreEqual(chainNum, testCase.stdChainNum);
			}
		}

		TEST_METHOD(testGenChainWordUnique) {
			class GenChainWordUniqueTestCase {
			public:
				char* words[100];
				int len;
				int stdChainNum;
				GenChainWordUniqueTestCase(char* words[], int len, int stdChainNum)
					: len(len), stdChainNum(stdChainNum) {
					for (int i = 0; i < len; i++) {
						this->words[i] = words[i];
					}
				}
			};
			std::vector<GenChainWordUniqueTestCase> testCases;
			char* words1[] = { "woo", "oom", "moon", "noox" };
			testCases.push_back(GenChainWordUniqueTestCase(words1, 4, 4));
			char* words2[] = { "Algebra", "Apple", "Zoo", "Elephant", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf", "Trick", "Pseudopseudohypoparathyroidism" };
			testCases.push_back(GenChainWordUniqueTestCase(words2, 12, 3));
			char* words3[] = { "woo" };
			testCases.push_back(GenChainWordUniqueTestCase(words3, 1, 0));
			char* words4[1] = {};
			testCases.push_back(GenChainWordUniqueTestCase(words4, 0, 0));

			auto result = new char* [10000];
			for (auto& testCase : testCases) {
				int chainNum = gen_chain_word_unique(testCase.words, testCase.len, result);
				Assert::AreEqual(chainNum, testCase.stdChainNum);
			}
		}

		TEST_METHOD(testGenChainChar) {
			class GenChainCharTestCase {
			public:
				char* words[100];
				int len;
				char head;
				char tail;
				bool enable_loop;
				int stdChainNum;
				GenChainCharTestCase(char* words[], int len, char head, char tail, bool enable_loop, int stdChainNum)
					: len(len), head(head), tail(tail), enable_loop(enable_loop), stdChainNum(stdChainNum) {
					for (int i = 0; i < len; i++) {
						this->words[i] = words[i];
					}
				}
			};
			std::vector<GenChainCharTestCase> testCases;
			char* words3[] = { "woo" };
			testCases.push_back(GenChainCharTestCase(words3, 1, 0, 0, false, 0));
			char* words1[] = { "woo", "oom", "moon", "noox" };
			testCases.push_back(GenChainCharTestCase(words1, 4, 0, 0, false, 4));
			testCases.push_back(GenChainCharTestCase(words1, 4, 'w', 0, false, 4));
			testCases.push_back(GenChainCharTestCase(words1, 4, 'o', 0, false, 3));
			testCases.push_back(GenChainCharTestCase(words1, 4, 'n', 0, false, 0));
			testCases.push_back(GenChainCharTestCase(words1, 4, 0, 'x', false, 4));
			testCases.push_back(GenChainCharTestCase(words1, 4, 0, 'n', false, 3));
			testCases.push_back(GenChainCharTestCase(words1, 4, 0, 'o', false, 0));
			char* words2[] = { "Algebra", "Apple", "Zoo", "Elephant", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf", "Trick", "Pdsxcvbhjkloiuytfdcvbnjklsm" };
			testCases.push_back(GenChainCharTestCase(words2, 12, 0, 0, false, 2));

			char* words4[1] = {};
			testCases.push_back(GenChainCharTestCase(words4, 0, 0, 0, false, 0));
			char* words5[] = { "woo", "oom", "moow" };
			testCases.push_back(GenChainCharTestCase(words5, 3, 0, 0, false, -3));
			testCases.push_back(GenChainCharTestCase(words5, 3, 0, 0, true, 3));
			testCases.push_back(GenChainCharTestCase(words5, 3, 'w', 0, true, 3));
			testCases.push_back(GenChainCharTestCase(words5, 3, 'o', 0, true, 3));
			testCases.push_back(GenChainCharTestCase(words5, 3, 'm', 0, true, 3));
			testCases.push_back(GenChainCharTestCase(words5, 3, 0, 'o', true, 3));
			testCases.push_back(GenChainCharTestCase(words5, 3, 0, 'm', true, 3));
			testCases.push_back(GenChainCharTestCase(words5, 3, 0, 'w', true, 3));

			if (true) {
				int i = 0;
				i++;
			}
			auto result = new char* [10000];
			for (auto& testCase : testCases) {
				int chainNum = gen_chain_char(testCase.words, testCase.len, result, testCase.head, testCase.tail, testCase.enable_loop);
				Assert::AreEqual(chainNum, testCase.stdChainNum);
			}
		}
	};
}
