#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <Windows.h>

#include "../../pair_dll/pair_dll/ParamHandler.h"
#include "../../pair_dll/pair_dll/InputsHandler.h"
//#include "WordListHandler.h"
//#include "word.h"
#include "OutputHandler.h"
#include "ErrorCodeHandler.h"

char** vectorString2charArray(std::vector<std::string> words);
std::string file2string(std::string filename);

#define DEBUG false

