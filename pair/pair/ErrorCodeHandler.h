#pragma once
#include <string>
#include <vector>
class ErrorCodeHandler {
private:
	static std::vector<std::string> errorMessages;
	static int errorMessagesNum;
	/*
	error code map:
		 0: Everything is alright;
		-1: Illegal word exists.
		-2: More than 20000 results.
		-3: EnableLoop is false, but loop is found.
		-4: Illegal head or tail letter.
		others: Unexpected exception occured, please contact the developer.
	*/
public:
	static std::string code2ErrorMessage(int errorCode) {
		if (errorCode >= 0) {
			return errorMessages[0];
		}
		else if (-errorCode >= errorMessages.size() - 1) {
			return errorMessages[errorMessages.size() - 1];
		}
		else {
			return errorMessages[-errorCode];
		}
		return "code2ErrorMessage is incompleted.";
	}
};