#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
class OutputHandler
{
public:
	virtual void output(char* s[], int len) = 0;
};

class FileOutputHandler : public OutputHandler {
private:
	std::string filename;
public:
	FileOutputHandler(std::string filename) : filename(filename) {}
	void output(char* s[], int len) {
		std::ofstream out(filename, std::ios::out);
		if (!out.is_open()) {
			throw "file " + filename + " cant be opened!!!!!";
		}
		for (int i = 0; i < len; i++) {
			out << s[i] << std::endl;
		}
		out.close();
	}
};

class STDOutputHandler : public OutputHandler {
public:
	void output(char* s[], int len) {
		for (int i = 0; i < len; i++) {
			std::cout << s[i] << std::endl;
		}
	}
};
