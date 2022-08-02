#ifndef __REVIEW_BOT_H__
#define __REVIEW_BOT_H__

#include <iostream>
#include <vector>
#include <tgbot/tgbot.h>

#include "../../utils/TelegramTools/TelegramTools.h"
#include "Event/Event.h"
#include "States.h"

#define END_EST 2
#define SEPARATOR_DEFAULT ';'
#define REVIEW_BOT "Review"

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
#define CHANGE_TIME "ChangeTime"
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
    int InitBot(const TgBot::Bot& bot,const std::int64_t chatId, const bool admin);
    int CreateEvent(const TgBot::Bot& bot,std::int64_t chatId, review_bot::Event event);
    int MenuEvent(const TgBot::Bot& bot,std::int64_t chatId);
    int ChooseWork(const TgBot::Bot& bot,const std::int64_t chatId);
    int SetNameState(const TgBot::Bot &bot,const std::int64_t chatId);
    int SetTimeState(const TgBot::Bot& bot,const std::int64_t chatId);
    int SetBodyState(const TgBot::Bot& bot,const std::int64_t chatId);
    int SetStructState(const TgBot::Bot& bot,std::int64_t chatId);
    int SetCommandState(const TgBot::Bot& bot,const std::int64_t chatId);
    int ChooseEvent(const TgBot::Bot& bot,const std::int64_t chatId, std::vector<std::string> names);
    int ChooseYear(const TgBot::Bot& bot,const std::int64_t chatId);
    int AddReviewAdditional(const TgBot::Bot& bot,const std::int64_t chatId);
    int MoreEventQuestions(const TgBot::Bot& bot,const std::int64_t chatId);
    std::vector<std::string> ActiveQuestion(const review_bot::EventType type);
    std::vector<std::string> StructQuestion(const review_bot::EventStructType type);
    std::vector<std::string> CommandQuestion(const review_bot::EventCommandType type);
    std::string EstString(const std::vector<std::string> ests);
    bool IsInt(const std::string est);
    std::vector<std::string> SeparateEst(const std::string est);
    std::string StatisticEst(const std::vector<std::string> ests);
    std::string StatisticMore(const std::vector<int> more);
    std::string SaveReviews(const std::string nameEvent, const std::string data,const std::vector<std::string> reviews);
};

#endif
