#include "Bot.h"


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


int InitBotCommands(TgBot::Bot &bot) {
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });

    std::cout << "Command init successful" << "\n";
    return Success;
}


int GetHash(std::string String) {
    std::hash<std::string> hashThisString;
    return int(hashThisString(String));
}

int main() {
    TgBot::Bot bot("1940339152:AAG0jf4jVUk62ZmSHyPmrjlYCoMYPR-qjNk");
    const std::string username = "admin";
    const std::string hostname = "localhost";
    const std::string password = "19572006gG.";

    db_api::Connector conn(hostname.c_str(), username.c_str(), password.c_str(), "Reviews");

    InitBotCommands(bot);
    bot.getEvents().onAnyMessage([&bot, &conn](TgBot::Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        else if(StringTools::startsWith(message->text, "/create")) {
            std::string nameEvent = ConcatString(ArgumentsCommand(message->text));
            conn.AddEvent(nameEvent, GetHash(nameEvent));
            return;
        }
    });
    TgBot::TgLongPoll longPoll(bot);
    while (true) {
        std::cout << "Long poll started" << "\n";
        longPoll.start();
    }

    return Success;
}