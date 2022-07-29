#include <vector>
#include <string>

// merge with Review.cpp

#include <tgbot/tgbot.h>
#include "Review.h"
#include "../Event/Event.h"
#include "../States.h"
#include "../../BotTools/BotTools.h"
#include "../ReviewBot.h"

namespace review_bot
{
    std::string EstString(review_bot::vector_string ests)
    {
        std::string estString = std::string("");
        for (std::size_t i = 0; i < ests.size(); i++)
        {
            estString += ests.at(i) + (i < ests.size() - 1 ? ";" : "");
        }
        estString = (estString == "") ? NO_EST : estString;
        return estString;
    }

    bool IsInt(std::string est)
    {
        for (int i = 0; i < est.size(); i++)
        {
            if (!std::isdigit(est[i]))
            {
                return false;
            }
        }
        return std::stoi(est) <= 10 && std::stoi(est) >= 0;
    }

    int MoreEventQuestions(TgBot::Bot &bot, std::int64_t chatId)
    {
        TgBot::InlineKeyboardMarkup::Ptr moreEvents(new TgBot::InlineKeyboardMarkup);
        moreEvents->inlineKeyboard.push_back(CreateLineButtons({{"Да", YES}, {"Нет", NO}}));
        bot.getApi().sendMessage(chatId, "Хотите ли вы больше подобных мероприятий?", false, 0, moreEvents);
        return 0;
    }

    int AddReviewAdditional(TgBot::Bot &bot, std::int64_t chatId)
    {
        TgBot::InlineKeyboardMarkup::Ptr skip(new TgBot::InlineKeyboardMarkup);
        skip->inlineKeyboard.push_back(CreateLineButtons({{"Пропустить", SKIPADD}}));
        bot.getApi().sendMessage(chatId, "Если хотите добавить что-то ещё, то введите это сюда?", false, 0, skip);
        return 0;
    }

    review_bot::vector_string ActiveQuestion(int type)
    {
        switch ((review_bot::EventType)type)
        {
        case MIND:
            return review_bot::vector_string{"Оцените интеллектуальную сложность заданий по 10-и бальной шкале, где 0 - \"слишком сложно, вообще не понял/слишком легко\", а 10 - \"всё по моим силам!\"."};
        case RUNNING:
            return review_bot::vector_string{"Задания были по вашим силам? Оцените по 10-и бальной шкале, где 0 - \"слишком сложно, после мероприятия всё болело\", а 10 - \"всё по моим силам!\"."};
        case COMBO:
            return review_bot::vector_string{"Оцените интеллектуальную сложность заданий по 10-и бальной шкале, где 0 - \"слишком сложно, вообще не понял/слишком легко\", а 10 - \"всё по моим силам!\".",
                                             "Задания были по вашим силам? Оцените по 10-и бальной шкале, где 0 - \"слишком сложно, после мероприятия всё болело\", а 10 - \"всё по моим силам!\"."};
        case VIEWER:
            return review_bot::vector_string{"Понравилось ли вам мероприятие в целом? Оцените по 10-и бальной шкале, где 0 - \"не понравилось вовсе\", а 10 - \"запомню надолго\"."};
        case INVALID_EVENT_TYPE:
            throw std::invalid_argument("NULL type in switch! !");
        }
    }

    review_bot::vector_string StructQuestion(int type)
    {
        switch ((review_bot::StructType)type)
        {
        case CP:
            return review_bot::vector_string{"Было ли понятны расположения КП? Оцените по 10-и бальной шкале, где 0 - \"в итоге я их на нашёл\", а 10 - \"всё интуитивно понятно\".",
                                             "Понятные ли было задания на КП? Оцените по 10-и бальной шкале, где 0 - \"вообще никто не решил\", а 10 - \"всё понятным, задание было классным!\".",
                                             "Как вы оцениваете поведение преподователей на КП? Оцените по 10-и бальной шкале, где 0 - \"еле-еле убежал\", а 10 - \"прекрасные люди на прекрасных КП\"."};
        case RELAY:
            return review_bot::vector_string{"Эстафеты были сбалансированы? Оцените по 10-и бальной шкале, где 0 - \"не все могли пройти\", а 10 - \"все были равны\".",
                                             "Эстафеты были сами по себе сложные? Оцените по 10-и бальной шкале, где 0 - \"даже преподы не решили!\", а 10 - \"все смогли решить.\"."};

        case TASKS:
            return review_bot::vector_string{"Понравились ли вам задания? Оцените по 10-и бальной шкале, где 0 - \"не понравилось вовсе, ничего не помню\", а 10 - \"лучшие задания, запомню надолго\"."};
        case NO_TASKS:
            return review_bot::vector_string{NO_QUESTION};

        case NONE_STRUCT:
            throw std::invalid_argument("NULL type in switch! !");
        }
    }

    review_bot::vector_string CommandQuestion(int type)
    {
        switch ((review_bot::CommandType)type)
        {
        case COMMAND:
            return review_bot::vector_string{"Было ли вам комфортно в команде? Оцените от 0 до 10, где 0 - \"никогда больше не вернусь\", а 10 - \"хоть бы ещё раз попасть в неё\".",
                                             "Был ли баланс в командах? Оцените от 0 до 10, где 0 - \"там команда, которая всех вынесла!\", а 10 - \"все команды  равны\".",
                                             "Комадна была командой? Оцените от 0 до 10, где 0 - \"нет, каждый сам по себе\", а 10 - \"один за всех, и все за одного!\"."};
        case ALONE:
        case ALL_TOGETHER:
            return review_bot::vector_string{NO_QUESTION};

        case NONE_COMMAND:
            throw std::invalid_argument("NULL type in switch! !");
        }
    }
};
