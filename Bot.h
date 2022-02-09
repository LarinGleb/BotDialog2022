
#ifndef __BOT_H__
#define __BOT_H__

#include <tgbot/tgbot.h> // bot th lib
#include <iostream> // standart lib
#include "Connector/DataBase.h" // for working with sql
#include <string>  // for working string
#include <vector> // for concat 
#include <functional>  // for hashing

// Errors and Succes keys
#define ErrorCommandInit 2
#define ErrorCommandWork 3
#define Success 0


#define SEPARATOR " "

int GetHash(std::string String); // Get hash by string 
std::string ConcatString(std::vector<std::string> concat); // Return Concat string of massive
std::vector<std::string> ArgumentsCommand(const std::string command); // Return massive of arguments
int InitBotCommands(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message); // Standart init commands for Bot
int main(); // main function 

#endif