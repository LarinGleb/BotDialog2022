#include <tgbot/tgbot.h>

#include "../ReviewBot.h"
#include "Event.h"
#include "../../BotTools/BotTools.h"
#include "../Time/Time.h"

namespace review_bot {
    int CreateEvent(TgBot::Bot& bot, std::int64_t chatId, review_bot::Event event) {
        TgBot::InlineKeyboardMarkup::Ptr createEvent(new TgBot::InlineKeyboardMarkup);
        createEvent->inlineKeyboard.push_back(CreateLineButtons({{"Название", SET_NAME}, {"Время", SET_TIME}}));
        createEvent->inlineKeyboard.push_back(CreateLineButtons({{"Вид активности", SET_ACTIVE}, {"Вид заданий", SET_QUESTION}}));
        createEvent->inlineKeyboard.push_back(CreateLineButtons({{"Разбиение на команды", SET_COMMAND}}));
        createEvent->inlineKeyboard.push_back(CreateLineButtons({{"Добавить мероприятие", ADD_EVENT_BD}}));
        std::string textEvent = std::string("Текущие характеристики мероприятия. ") + std::string("\n") + event.Info();
        bot.getApi().sendMessage(chatId, textEvent, false, 0, createEvent);
        return 0;
    }
    int SetTimeState(TgBot::Bot& bot, std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr nowTime(new TgBot::InlineKeyboardMarkup);
        nowTime->inlineKeyboard.push_back(CreateLineButtons({{"Поставить сегодняшнюю дату: " + GetStringDay(), SET_TIME_NOW}}));
        nowTime->inlineKeyboard.push_back(ButtonToMenu());

        bot.getApi().sendMessage(chatId, "Введите время в формате дд.мм.гггг", false, 0, nowTime);
        return 0;
    }

    int SetNameState(TgBot::Bot &bot, std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr name(new TgBot::InlineKeyboardMarkup);
        name->inlineKeyboard.push_back(ButtonToMenu());
        bot.getApi().sendMessage(chatId, "Введите название мероприятия:", false, 0, name);
        return 0;
    }

    int SetBodyState(TgBot::Bot& bot, std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr body(new TgBot::InlineKeyboardMarkup);
        body->inlineKeyboard.push_back(CreateLineButtons({{"Думательная", MIND_TYPE}, {"Бегательная", RUN_TYPE}}));
        body->inlineKeyboard.push_back(CreateLineButtons({{"Зрительная, без участия", VIEWER_TYPE}}));
        body->inlineKeyboard.push_back(CreateLineButtons({{"Смешанная", COMBO_TYPE}}));
        body->inlineKeyboard.push_back(ButtonToMenu());
        bot.getApi().sendMessage(chatId, "Выберите вид активности мероприятия:", false, 0, body);
        return 0;
    }

    int SetStructState(TgBot::Bot& bot, std::int64_t chatId) { 
        TgBot::InlineKeyboardMarkup::Ptr structQuestions(new TgBot::InlineKeyboardMarkup);
        structQuestions->inlineKeyboard.push_back(CreateLineButtons({{"Эстафеты", RELAY_TYPE}, {"КП", CP_TYPE}}));
        structQuestions->inlineKeyboard.push_back(CreateLineButtons({{"Задания", TASKS_TYPE}, {"Без заданий", NO_TASKS_TYPE}}));
        structQuestions->inlineKeyboard.push_back(ButtonToMenu());
        bot.getApi().sendMessage(chatId, "Выберите вид заданий мероприятия:", false, 0, structQuestions);
        return 0;
    }

    int SetCommandState(TgBot::Bot& bot, std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr structQuestions(new TgBot::InlineKeyboardMarkup);
        structQuestions->inlineKeyboard.push_back(CreateLineButtons({{"По одиночке", ALONE_TYPE}, {"По несколько человек", COMMAND_TYPE}}));    
        structQuestions->inlineKeyboard.push_back(CreateLineButtons({{"Весь лагерь вместе", ALL_TYPE},}));
        structQuestions->inlineKeyboard.push_back(ButtonToMenu());
        bot.getApi().sendMessage(chatId, "Выберите разбиение на команды:", false, 0, structQuestions);
        return 0;

    }
}