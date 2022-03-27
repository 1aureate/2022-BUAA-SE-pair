#pragma once
extern"C" __declspec(dllexport) int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);

extern"C" __declspec(dllexport) int gen_chains_all(char* words[], int len, char* result[]);

extern"C" __declspec(dllexport) int gen_chain_word_unique(char* words[], int len, char* result[]);

extern"C" __declspec(dllexport) int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);