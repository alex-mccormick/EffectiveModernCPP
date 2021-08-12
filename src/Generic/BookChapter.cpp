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
    int optionIndex = 0;
    std::unordered_map<int, MenuFunction> functionMapping = {};
        
    for (auto const& menuOption : this->menuMap)
    {
        functionMapping.emplace(++optionIndex, menuOption.second);
    }
    
	while (!exit)
    {
        optionIndex = 0;
        std::cout << "Menu: " << this->chapterName << std::endl;
        for (const auto& menuOption : this->menuMap)
        {
            std::cout << ++optionIndex << ". " << menuOption.first << std::endl;
        }
        std::cout << "0. Exit" << std::endl;
        
        int selection;
        std::cin >> selection;

        if (selection == 0)
        {
            exit = true;
        }
        else if (selection <= this->menuMap.size())
        {
            functionMapping[selection]();
        }

        std::cout << std::endl << std::endl;
    }

}