#pragma once

#include <string>

struct Word {
    char first;
    char last;
    //TODO content array
    std::string content;

    Word(std::string content) {
        this->content = content;
        this->first = content[0];
        this->last = content.back();
    };
};