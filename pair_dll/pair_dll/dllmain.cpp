// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "dllmain.h"

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
int fib(int n) {
    return n == 0 || n == 1 ? 1 : fib(n - 1) + fib(n - 2);
}


// result只存储一个字符串
int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
    try {
        head = tolower(head);
        tail = tolower(tail);
        if (!checkHeadAndTail(head, tail)) {
            return -4;
        }
        ParamHandler ph(Type::WORD_NUM, head, tail, enable_loop, false);
        std::vector<Word> ws;
        int r;
        if ((r = buildWordList(words, len, ws)) < 0) {
            return -1;
        }

        WordListHandler wh(ph, ws);
        std::vector<std::string> ans = wh.handle();

        if (ans.size() > 20000) {
            return -2;
        }
        output2result(ans, result);
        return ans.size();
    }
    catch (ExistsLoopException e) {
        return -3;
    }
    catch (std::exception e) {
        return -400;
    }
    
}

int gen_chains_all(char* words[], int len, char* result[]) {
    try {
        ParamHandler ph(Type::CHAIN_NUM, 0, 0, false, false);
        std::vector<Word> ws;
        int r;
        if ((r = buildWordList(words, len, ws)) < 0) {
            return -1;
        }
        WordListHandler wh(ph, ws);
        std::vector<std::string> ans = wh.handle();

        if (ans.size() > 20000) {
            return -2;
        }
        output2result(ans, result);
        return ans.size();
    }
    catch (ExistsLoopException e) {
        return -3;
    }
    catch (std::exception e) {
        return -400;
    }
    
}

int gen_chain_word_unique(char* words[], int len,  char* result[]) {
    try {
        ParamHandler ph(Type::WORD_NUM, 0, 0, false, true);
        std::vector<Word> ws;
        int r;
        if ((r = buildWordList(words, len, ws)) < 0) {
            return -1;
        }
        WordListHandler wh(ph, ws);
        std::vector<std::string> ans = wh.handle();

        if (ans.size() > 20000) {
            return -2;
        }
        output2result(ans, result);
        return ans.size();
    }
    catch (ExistsLoopException e) {
        return -3;
    }
    catch (std::exception e) {
        return -400;
    }
}

int gen_chain_char(char* words[], int len, char* result[], 
    char head, char tail, bool enable_loop) {
    try {
        head = tolower(head);
        tail = tolower(tail);
        if (!checkHeadAndTail(head, tail)) {
            return -4;
        }

        ParamHandler ph(Type::CHAR_NUM, head, tail, enable_loop, false);
        std::vector<Word> ws;
        int r;
        if ((r = buildWordList(words, len, ws)) < 0) {
            return -1;
        }
        WordListHandler wh(ph, ws);
        std::vector<std::string> ans = wh.handle();

        if (ans.size() > 20000) {
            return -2;
        }
        output2result(ans, result);
        return ans.size();
    }
    catch (ExistsLoopException e) {
        return -3;
    }
    catch (std::exception e) {
        return -400;
    }
}


int gen_chains_all_python(char* words, char** result, char** error_msg) {
    try {


        // 面向python开放的接口
        InputsHandler ih;
        auto origin = ih.extractWords(std::string(words));
        std::vector<Word> ws;
        int r;
        if ((r = buildWordList(origin, ws)) < 0) {
            return -1;
        }

        ParamHandler ph(Type::CHAIN_NUM, 0, 0, false, false);

        WordListHandler wh(ph, ws);
        std::vector<std::string> ans = wh.handle();
        output2result_python(ans, result);
        return ans.size();
    }

    catch (ExistsLoopException e) {
        return -3;
    }
    catch (std::exception e) {
        return -400;
    }
}

int gen_chain_word_python(char* words, char** result, char head, 
    char tail, bool enable_loop, char** error_msg) {
    // 面向python开放的接口
    try {
        head = tolower(head);
        tail = tolower(tail);
        if (!checkHeadAndTail(head, tail)) {
            return -4;
        }
        InputsHandler ih;
        auto origin = ih.extractWords(std::string(words));
        std::vector<Word> ws;
        int r;
        if ((r = buildWordList(origin, ws)) < 0) {
            return -1;
        }

        ParamHandler ph(Type::WORD_NUM, head, tail, enable_loop, false);

        WordListHandler wh(ph, ws);
        std::vector<std::string> ans = wh.handle();
        output2result_python(ans, result);
        return ans.size();
    }
    catch (ExistsLoopException e) {
        return -3;
    }
    catch (std::exception e) {
        return -400;
    }
}

int gen_chain_word_unique_python(char* words, char** result, char** error_msg) {
    try{
        // 面向python开放的接口
        InputsHandler ih;
        auto origin = ih.extractWords(std::string(words));
        std::vector<Word> ws;
        int r;
        if ((r = buildWordList(origin, ws)) < 0) {
            return -1;
        }

        ParamHandler ph(Type::WORD_NUM, 0, 0, false, true);
        WordListHandler wh(ph, ws);
        std::vector<std::string> ans = wh.handle();
        output2result_python(ans, result);
        return ans.size();
    }
    catch (ExistsLoopException e) {
        return -3;
    }
    catch (std::exception e) {
        return -400;
    }
}

int gen_chain_char_python(char* words, char** result, char head, char tail, 
    bool enable_loop, char** error_msg) {
    try{
        head = tolower(head);
        tail = tolower(tail);
        if (!checkHeadAndTail(head, tail)) {
            return -4;
        }
        // 面向python开放的接口
        InputsHandler ih;
        auto origin = ih.extractWords(std::string(words));
        std::vector<Word> ws;
        int r;
        if ((r = buildWordList(origin, ws)) < 0) {
            return -1;
        }
    
        ParamHandler ph(Type::CHAR_NUM, head, tail, enable_loop, false);
        WordListHandler wh(ph, ws);
        std::vector<std::string> ans = wh.handle();
        output2result_python(ans, result);
        return ans.size();
    }
    catch (ExistsLoopException e) {
        return -3;
    }
    catch (std::exception e) {
        return -400;
    }
}

bool checkHeadAndTail(char head, char tail) {
    return (head == 0 || ((head >= 'a' && head <= 'z') || (head >= 'A' && head <= 'Z')))
        && (tail == 0 || ((tail >= 'a' && tail <= 'z') || (tail >= 'A' && tail <= 'Z')));
}

bool checkWord(const char word[]) {
    for (int i = 0; word[i] != 0; i++) {
        char ch = word[i];
        if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
            return false;
        }
    }
    return true;
}

int buildWordList(char* words[], int len, std::vector<Word>& ws) {
    for (int i = 0; i < len; i++) {
        if (!checkWord(words[i])) {
            return -1;
        }
        ws.push_back(std::string(words[i]));
    }
    return 0;
}

int buildWordList(std::vector<std::string>& words, std::vector<Word>& ws) {
    for (auto w : words) {
        if (!checkWord(w.c_str())) {
            return -1;
        }
        ws.push_back(w);
    }
    return 0;
}

int output2result(std::vector<std::string> words, char* result[]) {
    std::string result_string = "";
    size_t size = words.size();
    for (size_t i = 0; i < size; i++) {
        // c_str return a "const char *" type, so we need to copy the origin string 
        auto len = words[i].size();
        char* temp = new char[len + 1];
        strcpy_s(temp, len + 1, words[i].c_str());
        result[i] = temp;
    }
    return 0;
}

int output2result_python(std::vector<std::string> words, char* result[]) {
    std::string result_string = "";
    size_t len = words.size();
    for (size_t i = 0; i < len; i++) {
        auto len = words[i].size();
        result_string = result_string + words[i] + "\n";
    }
    strcpy_s(*result, result_string.size() + 1, result_string.c_str());
    return 0;
}
