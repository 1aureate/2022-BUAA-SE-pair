// pair.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include "pair.h"

std::ifstream in;
std::ofstream out;

std::vector<Word&> words;
std::unordered_map<char, std::list<Word&>> head2words;
std::unordered_map<char, std::list<Word&>> tail2words;

void init() {
	for (int i = 0; i < 32; i++) {
		head2words.emplace('a' + i, std::list<Word&>());
		tail2words.emplace('a' + i, std::list<Word&>());
	}
}

std::string getWord(std::ifstream& in) {
	std::string res = "";
	char ch;
	in.get(ch);
	while (ch != '\0') {
		if (ch >= 'a' && ch <= 'z') {
			res += ch;
		}
		else if (ch >= 'A' && ch <= 'Z') {
			res += ch - 'A' + 'a';
		}
		in.get(ch);
	}
	return res;
}

void handleInputs(std::string filename) {
	// TODO exception if file dont exist
	in.open(filename, std::ios::in);
	while (in.peek() != EOF) {
		std::string s = getWord(in);
		Word w = Word(s);
		words.emplace_back(w);
		head2words[w.first].emplace_back(w);
		tail2words[w.last].emplace_back(w);
	}
}

void handleParams(std::string op) {
	switch (op[1])
	{
	case 'n':
		
		break;
	case 'w':
		break;
	case 'm':
		break;
	case 'c':
		break;
	case 'h':
		break;
	case 't':
		break;
	case 'r':
		break;
	default:
		break;
	}
}


int main(int argc, char* argv[])
{
	init();
	//TODO excepitions when argc is ilegal
	
	handleInputs(argv[argc - 1]);
	for (int i = 0; i < argc-1; i++) {
		handleParams(std::string(argv[i]));
	}

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
