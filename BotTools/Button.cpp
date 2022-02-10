#include "BotTools.h"


TgBot::InlineKeyboardButton::Ptr CreateButtonTG(const std::string textButton, const std::string callBackData) {
    TgBot::InlineKeyboardButton::Ptr WriteNew(new TgBot::InlineKeyboardButton);
    WriteNew->text = textButton;
    WriteNew->callbackData = callBackData;
    return WriteNew;
}


