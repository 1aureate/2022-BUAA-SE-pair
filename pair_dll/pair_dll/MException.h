#pragma once
#include<string>
#include<exception>
class MException : public std::exception {
private:
    std::string msg;
public:
    MException(std::string msg) : msg(msg) {}
    const char* what() const throw ()
    {
        return msg.c_str();
    }
};

class ParamException : public MException {
public:
    ParamException(std::string msg) : MException(msg) {}
};


class FileIllegalException : public MException {
public:
    FileIllegalException(std::string msg) : MException(msg) {}
};

class ExistsLoopException : public MException {
public: 
    ExistsLoopException(std::string msg) : MException(msg) {}
};

