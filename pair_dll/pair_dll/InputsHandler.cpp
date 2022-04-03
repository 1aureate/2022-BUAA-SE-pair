#include "InputsHandler.h"

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
		// maybe useless or not.
		//if (i == len && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
		//	if (ch >= 'a' && ch <= 'z') {
		//		res += ch;
		//	}
		//	else if (ch >= 'A' && ch <= 'Z') {
		//		res += ch - 'A' + 'a';
		//	}
		//}
		if (res.size() > 1) {
			std::cout << "get word " + res << std::endl;
			words.push_back(res);
		}
	}
	return words;
}

