#ifndef __REVIEW_BOT_H__
#define __REVIEW_BOT_H__


#include <tgbot/tgbot.h>
#include <iostream>
#include "../BotTools/BotTools.h"
#include <vector>
#include <cmath>

#define COUNT_EVENT_IN_PAGE 10
#define Success 0

int InitReviewBot(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message);
int DeleteEventState(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message);
std::string GetPageMessage(int page, std::vector<std::string> events);
int ListEventsState(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message);
int StartCreatingState(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message);
int MenuCreateEventCP(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message);
int ChooseTypeEvent(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message);
int MenuCreateCP(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message);
int MenuDeleteCP(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message, std::vector<std::string> namesCP);

#endif