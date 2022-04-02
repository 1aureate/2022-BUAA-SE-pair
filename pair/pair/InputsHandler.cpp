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

std::vector<std::string> InputsHandler::extractWords(const std::string& s)
{
	std::vector<std::string> words;
	auto len = s.size();
	for (auto i = len - len; i < len; i++) {
		char ch = s[i];
		std::string res = "";
		while (!(ch >= 'a' && ch <= 'z') && !(ch >= 'A' && ch <= 'Z') && i < len)
		{
			i++;
			ch = s[i];
		}
		while (((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) && i < len) {
			if (ch >= 'a' && ch <= 'z') {
				res += ch;
			}
			else if (ch >= 'A' && ch <= 'Z') {
				res += ch - 'A' + 'a';
			}
			i++;
			ch = s[i];
		}
		if (i == len && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
			if (ch >= 'a' && ch <= 'z') {
				res += ch;
			}
			else if (ch >= 'A' && ch <= 'Z') {
				res += ch - 'A' + 'a';
			}
		}
		if (res.size() > 1) {
			std::cout << "get word " + res << std::endl;
			words.push_back(res);
		}
	}
	return words;
}

std::vector<std::string> InputsHandler::handle(std::string _filename)
{
	std::ifstream in;
	in.open(_filename, std::ios::in);
	if (!in.is_open()) {
		throw FileIllegalException("cant open file " + _filename);
	}
	std::cout << "start" << std::endl;
	in.seekg(0, std::ios::end);
	auto length = in.tellg();
	in.seekg(0, std::ios::beg);
	auto buffer = new char[length];
	in.read(buffer, length);
	std::cout << "end" << std::endl;
	in.close();
	return extractWords(buffer);
}