#include "parser.h"

#include <iostream>

namespace NParser
{
    TokenParser::TokenParser() : pattern{}
    {
        init();
    }
    TokenParser::TokenParser(const std::string& pattern) : pattern(pattern)
    {
        init();
    }
    void TokenParser::setStartCallback(StartFinishStringCallback callback)
    {
        startStringCallback = std::move(callback);
    }
    void TokenParser::setFinishCallback(StartFinishStringCallback callback)
    {
        finishStringCallback = std::move(callback);
    }
    void TokenParser::setStringCallback(StringCallback callback)
    {
        stringCallback = std::move(callback);
    }
    void TokenParser::setDigitStringCallback(DigitCallback callback)
    {
        digitalCallback = std::move(callback);
    }
    void TokenParser::parse()
    {
        startStringCallback(pattern);
        enum EState
        {
            ES_NONE,
            ES_IN_DIGIT,
            ES_IN_TOKEN,
        };
        EState state = EState::ES_NONE;
        std::string currentElement = "";
        auto isDigit = [](char sym) -> bool
        {
            return sym >= '0' && sym <= '9';
        };
        for (auto sym : pattern)
        {
            if (isDigit(sym))
            {
                if (state == EState::ES_NONE)
                    state = EState::ES_IN_DIGIT;
                if (state == EState::ES_IN_DIGIT)
                {
                    currentElement.push_back(sym);
                }
                else if (state == EState::ES_IN_TOKEN)
                {
                    stringCallback(currentElement);
                    currentElement = std::string({ sym });                    
                }
                state = EState::ES_IN_DIGIT;
            } else
            {   
                if (state == EState::ES_NONE)
                    state = EState::ES_IN_TOKEN;
                if (state == EState::ES_IN_DIGIT)
                {
                    digitalCallback(std::stoi(currentElement));
                    currentElement = std::string({ sym });
                }
                else if (state == EState::ES_IN_TOKEN)
                {
                    currentElement.push_back(sym);
                }
                state = EState::ES_IN_TOKEN;
            }
        }
        if (!currentElement.empty())
        {
            if (state == EState::ES_IN_DIGIT)
            {
                digitalCallback(std::stoi(currentElement));
            } else if (state == EState::ES_IN_TOKEN)
            {
                stringCallback(currentElement);
            }
        }
        finishStringCallback(pattern);
    }
    void TokenParser::setPattern(const std::string& pat)
    {
        pattern = pat;
    }
    void TokenParser::init()
    {
        setStartCallback([](const std::string&)
        {

        });
        setFinishCallback([](const std::string&)
        {

        });
        setStringCallback([](const std::string&)
        {

        });
        setDigitStringCallback([](int)
        {

        });
    }

}