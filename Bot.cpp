
#include "Bot.h"

int InitBotCommands(TgBot::Bot &bot) {
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });

    std::cout << "Command init successful" << "\n";
    return Success;
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
            conn.AddEvent(, 1);
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });
    TgBot::TgLongPoll longPoll(bot);
    while (true) {
        std::cout << "Long poll started" << "\n";
        longPoll.start();
    }

    return Success;
}