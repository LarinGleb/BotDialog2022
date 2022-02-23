#include "BotTools.h"


TgBot::InlineKeyboardButton::Ptr CreateButtonTG(const std::string textButton, const std::string callBackData) {
    TgBot::InlineKeyboardButton::Ptr Button(new TgBot::InlineKeyboardButton);
    Button->text = textButton;
    Button->callbackData = callBackData;
    return Button;

}
