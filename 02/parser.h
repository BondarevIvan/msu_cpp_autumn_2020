#pragma once
#include <functional>
#include <string>


namespace NParser
{
    using StringCallback = std::function<void(const std::string&)>;
    using DigitCallback = std::function<void(int)>;
    using StartFinishStringCallback = std::function<void(const std::string&)>;

    class TokenParser
    {
    public:
        TokenParser();
        TokenParser(const std::string& pattern);
        TokenParser(const TokenParser&) = delete;
        void setStartCallback(StartFinishStringCallback callback);
        void setFinishCallback(StartFinishStringCallback callback);
        void setStringCallback(StringCallback callback);
        void setDigitStringCallback(DigitCallback callback);
        void parse();
        void setPattern(const std::string& pat);
    private:
        std::string pattern;
        StringCallback stringCallback;
        DigitCallback digitalCallback;
        StartFinishStringCallback startStringCallback;
        StartFinishStringCallback finishStringCallback;
    private:
        void init();
    };
}