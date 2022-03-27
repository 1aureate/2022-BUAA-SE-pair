// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "dllmain.h"
#include "D:\Chaos\Program\C++\2022-BUAA-SE-pair\pair\pair\main.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// result只存储一个字符串
int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
    ParamHandler ph(Type::WORD_NUM, head, tail, enable_loop, false);
    std::vector<Word> ws(len);
    for (int i = 0; i < len; i++) {
        ws[i] = Word(std::string(words[i]));
    }
    WordListHandler wh(ph, ws);
    std::vector<std::string> ans = wh.handle();

    int ans_size = ans.size();
    std::string result_string = "";
    for (int i = 0; i < ans_size; i++) {
        // c_str return a "const char *" type, so we need to copy the origin string 
        auto len = ans[i].size();
        char* temp = new char[len + 1];
        strcpy_s(temp, len + 1, ans[i].c_str());
        result[i] = temp;
    }
    return ans_size;
}

int gen_chains_all(char* words[], int len, char* result[]) {
    ParamHandler ph(Type::CHAIN_NUM, 0, 0, false, false);
    std::vector<Word> ws(len);
    for (int i = 0; i < len; i++) {
        ws[i] = Word(std::string(words[i]));
    }
    WordListHandler wh(ph, ws);
    std::vector<std::string> ans = wh.handle();

    auto ans_size = ans.size();
    std::string result_string = "";
    for (int i = 0; i < ans_size; i++) {
        auto len = ans[i].size();
        char* temp = new char[len + 1];
        strcpy_s(temp, len + 1, ans[i].c_str());
        result[i] = temp;
    }
    return ans_size;
}

int gen_chain_word_unique(char* words[], int len,  char* result[]) {
    ParamHandler ph(Type::WORD_NUM, 0, 0, false, true);
    std::vector<Word> ws(len);
    for (int i = 0; i < len; i++) {
        ws[i] = Word(std::string(words[i]));
    }
    WordListHandler wh(ph, ws);
    std::vector<std::string> ans = wh.handle();

    auto ans_size = ans.size();
    std::string result_string = "";
    for (int i = 0; i < ans_size; i++) {
        auto len = ans[i].size();
        char* temp = new char[len + 1];
        strcpy_s(temp, len + 1, ans[i].c_str());
        result[i] = temp;
    }
    return ans_size;
}

int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
    ParamHandler ph(Type::CHAR_NUM, head, tail, enable_loop, false);
    std::vector<Word> ws(len);
    for (int i = 0; i < len; i++) {
        ws[i] = Word(std::string(words[i]));
    }
    WordListHandler wh(ph, ws);
    std::vector<std::string> ans = wh.handle();

    auto ans_size = ans.size();
    std::string result_string = "";
    for (int i = 0; i < ans_size; i++) {
        auto len = ans[i].size();
        char* temp = new char[len + 1];
        strcpy_s(temp, len + 1, ans[i].c_str());
        result[i] = temp;
    }
    return ans_size;
}

