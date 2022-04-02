#pragma once
#include "pch.h"
#include "../../pair/pair/main.h"
extern"C" __declspec(dllexport) int fib(int n);
extern"C" __declspec(dllexport) int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
extern"C" __declspec(dllexport) int gen_chains_all(char* words[], int len, char* result[]);
extern"C" __declspec(dllexport) int gen_chain_word_unique(char* words[], int len, char* result[]);
extern"C" __declspec(dllexport) int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);

extern"C" __declspec(dllexport) int gen_chains_all_python(char* words, char** result, char** error_msg);
extern"C" __declspec(dllexport) int gen_chain_word_python(char* words, char** result, char head, char tail, bool enable_loop, char** error_msg);
extern"C" __declspec(dllexport) int gen_chain_word_unique_python(char* words, char** result, char** error_msg);
extern"C" __declspec(dllexport) int gen_chain_char_python(char* words, char** result, char head, char tail, bool enable_loop, char** error_msg);



bool checkHeadAndTail(char head, char tail);
bool checkWord(const char word[]);
int buildWordList(char* words[], int len, std::vector<Word>& ws);
int buildWordList(std::vector<std::string>& words, std::vector<Word>& ws);
int output2result(std::vector<std::string> words, char* result[]);
int output2result_python(std::vector<std::string> words, char* result[]);