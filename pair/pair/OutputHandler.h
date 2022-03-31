#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
class OutputHandler
{
public:
	virtual void output(std::vector<std::string> s) = 0;
};

class FileOutputHandler : public OutputHandler {
private:
	std::string filename;
public:
	FileOutputHandler(std::string filename) : filename(filename) {}
	void output(std::vector<std::string> s) {
		std::ofstream out(filename, std::ios::out);
		if (!out.is_open()) {
			throw "file " + filename + " cant be opened!!!!!";
		}
		for (auto& str : s) {
			out << str << std::endl;
		}
		out.close();
	}
};

class STDOutputHandler : public OutputHandler {
public:
	void output(std::vector<std::string> s) {

		for (auto e : s) {
			std::cout << e << std::endl;
		}
	}
};
