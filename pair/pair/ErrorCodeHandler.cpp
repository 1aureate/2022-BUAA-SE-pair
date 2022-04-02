#include "ErrorCodeHandler.h"

/*
0: no problem
-1: 
*/

std::vector<std::string> ErrorCodeHandler::errorMessages = { 
	"Everything is alright.", 
	"Illegal word exists.",
	"More than 20000 results.",
	"EnableLoop is false, but loop is found.",
	"Illegal head or tail letter.",
	"Unexpected exception occured, please contact the developer.",};
int ErrorCodeHandler::errorMessagesNum = 4;