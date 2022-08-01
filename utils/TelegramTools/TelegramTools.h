#ifndef __KEY_BOARD_H__
#define __KEY_BOARD_H__
#include <map>

#include <tgbot/tgbot.h>

#define RETURN_MENU "ToMenu"

typedef std::map<std::string, std::string> buttonQuery;

inline TgBot::InlineKeyboardButton::Ptr CreateButtonTG(const std::string textButton, const std::string callBackData);
inline std::vector<TgBot::InlineKeyboardButton::Ptr> CreateLineButtons(const buttonQuery button);
inline std::vector<TgBot::InlineKeyboardButton::Ptr> ButtonToMenu();

#endif
