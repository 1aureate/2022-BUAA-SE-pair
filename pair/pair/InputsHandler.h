#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include "word.h"
#include "MException.h"

class InputsHandler
{
private:
	std::string getWord(std::ifstream& _in) {
		{
			std::string res = "";
			char ch;
			_in.get(ch);
			while (ch != '\0') {
				if (ch >= 'a' && ch <= 'z') {
					res += ch;
				}
				else if (ch >= 'A' && ch <= 'Z') {
					res += ch - 'A' + 'a';
				}
				_in.get(ch);
			}
			return res;
		}
	}
public:
	InputsHandler() {};
	std::vector<Word> handle(std::string _filename) {
		std::vector<Word> _words;
		std::ifstream in;
		// init(_head2words, _tail2words);
		in.open(_filename, std::ios::in);
		if (!in.is_open()) {
			throw FileNotExistException("cant open file " + _filename);
		}
		while (in.peek() != EOF) {
			std::string s = getWord(in);
			Word w = Word(s);
			_words.emplace_back(w);
		}
		return _words;
	}
};

