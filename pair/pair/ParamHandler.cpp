#include "ParamHandler.h"

void ParamHandler::check(int argc, char* argv[])
{
	int flag = 0;
	for (int i = 1; i < argc - 1; i++) {
		char* s = argv[i];
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
				break;
			case 'w':
				if (status & w) {
					throw ParamException("duplicated option");
				}
				status |= w;
				break;
			case 'm':
				if (status & m) {
					throw ParamException("duplicated option");
				}
				status |= m;
				break;
			case 'c':
				if (status & c) {
					throw ParamException("duplicated option");
				}
				status |= c;
				break;
			case 'h':
				flag = 1;
				status |= h;
				break;
			case 't':
				status |= t;
				break;
			default:
				throw ParamException("unrecognized options: -" + s[1]);
				break;
			}
		}
		else {
			if (s[1] != '\0') {
				throw ParamException("There is redundent character");
			}
			if (flag) {
				if (flag == 1) {
					head = s[0];
				}
				else if (flag == 2) {
					tail = s[0];
				}
			}
			else {
				throw ParamException("There is no -t or -n");
			}
		}
	}
	// contradicted options detection
	if ((status & n) && (status - n)) {
		throw ParamException("option -n is incompatible with other options");
	}
	int cnt = 0;
	if (status & n) {
		cnt++;
	}
	if (status & w) {
		cnt++;
	}
	if (status & m) {
		cnt++;
	}
	if (status & c) {
		cnt++;
	}
	if (cnt == 0) {
		throw ParamException("There is no any option");
	}
	if (cnt > 1) {
		throw ParamException("-n, -w, -m, -c are contradicted");
	}
}

Type ParamHandler::getType()  
{
	if (status & n) {
		return CHAIN_NUM;
	}
	if (status & w || status & m) {
		return WORD_NUM;
	}
	if (status & c) {
		return CHAR_NUM;
	}
}
