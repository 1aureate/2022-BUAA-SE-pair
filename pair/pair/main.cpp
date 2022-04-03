// pair.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
// TODO handle the header

#include "main.h"


int main(int argc, char* argv[]) {
	
	HINSTANCE hdll;
	hdll = LoadLibrary(L"../../pair_dll/x64/Debug/pair_dll.dll");
	if (hdll == nullptr) {
		std::cout << "[error]: can't find dll file";
		return 0;
	}

	try {
		ParamHandler* paramHandler;
		if (DEBUG) {
			int argc = 4;
			char* argv[] = { "pair.exe", "-w", "test.txt", "-r" };
			paramHandler = new ParamHandler(argc, argv);
		}
		else {
			paramHandler = new ParamHandler(argc, argv);
		}
		
		std::cout << "[msg]: param handled" << std::endl;
		InputsHandler inputsHandler;
		std::vector<std::string> words = 
			inputsHandler.extractWords(file2string(paramHandler->getFileName()));
		std::cout << "[msg]: inputs handled" << std::endl;

		char** newWords = vectorString2charArray(words);
		auto result = new char[20000][200];
		int returnValue = 0;
		switch (paramHandler->getType())
		{
		case Type::CHAIN_NUM: {
			int (*func)(char* [], int, char* []) = 
				(int (*)(char* [], int, char* []))GetProcAddress(hdll, "gen_chains_all");
			returnValue = func(newWords, words.size(), (char**)result);
			break;
		} 
		case Type::WORD_NUM: {
			if (paramHandler->noSameHead()) {
				int (*func)(char* [], int, char* []) =
					(int (*)(char* [], int, char* []))GetProcAddress(hdll, "gen_chain_word_unique");
				returnValue = func(newWords, words.size(), (char**)result);
			}
			else {
				int (*func)(char* [], int, char* [], char, char, bool) =
					(int (*)(char* [], int, char* [], char, char, bool))
					GetProcAddress(hdll, "gen_chain_word");
				returnValue = func(newWords, words.size(), 
					(char**)result,
					paramHandler->specializedHead(), 
					paramHandler->specializedTail(),
					paramHandler->allowCircle());
			}
			break;
		} 
		case Type::CHAR_NUM: {
			int (*func)(char* [], int, char* [], char, char, bool) =
				(int (*)(char* [], int, char* [], char, char, bool))
				GetProcAddress(hdll, "gen_chain_char");
			returnValue = func(newWords, words.size(),
				(char**)result,
				paramHandler->specializedHead(),
				paramHandler->specializedTail(),
				paramHandler->allowCircle());
			break;
		}
		default:
			break;
		}

		if (returnValue < 0) {
			std::cout << "[error]: " << ErrorCodeHandler::code2ErrorMessage(returnValue);
			return 0;
		}
		if (DEBUG) {
			STDOutputHandler soh;
			soh.output((char**)result, returnValue);
		}
		else {
			if (paramHandler->getType() == Type::CHAIN_NUM) {
				STDOutputHandler soh;
				soh.output((char**)result, returnValue);
			}
			else {
				FileOutputHandler foh("solution.txt");
				foh.output((char**)result, returnValue);
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
	catch (std::exception e) {
		std::cout << "[error]: " << e.what();
	}
	return 0;

}

char** vectorString2charArray(std::vector<std::string> words) {
	char** ans;
	ans = (char**)new char*[words.size()];
	int wordsLen = words.size();
	for (int i = 0; i < wordsLen; i++) {
		ans[i] = new char[words[i].size()];
		strcpy_s(ans[i], words[i].size() + 1, words[i].c_str());
	}
	return ans;
}

std::string file2string(std::string filename)
{
	std::ifstream in;
	in.open(filename, std::ios::in);
	if (!in.is_open()) {
		throw FileIllegalException("cant open file " + filename);
	}
	std::cout << "start" << std::endl;
	in.seekg(0, std::ios::end);
	auto length = in.tellg();
	in.seekg(0, std::ios::beg);
	auto buffer = new char[length];
	in.read(buffer, length);
	std::cout << "end" << std::endl;
	in.close();
	return buffer;
}