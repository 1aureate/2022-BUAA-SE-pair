#pragma once
#include <string>
#include "MException.h"

enum Type {
	CHAIN_NUM, WORD_NUM, CHAR_NUM
};
class ParamHandler
{
private:
	//bool n; // only itself ���㵥���ı��п��Թ��ɶ��ٸ����������ܹ��������е���������Ŀ��
	//bool w; // ������൥�������ĵ�����
	//bool m; // not pair with h t r  Ҫ�󵥴����е�ÿһ�����ʵ�����ĸ������ͬ��������൥�������ĵ����� ע��-m ������Ҫ�������� -h��-t��-r ����ʹ�á�
	//bool c; // ������ĸ���ĵ�����
	//bool h; // ָ����������ͷ��ĸ
	//bool t; // ָ����������β��ĸ
	//bool r; // ���������ı��������ʻ�

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

	void check(int argc, char* argv[]) {
		int flag = 0;
		for (int i = 1; i < argc-1; i++) {
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
					throw ParamException("unrecognized options: -" +  s[1]);
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

	Type getType() {
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

	bool noSameHead() {
		return (status & m) != 0;
	}
};

