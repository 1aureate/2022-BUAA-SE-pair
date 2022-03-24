#pragma once
#include <string>
#include <fstream>
#include "pair.h"
#include <vector>
#include <unordered_map>
#include "MException.h"

class InputsHandler
{
private:
	std::vector<Word&> words;
	std::unordered_map<char, std::list<Word&>> head2words;
	std::unordered_map<char, std::list<Word&>> tail2words;
	std::ifstream in;
public:

	InputsHandler(std::string _filename);

	std::string getWord(std::ifstream &_in);

	void init();

	std::list<Word&> getWordsEndWithCh(char _ch) {
		return tail2words[_ch];
	}

	std::list<Word&> getWordsStartWithCh(char _ch) {
		return head2words[_ch];
	}
};

void InputsHandler::init() {
	for (int i = 0; i < 32; i++) {
		head2words.emplace('a' + i, std::list<Word&>());
		tail2words.emplace('a' + i, std::list<Word&>());
	}
}

InputsHandler::InputsHandler(std::string filename) {
	init();
	in.open(filename, std::ios::in);
	if (!in.is_open()) {
		throw FileNotExistException("cant open file " + filename);
	}
	while (in.peek() != EOF) {
		std::string s = getWord(in);
		Word w = Word(s);
		words.emplace_back(w);
		head2words[w.first].emplace_back(w);
		tail2words[w.last].emplace_back(w);
	}
}

std::string InputsHandler::getWord(std::ifstream &in) {
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

