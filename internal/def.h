#ifndef DEF_H
#define DEF_H

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

#include <thirdparty/stc.hpp>

// Vars in templates

const std::map<std::string, std::string> VIEW_VAR_MAP = {
    {"HEADER_GUARD", ""}
    , {"NAMESPACE", ""}
    , {"CLASS_NAME", ""}
    , {"FILE_NAME", ""}
};


// Templates
const std::string DEPS_DIR_PATH = "../../deps/";
const std::string PUBLIC_VIEW_H = "ViewTemplate.h.txt";
const std::string PRIVATE_VIEW_H = "ViewTemplate.cpp.txt";




static std::string toUpperCase(std::string str) 
{
    std::transform(str.begin(), str.end(), str.begin(),
        [](unsigned char c){ return std::toupper(c); });
    return str;
}

template<typename Type>
static void printSMTH(Type smthInfo)
{
    std::cout << stc::rgb_fg(0, 255, 0) << smthInfo << stc::reset << std::endl;
}

#endif // DEF_H
