#include <iostream>
#include <vector> // for concat
#include <map>

#include <tgbot/tgbot.h>

#include "BotTools.h"

TgBot::InlineKeyboardButton::Ptr CreateButtonTG(const std::string textButton, const std::string callBackData) {
    TgBot::InlineKeyboardButton::Ptr Button(new TgBot::InlineKeyboardButton);
    Button->text = textButton;
    Button->callbackData = callBackData;
    return Button;

}
std::vector<TgBot::InlineKeyboardButton::Ptr> CreateLineButtons(buttonQuery buttons) {

    std::vector<TgBot::InlineKeyboardButton::Ptr> linebuttons;
    for (const std::pair<std::string, std::string> pair : buttons) {
        linebuttons.push_back(CreateButtonTG(pair.first, pair.second));
    }
    return linebuttons;
}

std::vector<TgBot::InlineKeyboardButton::Ptr> ButtonToMenu() {
    return CreateLineButtons({{"Назад", RETURN_MENU}});
}
