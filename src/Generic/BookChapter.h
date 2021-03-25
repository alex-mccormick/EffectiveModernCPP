#pragma once
#include "../include/stdafx.h"
#include <unordered_map>
#include <string>

class BookChapter {

    public:
        typedef void (*MenuFunction)(void);
        typedef std::unordered_map<std::string, MenuFunction> MenuMap;
        MenuMap menuMap;
        std::string chapterName;

        BookChapter(std::string);
        ~BookChapter(void);
        
        void RunChapter(void);
};