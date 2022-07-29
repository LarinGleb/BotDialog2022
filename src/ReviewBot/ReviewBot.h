#ifndef __REVIEW_BOT_H__
#define __REVIEW_BOT_H__

#include <map>

#include <tgbot/tgbot.h>

#include "Event/Event.h"
#include "States.h"

#define END_EST 2
#define SEPARATOR_DEFAULT ';'
#define REVIEW_BOT "Review"
#define CHANGE_TIME "ChangeTime"
// ----------------------------- FOR ADD REVIEW DEFINES -----------------------------
#define ADD_REVIEW "AddReview"

#define YES "YesAnswerMore"
#define NO "NoAnswerMore"
#define SKIPADD "SkipAdditional"
#define CURRENT_YEAR "CurrentYear"

#define EVENT_WORKING "EventWorking"
#define FIND_EVENT "FindEvent"

#define RETURN_TO_MAIN "ReturnToMain"
// ----------------------------- FOR ADD EVENT DEFINES -----------------------------
#define ADD_EVENT "AddEvent"

#define READ_REVIEW "ReadReview"

#define SET_TIME_NOW "SetTimeNow"
#define SET_TIME "SetTime"
#define SET_NAME "SetName"

#define SET_ACTIVE "SetActive"
#define MIND_TYPE "Mind" 
#define RUN_TYPE "Run"
#define COMBO_TYPE "Combo"
#define VIEWER_TYPE "Viewer"

#define SET_QUESTION "SetQuestion"
#define RELAY_TYPE "Relay"
#define CP_TYPE "Cp"
#define TASKS_TYPE "Tasks"
#define NO_TASKS_TYPE "NoTasks"

#define SET_COMMAND "SetCommand"
#define COMMAND_TYPE "Command"
#define ALONE_TYPE "Alone"
#define ALL_TYPE "All"

#define ADD_EVENT_BD "AddEventBD"

namespace review_bot {
    typedef std::vector<std::string> vector_string;
    int InitBot(TgBot::Bot& bot, std::int64_t chatId, bool admin);
    int CreateEvent(TgBot::Bot& bot, std::int64_t chatId, review_bot::Event event);
    int MenuEvent(TgBot::Bot& bot, std::int64_t chatId);
    int ChooseWork(TgBot::Bot& bot, std::int64_t chatId);

    int SetNameState(TgBot::Bot &bot, std::int64_t chatId);
    int SetTimeState(TgBot::Bot& bot, std::int64_t chatId);
    int SetBodyState(TgBot::Bot& bot, std::int64_t chatId);
    int SetStructState(TgBot::Bot& bot, std::int64_t chatId);
    int SetCommandState(TgBot::Bot& bot, std::int64_t chatId);

    int ChooseEvent(TgBot::Bot& bot, std::int64_t chatId, review_bot::vector_string names);
    int ChooseYear(TgBot::Bot& bot, std::int64_t chatId);
    
    int AddReviewAdditional(TgBot::Bot& bot, std::int64_t chatId);
    int MoreEventQuestions(TgBot::Bot& bot, std::int64_t chatId);
    
    review_bot::vector_string ActiveQuestion(int type);
    review_bot::vector_string StructQuestion(int type);
    review_bot::vector_string CommandQuestion(int type);

    std::string EstString(review_bot::vector_string ests);
    bool IsInt(std::string est);

    std::vector<std::string> SeparateEst(std::string est);
    
    std::string StatisticEst(std::vector<std::string> ests);
    std::string StatisticMore(std::vector<int> more);
    std::string SaveReviews(std::string nameEvent, std::string data, review_bot::vector_string reviews);

    
};

#endif
