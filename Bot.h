
#ifndef __BOT_H__
#define __BOT_H__

#include <tgbot/tgbot.h> // bot th lib
#include <iostream> // standart lib
#include "Connector/DataBase.h" // for working with sql
#include <functional>  // for hashing
#include "BotTools/BotTools.h"
#include "ReviewBot/ReviewBot.h"


// Errors and Succes keys
#define ErrorCommandInit 2
#define ErrorCommandWork 3
#define Success 0

// Get hash by string 
size_t GetHash(std::string String); 

// Standart init commands for Bot
int InitBotCommands(TgBot::Bot& bot); 

int main(); // main function 

#endif