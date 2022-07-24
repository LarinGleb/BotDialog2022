
#ifndef __KEY_BOARD_H__

#define __KEY_BOARD_H__

#include <tgbot/tgbot.h>

TgBot::InlineKeyboardButton::Ptr CreateButtonTG(const std::string textButton, const std::string callBackData);

// Return concated string of massive
std::string ConcatString(std::vector<std::string> concat); 

 // Return massive of arguments of command
std::vector<std::string> ArgumentsCommand(const std::string command);

#endif