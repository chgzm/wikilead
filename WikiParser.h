#ifndef WIKIPARSER_H
#define WIKIPARSER_H

#include <string>
#include <vector>
#include <regex>

#include "Param.h"

class WikiParser {
public:
    WikiParser();
    ~WikiParser();

    int parse(const Param& param);

private:
    std::vector<std::string> getLines(const std::string& str);
    std::string removeMarkups(const std::string& str);
    std::string getURLEncoding(const std::string& str);

    const std::string enBaseURL = 
        "https://en.wikipedia.org/w/api.php"
        "?action=query"
        "&prop=revisions"
        "&rvprop=content"
        "&rvslots=main"
        "&format=xml"
        "&titles=";

    const std::string jpBaseURL = 
        "https://ja.wikipedia.org/w/api.php"
        "?action=query"
        "&prop=revisions"
        "&rvprop=content"
        "&rvslots=main"
        "&format=xml"
        "&titles=";

    const std::regex italicBold    = std::regex(R"('{2,4}([^']*)'{2,4})");
    const std::regex link          = std::regex(R"(\[\[([^\]]*)\]\])");
    const std::regex linkWithText  = std::regex(R"(\[\[([^\]]*)\|([^\]]*)\]\])");
    const std::regex linkToSection = std::regex(R"(\[\[([\]]*)#([^\]]*)\|([^\]]*)\]\])");
    const std::regex inParenthesis = std::regex(R"(\(.*?\) )");
    const std::regex refTag        = std::regex(R"(<ref.*?</ref>)");

    std::string contents;
};

#endif
