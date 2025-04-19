

// std
#include <iostream>

// io colors
#include <thirdparty/stc.hpp>

// self
#include <internal/Parser.hpp>
#include <generator/ModelGenerator.hpp>
#include <generator/ViewGenerator.hpp>

void printErrors(const std::vector<std::string> &errors, const std::string &title = "Error")
{
    std::cout << stc::rgb_fg(255, 0, 0) << title << stc::reset << '\n' ;
    for (const auto &item : errors)
        std::cout << item << '\n';
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    auto parseResult = parse(argc, argv);
    if (!parseResult.errors.empty())
    {
        printErrors(parseResult.errors, "Parse errors");
        return 1;
    }

    if (parseResult.view)
    {
        auto result = ViewGenerator(
            parseResult.outputPath, 
            parseResult.nsName, 
            parseResult.viewName, 
            parseResult.viewPrivate
        );
        if (!result.empty())
            printErrors(result, "Create view errors");
    }
}



