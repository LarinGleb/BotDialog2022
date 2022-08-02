#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>

#include <tgbot/tgbot.h>

#include "Review.h"
#include "../ReviewBot.h"
#include "../Event/Event.h"
#include "../States.h"

namespace review_bot {

    std::vector<std::string> SeparateEst(const std::string est) {
        std::vector<std::string> estsVector = {};

        std::stringstream ss(est);
        std::string item;
        while(std::getline(ss, item, (char)SEPARATOR_DEFAULT)) {
            estsVector.push_back(item);
        }
        return estsVector;
    }

    std::string StatisticEst(const std::vector<std::string> ests) {
        std::string statistic = std::string("");
        for (int i = MIN_EST; i <= MAX_EST; i ++) {
            statistic += std::string("Количество оценок ") + std::to_string(i) + std::string(" составляет ") + std::to_string(std::count(ests.begin(), ests.end(), std::to_string(i))) + std::string(".\n");
        }
        return statistic;
    }

    std::string StatisticMore(const std::vector<int> more) {
        std::string statistic = std::string("");
        statistic += std::string("Количество \"да, мы хотим ещё!\": ") + std::to_string(std::count(more.begin(), more.end(), NEED_MORE_EVENT)) + std::string(".\n");
        statistic += std::string("Количество \"нет, не хотим!\": ") + std::to_string(std::count(more.begin(), more.end(), DONT_NEED_MORE_EVENT)) + std::string(".\n");
        return statistic;
    }

    std::string SaveReviews(const std::string nameEvent, const std::string data, const std::vector<std::string> reviews) {
        std::ofstream reviewFile;
        std::string fileDir = "../tempReviews/" + data + "_" + nameEvent + ".txt";
        reviewFile.open(fileDir, std::ofstream::out | std::ofstream::trunc);
        if(reviewFile.is_open()) {
            for(std::string review: reviews) {
                if (review != NO_ADDITIONAL) {
                    reviewFile << review + "\n";
                }
            }
            reviewFile.close();
        }
        else std::cout << "Файл не открылся для записи";
        return fileDir;
    }
    std::string EstString(const std::vector<std::string> ests) {
        std::string estString = std::string("");
        for (std::size_t i = 0; i < ests.size(); i ++) {
            estString += ests.at(i) + (i < ests.size() - 1 ? ";": "");
        }
        estString = (estString == "") ? NO_EST: estString;
        return estString;    
    }

    bool IsInt(const std::string est) { 
        if (est.size() > 2) {
            return false;
        }
	    for (int i = 0; i < est.size(); i++) {
       	    if (!std::isdigit(est[i])) {
                return false;
        }
	}
        return std::stoi(est) <= 10 && std::stoi(est) >= 0;
    }
    int MoreEventQuestions(const TgBot::Bot& bot,const std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr moreEvents(new TgBot::InlineKeyboardMarkup);
        moreEvents->inlineKeyboard.push_back(CreateLineButtons({{"Да", YES}, {"Нет", NO}}));
        bot.getApi().sendMessage(chatId, "Хотите ли вы больше подобных мероприятий?", false, 0, moreEvents);
        return 0;
    }

    int AddReviewAdditional(const TgBot::Bot& bot,const std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr skip(new TgBot::InlineKeyboardMarkup);
        skip->inlineKeyboard.push_back(CreateLineButtons({{"Пропустить", SKIPADD}}));
        bot.getApi().sendMessage(chatId, "Если хотите добавить что-то ещё, то введите это сюда?", false, 0, skip);
        return 0;
    }

    std::vector<std::string> ActiveQuestion(const review_bot::EventType type) {
        switch(type) {
            case MIND:
                return std::vector<std::string> {"Оцените интеллектуальную сложность заданий по 10-и бальной шкале, где 0 - \"слишком сложно, вообще не понял/слишком легко\", а 10 - \"всё по моим силам!\"."};
            case RUNNING:
                return std::vector<std::string> {"Задания были по вашим силам? Оцените по 10-и бальной шкале, где 0 - \"слишком сложно, после мероприятия всё болело\", а 10 - \"всё по моим силам!\"."};
            case COMBO:
                return std::vector<std::string> {"Оцените интеллектуальную сложность заданий по 10-и бальной шкале, где 0 - \"слишком сложно, вообще не понял/слишком легко\", а 10 - \"всё по моим силам!\".", 
                                                  "Задания были по вашим силам? Оцените по 10-и бальной шкале, где 0 - \"слишком сложно, после мероприятия всё болело\", а 10 - \"всё по моим силам!\"."};
            case VIEWER:
                return std::vector<std::string> {"Понравилось ли вам мероприятие в целом? Оцените по 10-и бальной шкале, где 0 - \"не понравилось вовсе\", а 10 - \"запомню надолго\"."};
            case INVALID_EVENT_TYPE:
                throw std::invalid_argument("NULL type in switch! !");
        }   
    }
    std::vector<std::string> StructQuestion(const review_bot::EventStructType type) {
        switch(type) {
            case CP:
                return std::vector<std::string> {"Было ли понятны расположения КП? Оцените по 10-и бальной шкале, где 0 - \"в итоге я их на нашёл\", а 10 - \"всё интуитивно понятно\".",
                                                 "Понятные ли было задания на КП? Оцените по 10-и бальной шкале, где 0 - \"вообще никто не решил\", а 10 - \"всё понятным, задание было классным!\".",
                                                 "Как вы оцениваете поведение преподователей на КП? Оцените по 10-и бальной шкале, где 0 - \"еле-еле убежал\", а 10 - \"прекрасные люди на прекрасных КП\"."};
            case RELAY:
                return std::vector<std::string> {"Эстафеты были сбалансированы? Оцените по 10-и бальной шкале, где 0 - \"не все могли пройти\", а 10 - \"все были равны\".",
                                                  "Эстафеты были сами по себе сложные? Оцените по 10-и бальной шкале, где 0 - \"даже преподы не решили!\", а 10 - \"все смогли решить.\"."};

            case TASKS:
                return std::vector<std::string> {"Понравились ли вам задания? Оцените по 10-и бальной шкале, где 0 - \"не понравилось вовсе, ничего не помню\", а 10 - \"лучшие задания, запомню надолго\"."};
            case NO_TASKS:
                return std::vector<std::string> {NO_QUESTION};

            case INVALID_EVENET_STRUCT_TYPE:
                throw std::invalid_argument("NULL type in switch! !");
        }
    }

    std::vector<std::string> CommandQuestion(const review_bot::EventCommandType type) {
        switch (type)
        {
            case COMMAND:
                return std::vector<std::string>{"Было ли вам комфортно в команде? Оцените от 0 до 10, где 0 - \"никогда больше не вернусь\", а 10 - \"хоть бы ещё раз попасть в неё\".", 
                                                 "Был ли баланс в командах? Оцените от 0 до 10, где 0 - \"там команда, которая всех вынесла!\", а 10 - \"все команды  равны\".", 
                                                 "Комадна была командой? Оцените от 0 до 10, где 0 - \"нет, каждый сам по себе\", а 10 - \"один за всех, и все за одного!\"."};
            case ALONE:
            case ALL_TOGETHER:
                return std::vector<std::string>{NO_QUESTION};
            
            case INVALID_EVENT_COMMAND_TYPE:
                throw std::invalid_argument("NULL type in switch! !");
        }
    }
};