#include <iostream>
#include <vector>
#include <ctime>
#include <string>

#include <tgbot/tgbot.h>

#include "ReviewBot.h"
#include "../BotTools/BotTools.h"

namespace review_bot {
    int InitBot(TgBot::Bot& bot, std::int64_t chatId, bool admin) {
        TgBot::InlineKeyboardMarkup::Ptr keyboardInit(new TgBot::InlineKeyboardMarkup);
        keyboardInit->inlineKeyboard.push_back(CreateLineButtons({{"Оставить отзыв", ADD_REVIEW}}));

        if (admin) {
            keyboardInit->inlineKeyboard.push_back(CreateLineButtons({{"Работать с мероприятиями", EVENT_WORKING}}));
        }
        bot.getApi().sendMessage(chatId, "Привяу!", false, 0, keyboardInit);

        return 0;
    }  
};