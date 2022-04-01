// pair.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
// TODO handle the header

#include "main.h"
#include <Windows.h>

int main(int argc, char* argv[]) {
	HINSTANCE hdll;
	hdll = LoadLibrary(L"../../pair_dll/x64/Debug/pair_dll.dll");
	if (hdll == nullptr) {
		std::cout << "[error]: can't find dll file";
		return 0;
	}
	int (*func1)(char* [], int, char* []) = (int (*)(char* [], int, char* []))GetProcAddress(hdll, "gen_chains_all");
	char* words[] = { "moox", "xooy", "yoot", "toop" };
	auto result = new char* [20000];
	int r = func1(words, 4, result);
	std::cout << "r = " << r << std::endl;
	std::cout << "result[0] = " << result[0];

	return 0;
}
/*
int main(int argc, char* argv[])
{
	try {
		if (DEBUG) {
			int argc = 4;
			
			char * argv[] = { "pair.exe", "-w", "test.txt", "-r"};
			argv[0] = "pair.exe";
			ParamHandler paramHandler(argc, argv);
			std::cout << "[msg]: param handled" << std::endl;
			InputsHandler inputsHandler;
			std::vector<Word> words = inputsHandler.handle(paramHandler.getFileName());
			std::cout << "[msg]: inputs handled" << std::endl;
			WordListHandler wordListHandler(paramHandler, words);
			std::cout << "[msg]: start wordListHandler" << std::endl;
			std::vector<std::string> ans = wordListHandler.handle();
			STDOutputHandler soh;
			soh.output(ans);
		}
		else {
			ParamHandler paramHandler(argc, argv);
			std::cout << "[msg]: param handled" << std::endl;
			InputsHandler inputsHandler;
			std::vector<Word> words = inputsHandler.handle(argv[argc - 1]);
			std::cout << "[msg]: inputs handled" << std::endl;
			WordListHandler wordListHandler(paramHandler, words);
			std::cout << "[msg]: start wordListHandler" << std::endl;
			std::vector<std::string> ans = wordListHandler.handle();

			if (paramHandler.getType() == Type::CHAIN_NUM) {
				STDOutputHandler soh;
				soh.output(ans);
			}
			else {
				FileOutputHandler foh("solution.txt");
				foh.output(ans);
			}
		}
		std::cout << "[msg]: target handled" << std::endl;
	}
	catch (ParamException pe) {
		std::cout << "[error]: " << pe.what();
	}
	catch (FileIllegalException fe) {
		std::cout << "[error]: " << fe.what();
	}
	catch (ExistsLoopException ee) {
		std::cout << "[error]: " << ee.what();
	}
	return 0;
}
*/