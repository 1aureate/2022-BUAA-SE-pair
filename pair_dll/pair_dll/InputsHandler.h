#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include "word.h"
#include "MException.h"

class InputsHandler
{

public:
	InputsHandler() {};
	std::vector<std::string> extractWords(const std::string& s);
};

