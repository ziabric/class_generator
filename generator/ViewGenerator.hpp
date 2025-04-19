#ifndef VIEWGENERATOR_H
#define VIEWGENERATOR_H 

// std
#include <filesystem>
#include <fstream>
#include <ios>
#include <regex>
#include <string>
#include <vector>

// self
#include <internal/def.h>

static std::vector<std::string> ViewGenerator(
      std::string path
    , const std::string &nsName
    , const std::string &viewName
    , bool createPrivate = false
)
{
    namespace fs = std::filesystem;

    std::vector<std::string> errors;

    if (path = fs::absolute(path); !fs::exists(path))
    {
        errors.push_back("directory " + path + " not exist");
        return errors;        
    }

    // prepare class info
    auto publicViewVarMap = VIEW_VAR_MAP;
    publicViewVarMap["HEADER_GUARD"] = toUpperCase(nsName) + "_" + toUpperCase(viewName) + "_H";
    publicViewVarMap["NAMESPACE"] = nsName;
    publicViewVarMap["CLASS_NAME"] = viewName;
    publicViewVarMap["FILE_NAME"] = viewName;

    // get template file
    std::fstream templateHStream(DEPS_DIR_PATH + PUBLIC_VIEW_H, std::fstream::in);
    std::fstream templateCPPStream(DEPS_DIR_PATH + PRIVATE_VIEW_H, std::fstream::in);
    if (!templateHStream.is_open() || !templateCPPStream.is_open())
    {
        errors.push_back("Open template public view files error");
        return errors;
    }

    // create public class
    auto templateHString = std::string((std::istreambuf_iterator<char>(templateHStream)), std::istreambuf_iterator<char>());
    auto templateCPPString = std::string((std::istreambuf_iterator<char>(templateCPPStream)), std::istreambuf_iterator<char>());

    // close files
    templateCPPStream.close();
    templateHStream.close();

    // add key words
    for (const auto &var : publicViewVarMap)
    {
        std::regex regex(var.first, std::regex::flag_type::_S_basic);
        templateHString = std::regex_replace(templateHString, regex, var.second);
        templateCPPString = std::regex_replace(templateCPPString, regex, var.second);
    }

    // write public class to files
    std::fstream publicHOutput(path + "/" + viewName + ".h", std::ios_base::out);
    std::fstream publicCPPOutput(path + "/" + viewName + ".cpp", std::ios_base::out);
    
    if (!publicHOutput.is_open() || !publicCPPOutput.is_open())
    {
        errors.push_back("Write public class to files error");
        return errors;
    }
    publicHOutput << templateHString;
    publicCPPOutput << templateCPPString;
    publicHOutput.close();
    publicCPPOutput.close();

    if (!createPrivate)
        return errors;

    // TODO: create private 

    return errors;
}


#endif // VIEWGENERATOR_H
