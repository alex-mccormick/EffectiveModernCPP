#include "BookChapter.h"

BookChapter::BookChapter(std::string chapterName)
{
    this->chapterName = chapterName;
}

BookChapter::~BookChapter()
{
}

void BookChapter::RunChapter()
{
    bool exit = false;
    int optionIndex = 1;
    std::unordered_map<int, MenuFunction> functionMapping = {};

	while (!exit)
    {
        std::cout << "Menu: " << this->chapterName << std::endl;
        for (auto const& menuOption : this->menuMap)
        {
            std::cout << optionIndex << ". " << menuOption.first << std::endl;
            functionMapping.emplace(optionIndex, menuOption.second);
        }
        std::cout << "0. Exit" << std::endl;
        
        int selection;
        std::cin >> selection;

        if (selection == 0)
        {
            exit = true;
        }
        else
        {
            functionMapping[selection]();
        }

        std::cout << std::endl;
    }

}