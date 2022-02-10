
#include "BotTools.h"

int InitReviewBot(TgBot::Bot& bot) {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> startReviewBotkeyBoard;

    startReviewBotkeyBoard.push_back(CreateButtonTG("Add event", "AddEvent"));
    keyboard->inlineKeyboard.push_back(startReviewBotkeyBoard);
    return 0;

}