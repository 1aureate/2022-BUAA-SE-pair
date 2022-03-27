#pragma once
#include <string>
#include "MException.h"

enum class Type {
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
	ParamHandler() : head(0), tail(0), status(0) {}

	ParamHandler(Type type, char head, char tail, bool enable_loop, bool sameHead);

	ParamHandler(int argc, char* argv[]) : head(0), tail(0), status(0) {
		check(argc, argv);
	}

	void check(int argc, char* argv[]);

	Type getType();
	char SpecializedHead() {
		if (status & h) {
			return head;
		}
		return 0;
	}

	char SpecializedTail() {
		if (status & t) {
			return tail;
		}
		return 0;
	}

	bool allowCircle() {
		return (status & r) != 0;
	}

	bool noSameHead() {
		return (status & m) == 0;
	}
};

