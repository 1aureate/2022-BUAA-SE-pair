#pragma once
#include <iostream>
#include "InputsHandler.h"
#include "ParamHandler.h"

class WordListHandler
{
private:
	ParamHandler paramHandler;
	std::unordered_map<char, std::list<Word>> head2words;
	std::unordered_map<char, std::list<Word>> tail2words;
	std::vector<Word> words;

public:

	WordListHandler(ParamHandler& _paramHandler, std::vector<Word> _words) {

		for (int i = 0; i < 26; i++) {
			head2words.emplace(i + 'a', std::list<Word>());
			tail2words.emplace(i + 'a', std::list<Word>());
		}

		words = _words;
		paramHandler = _paramHandler;

		for (auto w : words) {
			head2words[w.first].emplace_back(w);
			tail2words[w.last].emplace_back(w);
		}
	}

	void handle() {
		switch (paramHandler.getType())
		{
		case Type::CHAIN_NUM:

			break;
		case Type::CHAR_NUM:

			break;
		case Type::WORD_NUM:

			break;
		default:
			throw "illegal param type!";
			break;
		}
	}

	void gen_chains_all() {
		
	}





};





