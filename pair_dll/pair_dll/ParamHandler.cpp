#include "ParamHandler.h"
ParamHandler::ParamHandler(Type type, char head, char tail, bool enable_loop, bool noSameHead) :
	head(0), tail(0), status(0), fileName("") {
	switch (type)
	{
	case Type::CHAIN_NUM:
		status |= n;
		break;
	case Type::WORD_NUM:
		status |= w;
		break;
	case Type::CHAR_NUM:
		status |= c;
		break;
	default:
		break;
	}
	// 传入0表示没有约束
	if (head) {
		this->head = head;
		status |= h;
	}
	if (tail) {
		this->tail = tail;
		status |= t;
	}
	if (enable_loop) {
		status |= r;
	}
	if (noSameHead) {
		status |= m;
	}
}

ParamHandler::ParamHandler(int argc, char* argv[])
	: head(0), tail(0), status(0), fileName("") {
	if (argc < 2) {
		throw ParamException("Please specify -n -w -m -c");
	}
	int flag = 0;
	int preParam = 0;
	for (int i = 1; i < argc; i++) {
		char const* s = argv[i];
		if (s[0] == '-') {
			if (s[1] == '\0' || s[2] != '\0') {
				throw ParamException("There are redundant character or missed cahrecter after '-'");
			}
			switch (s[1])
			{
			case 'n':
				if (status & n) {
					throw ParamException("duplicated option");
				}
				status |= n;
				preParam = n;
				break;
			case 'w':
				if (status & w) {
					throw ParamException("duplicated option");
				}
				status |= w;
				preParam = w;
				break;
			case 'm':
				if (status & m) {
					throw ParamException("duplicated option");
				}
				status |= m;
				preParam = m;
				break;
			case 'c':
				if (status & c) {
					throw ParamException("duplicated option");
				}
				status |= c;
				preParam = c;
				break;
			case 'h':
				if (status & h) {
					throw ParamException("duplicated option");
				}
				flag = 1;
				status |= h;
				preParam = h;
				break;
			case 't':
				if (status & t) {
					throw ParamException("duplicated option");
				}
				status |= t;
				preParam = t;
				break;
			case 'r':
				if (status & r) {
					throw ParamException("duplicated option");
				}
				status |= r;
				preParam = r;
				break;
			default:
				throw ParamException("unrecognized options: -" + s[1]);
				break;
			}
		}
		else {
			if (preParam == h || preParam == t) {
				if (s[1] != '\0') {
					throw ParamException("There is redundent character");
				}
				else if (tolower(s[0]) < 'a' || tolower(s[0]) > 'z') {
					throw ParamException("unrecognied character, please use English alphabet.");
				}
				if (preParam == h) {
					head = s[0];
				}
				else {
					tail = s[0];
				}

			}
			else {
				fileName = std::string(s);
				if (status & f) {
					throw FileIllegalException("Please input only one '.txt'");
				}
				auto r = checkFileName(fileName);
				if (r == false) {
					throw FileIllegalException("Please make sure the filename end up with '.txt'");
				}
			}
			preParam = 0;
		}
	}
	if (fileName == "") {
		throw ParamException("Please input filename");
	}
}

bool ParamHandler::checkFileName(std::string& s) {
	if (s.size() < 4 || s.substr(s.size() - 4, s.size()) != std::string(".txt")) {
		return false;
	}
	status |= f;
	return true;
}

Type ParamHandler::getType()
{
	if (status & n)
	{
		return Type::CHAIN_NUM;
	}
	else if (status & w || status & m)
	{
		return Type::WORD_NUM;
	}
	else if (status & c)
	{
		return Type::CHAR_NUM;
	}
	else
	{
		throw ParamException("Unhandled type, please contact the developer.");
	}
}
