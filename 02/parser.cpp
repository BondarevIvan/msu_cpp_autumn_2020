#include "parser.h"

#include <ctype.h>

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
    void TokenParser::setStartCallback(StartFinishStringCallback&& callback)
    {
        startStringCallback = std::move(callback);
    }
    void TokenParser::setFinishCallback(StartFinishStringCallback&& callback)
    {
        finishStringCallback = std::move(callback);
    }
    void TokenParser::setStringCallback(StringCallback&& callback)
    {
        stringCallback = std::move(callback);
    }
    void TokenParser::setDigitStringCallback(DigitCallback&& callback)
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
        auto changeState = [&](char sym)
        {
            if (state == EState::ES_IN_DIGIT)
            {
                digitalCallback(std::stoi(currentElement));
                state = EState::ES_IN_TOKEN;
            }
            else if (state == EState::ES_IN_TOKEN)
            {
                stringCallback(currentElement);
                state = EState::ES_IN_DIGIT;
            }
            currentElement = std::string({ sym });
        };
        for (auto sym : pattern)
        {
            EState currentState = EState::ES_IN_TOKEN;
            if (isdigit(sym))
                currentState = EState::ES_IN_DIGIT;
            if (state == EState::ES_NONE)
            {
                state = currentState;
            }
            if (currentState != state)
            {
                changeState(sym);
            } else
            {
                currentElement.push_back(sym);
            }
        }
        changeState('\0');
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