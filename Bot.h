
#ifndef __BOT_H__
#define __BOT_H__

#include <tgbot/tgbot.h>
#include <iostream>
#include "Connector/DataBase.h"
#include <string> 

// Errors and Succes keys
#define ErrorCommandInit 2
#define ErrorCommandWork 3
#define Success 0


std::string[] GetArgumentCommand(const std::string);
int InitBotCommands(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message); // Standart init commands for Bot
int main(); // main function 

#endif