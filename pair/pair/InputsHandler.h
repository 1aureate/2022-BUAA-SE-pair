#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include "word.h"
#include "MException.h"

class InputsHandler
{
private:
	std::string getWord(std::ifstream& _in);
public:
	InputsHandler() {};
	std::vector<std::string> extractWords(const std::string& s);
	std::vector<std::string> handle(std::string _filename);
};

