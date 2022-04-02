#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

#include "ParamHandler.h"
#include "InputsHandler.h"
#include "WordListHandler.h"
#include "word.h"
#include "OutputHandler.h"
#include "ErrorCodeHandler.h"

char** vectorString2charArray(std::vector<std::string> words);


#define DEBUG true

