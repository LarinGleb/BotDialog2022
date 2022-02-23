#include "BotTools.h"


std::vector<std::string> ArgumentsCommand(std::string command) {
    size_t indexStart = 1;
    size_t indexEnd; 
    
    std::string argument;
    std::vector<std::string> arguments;

    while ((indexEnd = command.find(SEPARATOR, indexStart)) != std::string::npos) {
        argument = command.substr(indexStart, indexEnd - indexStart);
        indexStart = indexEnd + 1;
        arguments.push_back(argument);
    }

    arguments.push_back(command.substr(indexStart));
    arguments.erase(arguments.begin());
    
    return arguments;
}


std::string ConcatString(std::vector<std::string> concat) {
    std::string concatString;
    for (std::string word: concat) {
        concatString += word + " ";
    }
    return concatString;
}