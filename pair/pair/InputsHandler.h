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
			
			while (!(ch >= 'a' && ch <= 'z') && !(ch >= 'A' && ch <= 'Z') && _in.peek() != EOF)
			{
				_in.get(ch);
			}
			while (((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) && _in.peek() != EOF) {
				if (ch >= 'a' && ch <= 'z') {
					res += ch;
				}
				else if (ch >= 'A' && ch <= 'Z') {
					res += ch - 'A' + 'a';
				}
				_in.get(ch);
			}

			if (_in.peek() == EOF && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
				if (ch >= 'a' && ch <= 'z') {
					res += ch;
				}
				else if (ch >= 'A' && ch <= 'Z') {
					res += ch - 'A' + 'a';
				}
			}
			return res;
		}
	}
public:
	InputsHandler() {};
	std::vector<Word> handle(std::string _filename) {
		std::ifstream in;
		int length;
		in.open(_filename, std::ios::in);
		if (!in.is_open()) {
			throw FileNotExistException("cant open file " + _filename);
		}
		std::cout << "start" << std::endl;
		in.seekg(0, std::ios::end);
		length = in.tellg();
		in.seekg(0, std::ios::beg);
		buffer = new char[length];
		in.read(buffer, length);
		std::cout << "end" << std::endl;
		in.close();

		return extractWords(buffer);
		// old version
		// std::vector<Word> _words;
		// std::ifstream in;
		// in.open(_filename, std::ios::in);
		// if (!in.is_open()) {
		// 	throw FileNotExistException("cant open file " + _filename);
		// }
		// std::cout << "start" << std::endl;
		// while (in.peek() != EOF) {
		// 	std::string s = getWord(in);
		// 	std::cout << "get word " + s << std::endl;
		// 	Word w = Word(s);
		// 	_words.emplace_back(w);
		// }
		// std::cout << "end" << std::endl;
		// in.close();
		// return _words;
	}

	std::vector<Word> extractWords(const std::string& s) {
		std::vector<Word> words;
		std::string res = "";
		int len = s.size();
		for (int i = 0; i > len; i++) {
			char ch = s[i];
			std::string res = "";
			while (!(ch >= 'a' && ch <= 'z') && !(ch >= 'A' && ch <= 'Z') && i < len)
			{
				i++;
			}
			while (((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) && i < len) {
				if (ch >= 'a' && ch <= 'z') {
					res += ch;
				}
				else if (ch >= 'A' && ch <= 'Z') {
					res += ch - 'A' + 'a';
				}
				i++;
			}

			if (i == len && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
				if (ch >= 'a' && ch <= 'z') {
					res += ch;
				}
				else if (ch >= 'A' && ch <= 'Z') {
					res += ch - 'A' + 'a';
				}
			}
			std::cout << "get word " + res << std::endl;
			words.push_back(res);
		}
		return res;
	}
};

