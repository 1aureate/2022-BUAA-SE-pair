#include "InputsHandler.h"

std::string InputsHandler::getWord(std::ifstream& _in)
{
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


std::vector<Word> InputsHandler::handle(std::string _filename)
{
	std::vector<Word> _words;
	std::ifstream in;
	in.open(_filename, std::ios::in);
	if (!in.is_open()) {
		throw FileNotExistException("cant open file " + _filename);
	}
	std::cout << "start" << std::endl;
	while (in.peek() != EOF) {
		std::string s = getWord(in);
		std::cout << "get word " + s << std::endl;
		Word w = Word(s);
		_words.emplace_back(w);
	}
	std::cout << "end" << std::endl;
	in.close();
	return _words;
}