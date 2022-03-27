#pragma once
#include <string>
#include "MException.h"

enum Type {
	CHAIN_NUM, WORD_NUM, CHAR_NUM
};
class ParamHandler
{
private:
	static const int n = 1<<6;
	static const int w = 1<<5;
	static const int m = 1<<4;
	static const int c = 1<<3;
	static const int h = 1<<2;
	static const int t = 1<<1;
	static const int r = 1;

	char head;
	char tail;
	int status;
	std::string fileName;
public:
	ParamHandler() {};

	ParamHandler(int argc, char* argv[]) : head(-1), tail(-1), status(0) {
		check(argc, argv);
	}

	void check(int argc, char* argv[]);

	Type getType();
	char ifSpecializedHead() {
		if (status & h) {
			return head;
		}
		return -1;
	}

	char ifSpecializedTail() {
		if (status & t) {
			return tail;
		}
		return -1;
	}

	bool allowCircle() {
		return (status & r) != 0;
	}

	bool sameHead() {
		return (status & m) != 0;
	}
};

