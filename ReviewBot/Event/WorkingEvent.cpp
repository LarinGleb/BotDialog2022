#include <iostream>
// merge with Event.cpp

#include <tgbot/tgbot.h>

#include "../../BotTools/BotTools.h"
#include "../ReviewBot.h"
#include "../Time/Time.h"

namespace review_bot
{

    int ChooseEvent(TgBot::Bot &bot, std::int64_t chatId, review_bot::vector_string names)
    {
        TgBot::InlineKeyboardMarkup::Ptr eventsButtons(new TgBot::InlineKeyboardMarkup);
        for (std::string name : names)
        {
            eventsButtons->inlineKeyboard.push_back(CreateLineButtons({{name, name}}));
        }
        bot.getApi().sendMessage(chatId, "Выберите мероприятие: ", false, 0, eventsButtons);
        return 0;
    }

    int ChooseYear(TgBot::Bot &bot, std::int64_t chatId)
    {
        TgBot::InlineKeyboardMarkup::Ptr yearCurrent(new TgBot::InlineKeyboardMarkup);
        int currentYear = GetTmCurrentDay()->tm_year + 1900;

        yearCurrent->inlineKeyboard.push_back(CreateLineButtons({{"Текущий год: " + std::to_string(currentYear), CURRENT_YEAR}}));

        bot.getApi().sendMessage(chatId, "Введите год, когда было мероприятие: ", false, 0, yearCurrent);
        return 0;
    }

    int MenuEvent(TgBot::Bot &bot, std::int64_t chatId)
    {
        TgBot::InlineKeyboardMarkup::Ptr menuEvent(new TgBot::InlineKeyboardMarkup);
        menuEvent->inlineKeyboard.push_back(CreateLineButtons({{"Нет, добавить новое", ADD_EVENT}}));
        menuEvent->inlineKeyboard.push_back(CreateLineButtons({{"Да, найти его", FIND_EVENT}}));

        bot.getApi().sendMessage(chatId, "Ваше мероприятие уже есть?", false, 0, menuEvent);
        return 0;
    }

    int ChooseWork(TgBot::Bot &bot, std::int64_t chatId)
    {
        TgBot::InlineKeyboardMarkup::Ptr menuEvent(new TgBot::InlineKeyboardMarkup);
        menuEvent->inlineKeyboard.push_back(CreateLineButtons({{"Прочитать отзывы", READ_REVIEW}}));
        menuEvent->inlineKeyboard.push_back(CreateLineButtons({{"Изменить время", CHANGE_TIME}}));
        menuEvent->inlineKeyboard.push_back(CreateLineButtons({{"Назад", RETURN_TO_MAIN}}));
        bot.getApi().sendMessage(chatId, "Ваше мероприятие уже есть?", false, 0, menuEvent);
        return 0;
    }

};
