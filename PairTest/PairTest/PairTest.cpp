#include "pch.h"
#include "PairTest.h"
#include "CppUnitTest.h"
#include "sp.h"
#include <iostream>
#include <vector>

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
			std::vector<TestCase> testCases;

			char* argv1555[] = { "pair.exe", "-c", "-r", "test1" };
			testCases.push_back(TestCase(4, argv1555, Type::CHAR_NUM, 0, 0, true, false, "test1.txt"));
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
				int stdChainNum;
				GenChainsAllPythonTestCase(char* words, int stdChainNum)
					: stdChainNum(stdChainNum) {
					this->words = words;
				}
			};
			std::vector<GenChainsAllPythonTestCase> testCases;
			char words1[] = { "woo oom moon noox" };
			testCases.push_back(GenChainsAllPythonTestCase(words1, 6));
			char words2[] = { "Algebra Apple Zoo Elephant Elephant Under Fox Dog Moon Leaf Trick Pseudopseudohypoparathyroidism" };
			testCases.push_back(GenChainsAllPythonTestCase(words2, 8));
			char words3[] = { "woo" };
			testCases.push_back(GenChainsAllPythonTestCase(words3, 0));
			char words4[1] = {};
			testCases.push_back(GenChainsAllPythonTestCase(words4, 0));

			char* result = new char[200000];
			char* error_msg = new char[2000];
			for (auto& testCase : testCases) {
				int chainNum = gen_chains_all_python(testCase.words, &result, &error_msg);
				Assert::AreEqual(chainNum, testCase.stdChainNum);
			}
		}
		TEST_METHOD(testGenChainWordPython) {
			class GenChainWordPythonTestCase {

			public:
				char* words;
				char head;
				char tail;
				bool enable_loop;
				int stdChainNum;
				GenChainWordPythonTestCase(char* words, char head, char tail, bool enable_loop, int stdChainNum)
					: head(head), tail(tail), enable_loop(enable_loop), stdChainNum(stdChainNum) {
					this->words = words;
				}
			};
			std::vector<GenChainWordPythonTestCase> testCases;
			char* words3 = { "woo" };
			testCases.push_back(GenChainWordPythonTestCase(words3, 0, 0, false, 0));
			char* words1 = { "woo oom moon noox" };
			testCases.push_back(GenChainWordPythonTestCase(words1, 0, 0, false, 4));
			testCases.push_back(GenChainWordPythonTestCase(words1, 'w', 0, false, 4));
			testCases.push_back(GenChainWordPythonTestCase(words1, 'o', 0, false, 3));
			testCases.push_back(GenChainWordPythonTestCase(words1, 'n', 0, false, 0));
			testCases.push_back(GenChainWordPythonTestCase(words1, 0, 'x', false, 4));
			testCases.push_back(GenChainWordPythonTestCase(words1, 0, 'n', false, 3));
			testCases.push_back(GenChainWordPythonTestCase(words1, 0, 'o', false, 0));
			char words2[] = { "Algebra Apple Zoo Elephant Elephant Under Fox Dog Moon Leaf Trick Pseudopseudohypoparathyroidism" };
			testCases.push_back(GenChainWordPythonTestCase(words2, 0, 0, false, 4));

			char* words4 = {"\0"};
			testCases.push_back(GenChainWordPythonTestCase(words4, 0, 0, false, 0));
			char* words5 = { "woo oom moow" };
			testCases.push_back(GenChainWordPythonTestCase(words5, 0, 0, false, -3));
			testCases.push_back(GenChainWordPythonTestCase(words5, 0, 0, true, 3));
			testCases.push_back(GenChainWordPythonTestCase(words5, 'w', 0, true, 3));
			testCases.push_back(GenChainWordPythonTestCase(words5, 'o', 0, true, 3));
			testCases.push_back(GenChainWordPythonTestCase(words5, 'm', 0, true, 3));
			testCases.push_back(GenChainWordPythonTestCase(words5, 0, 'o', true, 3));
			testCases.push_back(GenChainWordPythonTestCase(words5, 0, 'm', true, 3));
			testCases.push_back(GenChainWordPythonTestCase(words5, 0, 'w', true, 3));
			testCases.push_back(GenChainWordPythonTestCase(words5, 1, 'w', false, -4));
			testCases.push_back(GenChainWordPythonTestCase(words5, 0, 2, false, -4));


			char* result = new char[200000];
			char* error_msg = new char[2000];
			for (auto& testCase : testCases) {
				int chainNum = gen_chain_word_python(testCase.words, &result, testCase.head,
					testCase.tail, testCase.enable_loop, &error_msg);
				Assert::AreEqual(chainNum, testCase.stdChainNum);
			}
		}
		TEST_METHOD(testGenChainWordUniquePython) {
			class GenChainWordUniquePythonTestCase {
			public:
				char* words;
				int stdChainNum;
				GenChainWordUniquePythonTestCase(char* words, int stdChainNum)
					: stdChainNum(stdChainNum) {
					this->words = words;
				}
			};
			std::vector<GenChainWordUniquePythonTestCase> testCases;
			char words1[] = { "woo oom moon noox" };
			testCases.push_back(GenChainWordUniquePythonTestCase(words1, 4));
			char words2[] = { "Algebra Apple Zoo Elephant Elephant Under Fox Dog Moon Leaf Trick Pseudopseudohypoparathyroidism" };
			testCases.push_back(GenChainWordUniquePythonTestCase(words2, 3));
			char words3[] = { "woo" };
			testCases.push_back(GenChainWordUniquePythonTestCase(words3, 0));
			char words4[1] = {};
			testCases.push_back(GenChainWordUniquePythonTestCase(words4, 0));

			char* result = new char[200000];
			char* error_msg = new char[2000];
			for (auto& testCase : testCases) {
				int chainNum = gen_chain_word_unique_python(testCase.words, &result, &error_msg);
				Assert::AreEqual(chainNum, testCase.stdChainNum);
			}
		}
		TEST_METHOD(testGenChainCharPython) {
			class GenChainCharPythonTestCase {
			public:
				char* words;
				char head;
				char tail;
				bool enable_loop;
				int stdChainNum;
				GenChainCharPythonTestCase(char* words, char head, char tail, bool enable_loop, int stdChainNum)
					: head(head), tail(tail), enable_loop(enable_loop), stdChainNum(stdChainNum) {
					this->words = words;
				}
			};
			std::vector<GenChainCharPythonTestCase> testCases;
			char* words3 = { "woo" };
			testCases.push_back(GenChainCharPythonTestCase(words3, 0, 0, false, 0));
			char* words1 = { "woo oom moon noox" };
			testCases.push_back(GenChainCharPythonTestCase(words1, 0, 0, false, 4));
			testCases.push_back(GenChainCharPythonTestCase(words1, 'w', 0, false, 4));
			testCases.push_back(GenChainCharPythonTestCase(words1, 'o', 0, false, 3));
			testCases.push_back(GenChainCharPythonTestCase(words1, 'n', 0, false, 0));
			testCases.push_back(GenChainCharPythonTestCase(words1, 0, 'x', false, 4));
			testCases.push_back(GenChainCharPythonTestCase(words1, 0, 'n', false, 3));
			testCases.push_back(GenChainCharPythonTestCase(words1, 0, 'o', false, 0));
			char words2[] = { "Algebra Apple Zoo Elephant Elephant Under Fox Dog Moon Leaf Trick Pseudopseudohypoparathyroidism" };
			testCases.push_back(GenChainCharPythonTestCase(words2, 0, 0, false, 2));

			char* words4 = { "\0" };
			testCases.push_back(GenChainCharPythonTestCase(words4, 0, 0, false, 0));
			char* words5 = { "woo oom moow" };
			testCases.push_back(GenChainCharPythonTestCase(words5, 0, 0, false, -3));
			testCases.push_back(GenChainCharPythonTestCase(words5, 0, 0, true, 3));
			testCases.push_back(GenChainCharPythonTestCase(words5, 'w', 0, true, 3));
			testCases.push_back(GenChainCharPythonTestCase(words5, 'o', 0, true, 3));
			testCases.push_back(GenChainCharPythonTestCase(words5, 'm', 0, true, 3));
			testCases.push_back(GenChainCharPythonTestCase(words5, 0, 'o', true, 3));
			testCases.push_back(GenChainCharPythonTestCase(words5, 0, 'm', true, 3));
			testCases.push_back(GenChainCharPythonTestCase(words5, 0, 'w', true, 3));
			testCases.push_back(GenChainCharPythonTestCase(words5, 1, 'w', false, -4));
			testCases.push_back(GenChainCharPythonTestCase(words5, 0, 2, false, -4));


			char* result = new char[200000];
			char* error_msg = new char[2000];
			for (auto& testCase : testCases) {
				int chainNum = gen_chain_char_python(testCase.words, &result, testCase.head,
					testCase.tail, testCase.enable_loop, &error_msg);
				Assert::AreEqual(chainNum, testCase.stdChainNum);
			}
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
			/*char* words1[] = { "woo", "oom", "moon", "noox" };
			testCases.push_back(GenChainsAllTestCase(words1, 4, 6));
			char* words2[] = { "Algebra", "Apple", "Zoo", "Elephant", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf", "Trick", "Pseudopseudohypoparathyroidism" };
			testCases.push_back(GenChainsAllTestCase(words2, 12, 8));
			char* words3[] = { "woo" };
			testCases.push_back(GenChainsAllTestCase(words3, 1, 0));
			char* words4[1] = {};
			testCases.push_back(GenChainsAllTestCase(words4, 0, 0));*/
			char* words5[] = {"345"};
			testCases.push_back(GenChainsAllTestCase(words5, 1, -1));
			char* words6[] = { "woo", "oom", "moon", "noow" };
			testCases.push_back(GenChainsAllTestCase(words6, 4, -3));

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
			testCases.push_back(GenChainWordTestCase(words5, 3, 1, 'w', false, -4));
			testCases.push_back(GenChainWordTestCase(words5, 3, 0, 2, false, -4));

			char* words6[] = { "woo", "o", "oon" };
			testCases.push_back(GenChainWordTestCase(words6, 3, 0, 0, false, -1));
			char* words7[] = { "woo", "123", "oon" };
			testCases.push_back(GenChainWordTestCase(words7, 3, 0, 0, false, -1));

			

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
			char* words5[] = { "345" };
			testCases.push_back(GenChainWordUniqueTestCase(words5, 1, -1));
			char* words6[] = { "woo", "oom", "moon", "noow" };
			testCases.push_back(GenChainWordUniqueTestCase(words6, 4, -3));

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
			testCases.push_back(GenChainCharTestCase(words5, 3, 1, 'w', false, -4));
			testCases.push_back(GenChainCharTestCase(words5, 3, 0, 2, false, -4));

			char* words6[] = { "woo", "o", "oon" };
			testCases.push_back(GenChainCharTestCase(words6, 3, 0, 0, false, -1));
			char* words7[] = { "woo", "123", "oon" };
			testCases.push_back(GenChainCharTestCase(words7, 3, 0, 0, false, -1));

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
