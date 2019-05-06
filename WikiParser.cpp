#include "WikiParser.h"

#include <rapidxml/rapidxml.hpp>
#include <curl/curl.h>
#include <cstdio>
#include <cstring>
#include <iomanip>

#include <iostream>
#include <fstream>
#include <sstream>

#include <regex>

WikiParser::WikiParser()
{
}

WikiParser::~WikiParser()
{
}

static std::size_t callback(char* ptr, std::size_t size, std::size_t nmemb, std::string* contents)
{
    const std::size_t realSize = size * nmemb;
    contents->append(ptr, realSize);

    return realSize;
}

int WikiParser::parse(const Param& param)
{
    std::string url;
    switch (param.lang) {
    case Lang::EN: { 
        url = this->enBaseURL + param.word; 
        break; 
    }
    case Lang::JP: { 
        url = this->jpBaseURL + param.word;
        break;
    }
    default: { 
        return -1;
    }
    }

    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL,            url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,  callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,      &(this->contents));
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    if (curl_easy_perform(curl) != CURLE_OK) {
        std::fprintf(stderr, "curl_easy_perform failed.\n");
        return -1;
    }

    curl_easy_cleanup(curl);

    rapidxml::xml_document<> doc;
    doc.parse<0>((char*)(this->contents.c_str()));

    const rapidxml::xml_node<>* node = doc.first_node();
    if (node == nullptr) {
        return -1;
    }

    while (true) {
        if (std::string(node->name()) == "slot") {
            const std::string value(node->value());
            const std::vector<std::string> lines = this->getLines(value);

            for (const std::string& line : lines) {
                if (line.size() == 0) {
                    continue;
                }

                if (line[0] == ' ' || 
                    line[0] == '|' || 
                    line[0] == '{' || 
                    line[0] == '}' || 
                    line[0] == '[' ||
                    line[0] == '<'
                ) {
                    continue;
                }

                std::printf("%s\n",this->removeMarkups(line).c_str());

                return 0;
            }                        
    
            std::fprintf(stderr, "cannot find sentense.\n");
            return -1;
        } 

        if (node->next_sibling() != nullptr) {
            node = node->next_sibling();
        } else if (node->first_node() != nullptr) {
            node = node->first_node();
        } else {
            std::fprintf(stderr, "cannot find node.\n");
            return -1;
        }
    }
}

std::string WikiParser::getURLEncoding(const std::string& str)
{
    std::stringstream ss;
    ss << std::hex;

    for (std::size_t i = 0; i < str.size(); ++i) {
        ss << "%" << std::setfill('0') << std::setw(2) << (int)((uint8_t)(str[i]));
    }

    return ss.str();
}

std::vector<std::string> WikiParser::getLines(const std::string& str)
{
    std::stringstream ss(str);

    std::string line;
    std::vector<std::string> ret;
    while (std::getline(ss, line)) {
        ret.push_back(line);
    }
    
    return ret;
}

std::string WikiParser::removeMarkups(const std::string& str)
{
    const std::string str1 = std::move(std::regex_replace(str,  this->italicBold,    "$1"));
    const std::string str2 = std::move(std::regex_replace(str1, this->linkToSection, "$3"));
    const std::string str3 = std::move(std::regex_replace(str2, this->linkWithText,  "$2"));
    const std::string str4 = std::move(std::regex_replace(str3, this->link,          "$1"));
    const std::string str5 = std::move(std::regex_replace(str4, this->refTag,        ""));
    const std::string str6 = std::move(std::regex_replace(str5, this->inParenthesis, ""));

    return str6;
}
