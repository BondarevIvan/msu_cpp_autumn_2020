#include "parser.h"
#include <iostream>
#include <sstream>
#include <cassert>

std::ostringstream out("");

void digitalCallback(int value)
{
    out << value << "";
}

void StringCallback(const std::string& str)
{
    if (str == "{CURRENT_YEAR}")
        out << 2020;
    else
        out << str;
}

int main()
{
    NParser::TokenParser parser1("year:0{CURRENT_YEAR}");
    parser1.setDigitStringCallback(digitalCallback);
    parser1.setStringCallback(StringCallback);
    parser1.setStartCallback([](const std::string& s)
    {
        out << "\n";
    });
    parser1.setFinishCallback([](const std::string& s)
    {
        out << "\n";
    });
    parser1.parse();
    assert(out.str() == "\nyear:02020\n");
    std::string result;
    NParser::TokenParser parser2("");
    parser2.setDigitStringCallback(digitalCallback);
    parser2.setStringCallback(StringCallback);
    parser2.setStartCallback([&result](const std::string& s)
    {
        result += "begin\n";
    });
    parser2.setFinishCallback([&result](const std::string& s)
    {
        result += "end\n";
    });
    parser2.parse();
    assert(result == "begin\nend\n");
    std::cout << "\nSUCCESS!!!!!!!!!!!\n";
    return 0;
}