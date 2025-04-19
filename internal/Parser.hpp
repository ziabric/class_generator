#ifndef PARSER_H
#define PARSER_H

// std
#include <vector>

// args
#include <thirdparty/cxxopts.hpp>

struct ParserResult
{
    std::vector<std::string> errors;
    bool view{false};
    bool viewPrivate{false};
    std::string viewName;
    bool model{false};
    bool modelPrivate{false};
    std::string modelName;
    std::string outputPath;
    std::string nsName;

};

inline ParserResult parse(int argc, char** argv)
{
    cxxopts::Options options("Class generator", "");
    options.add_options()
        ("help", "Help string")
        ("view", "Generate view class")
        ("view_private", "Generate view private class")
        ("view_name", "Generate view name", cxxopts::value<std::string>()->default_value("View"))
        ("namespace_name", "Namespace name", cxxopts::value<std::string>()->default_value("NS"))
        ("path", "Output dir", cxxopts::value<std::string>()->default_value("."))
        ;

    cxxopts::ParseResult result;
    ParserResult pr;

    try {
        result = options.parse(argc, argv);
    } catch (...) {
        pr.errors.push_back("Parse error");
        return pr;
    }

    if (result.contains("view"))
        pr.view = result["view"].as<bool>();
    if (result.contains("view_private"))
        pr.viewPrivate = result["view_private"].as<bool>();
    if (result.contains("view_name"))
        pr.viewName = result["view_name"].as<std::string>();
    if (result.contains("namespace_name"))
        pr.nsName = result["namespace_name"].as<std::string>();
    if (result.contains("path"))
        pr.outputPath = result["path"].as<std::string>();

    return pr;
}


#endif // PARSER_H
