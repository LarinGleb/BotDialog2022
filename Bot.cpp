#include <iostream> // standart lib
#include <algorithm>
#include <vector>
#include <functional>  // for hashing
#include <map>

#include <tgbot/tgbot.h> // bot th lib

#include "ReviewBot/ReviewBot.h"
#include "Bot.h"
#include "Connector/DataBase.h" // for working with sql
#include "BotTools/BotTools.h"
#include "ReviewBot/Event/Event.h"
#include "ReviewBot/Time/Time.h"

int GetIndex(const std::vector<std::string> array, const std::string elem) {
    return std::distance(std::begin(array), std::find(std::begin(array), std::end(array), elem));
}

int main() {

    const std::string username = USER_NAME;
    const std::string hostname = HOST_DB;
    const std::string password = PASSWORD;
    db_api::Connector conn(hostname.c_str(), username.c_str(), password.c_str(), DIALOG_DB);

    TgBot::Bot bot("1940339152:AAHzeE78ERa0LQDw_Ehj0rw6P01Z8j9eHPg");
    std::map<std::int64_t, User> Users = {};
    //Event.Clear();
    bot.getEvents().onAnyMessage([&bot, &Users, &conn](TgBot::Message::Ptr message) {
        if (Users.count(message->from->id) == 0) {
            Users[message->from->id] = User();
            
        }
        std::int64_t chatId = message->chat->id;
        User user = Users[message->from->id];
        State* botState = user.BotState;

        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        
        switch (*botState)
        {   
            case W_START:
                review_bot::InitBot(bot, chatId, true);
                *botState = W_COMMAND_REVIEW;
                break;
            case W_NAME:
                user.eventUser->SetName(message->text);
                review_bot::CreateEvent(bot, chatId, *(user.eventUser));
                *botState = CR_EVENT;
                break;

            case W_TIME:
                user.eventUser->SetTime(TimeFromString(message->text, DATA_FORMAT));
                review_bot::CreateEvent(bot, chatId, *(user.eventUser));
                *botState = CR_EVENT;
                break;

            case EST: {
                if (!review_bot::ValidEst(message->text)) {
                    bot.getApi().sendMessage(chatId, "Неверная оценка: она должна лежать между 0 и 10 включительно!");
                    return;
                }
                switch (*(user.flagTypeQuestion))
                {
                    case 0: user.reviewUser->AddActiveEst(message->text); break;
                    case 1: user.reviewUser->AddStructEst(message->text); break;
                    case 2: user.reviewUser->AddCommandEst(message->text); break;
                }   
                
                while (*(user.flagQuestion) == user.questions->at(*(user.flagTypeQuestion)).size() ||
                    NO_QUESTION == user.questions->at(*(user.flagTypeQuestion)).at(*(user.flagQuestion))) {
                    *(user.flagTypeQuestion) += 1;
                    *(user.flagQuestion) = 0;
                    if (*(user.flagTypeQuestion) == END_EST) {
                        review_bot::MoreEventQuestions(bot, chatId);
                        return;
                    }
                }
                bot.getApi().sendMessage(chatId, user.questions->at(*(user.flagTypeQuestion)).at(*(user.flagQuestion)));
                *(user.flagQuestion) += 1;
                break;
            }

            case ADDITIONAL_EST: {
                user.reviewUser->AddReview(message->text);
                conn.AddReview(*(user.nameEvent) , review_bot::EstString(user.reviewUser->ActiveEst()), 
                review_bot::EstString(user.reviewUser->StructEst()), review_bot::EstString(user.reviewUser->CommandEst()), 
                user.reviewUser->AdditionalReview(), user.reviewUser->MoreEvent());
                *botState = W_COMMAND_REVIEW;
                bot.getApi().sendMessage(chatId, "Спасибо за отзыв!");
                user.Clear();
                review_bot::InitBot(bot, chatId, true);
                
                break;
            }
            default:
                break;
        }
    });


    bot.getEvents().onCallbackQuery([&bot, &Users, &conn](TgBot::CallbackQuery::Ptr query) {
        std::string queryText = query->data;
        std::int64_t chatId = query->message->chat->id;
        User user = Users[query->from->id];
        State *botState = user.BotState;
        if (*botState == CHOOSE_EVENT_REVIEW_ADD) {
            user.QuestionsByTypes(conn.TypeEventByName(queryText));
            *botState = EST;
            *(user.nameEvent) = queryText;
            bot.getApi().sendMessage(chatId, user.questions->at(*(user.flagTypeQuestion)).at(*(user.flagQuestion)));  
            *(user.flagQuestion) += 1;
        }
        else if (*botState == CHOOSE_EVENT_REVIEW_READ) {
            
            user.QuestionsByTypes(conn.TypeEventByName(queryText));
            *(user.nameEvent) = queryText;

            std::vector<std::vector<std::string>> ests_all = conn.AllEsts(*(user.nameEvent));
            std::string fileDir = review_bot::SaveReviews(*(user.nameEvent), GenerateFormatSession(TimeFromString(conn.GetTime(*(user.nameEvent)), SQL_DATA_FORMAT)), conn.AllReviews(*(user.nameEvent)));
            
            for(int i = 0; i < 3; i ++ ) {
                review_bot::vector_string question = user.questions->at(i);
                if(question.at(0) == NO_QUESTION) {
                    continue;
                }
                for(int j = 0; j < question.size(); j++) {
                    std::vector<int> ests_type;
                    for (int k = 0; k < ests_all.size(); k++) { 
                        
                        ests_type.push_back(review_bot::SeparateEst(ests_all.at(k).at(i)).at(j));
                    }
                    std::string message = question.at(j) + std::string("\n") + review_bot::StatisticEst(ests_type);
                    bot.getApi().sendMessage(chatId, message);
                    
                } 
            }
            std::ifstream fileSend(fileDir);
            bot.getApi().sendMessage(chatId, "Хотят ли люди ещё подобных мероприятий? \n " + review_bot::StatisticMore(conn.MoreEvent(*(user.nameEvent))));
            if (fileSend.peek() == EOF) {
                bot.getApi().sendMessage(chatId, "Отзывов нет!");
            }
            else {
                bot.getApi().sendDocument(chatId, TgBot::InputFile::fromFile(fileDir, "text/plain"));
            }
            
            std::remove(fileDir.c_str());
            review_bot::InitBot(bot, chatId, true);
            *botState = W_COMMAND_REVIEW;
        }
        
        if (queryText == YES || queryText == NO) {
            *botState = ADDITIONAL_EST;
            user.reviewUser->SetMoreEvent(queryText == YES);
            review_bot::AddReviewAdditional(bot, chatId);
        }
        else if(queryText == SKIPADD) {
            user.reviewUser->AddReview(NO_ADDITIONAL);
            conn.AddReview(*(user.nameEvent) , review_bot::EstString(user.reviewUser->ActiveEst()), 
            review_bot::EstString(user.reviewUser->StructEst()), review_bot::EstString(user.reviewUser->CommandEst()), 
            user.reviewUser->AdditionalReview(), user.reviewUser->MoreEvent());
            *botState = W_COMMAND_REVIEW;
            bot.getApi().sendMessage(chatId, "Спасибо за отзыв!");
            user.Clear();
            review_bot::InitBot(bot, chatId, true);
        }
        else if (queryText == ADD_REVIEW) {
            *botState = CHOOSE_EVENT_REVIEW_ADD;
            user.AddReview(new review_bot::Review());
            review_bot::ChooseEvent(bot, chatId, conn.PossibleEvents());
            return;
        }
        else if(queryText == READ_REVIEW) {
            *botState = CHOOSE_EVENT_REVIEW_READ;
            review_bot::ChooseEvent(bot, chatId, conn.PossibleEvents());
        }
        else if (queryText == ADD_EVENT || queryText == RETURN_MENU) {
            if (queryText == ADD_EVENT) {
                user.AddEvent(new review_bot::Event());
            }
            review_bot::CreateEvent(bot, chatId, *(user.eventUser));
            *botState = CR_EVENT;
        }
        else if (queryText == SET_NAME) {
            review_bot::SetNameState(bot, chatId);
            *botState = W_NAME;
        }

        // =========================== SET TIME ===========================

        else if (queryText == SET_TIME) {
            *botState = W_TIME;
            review_bot::SetTimeState(bot, chatId);
        }

        else if (queryText == SET_TIME_NOW) {
            *botState = CR_EVENT;
            user.eventUser->SetTime(TimeFromString(GetStringDay(), DATA_FORMAT));
            review_bot::CreateEvent(bot, chatId, *(user.eventUser));
        }

        // =========================== ACTIVE TYPE ===========================
        
        else if (queryText == SET_ACTIVE) {
            review_bot::SetBodyState(bot, chatId);
        }

        else if (queryText == MIND_TYPE || queryText == RUN_TYPE || queryText == COMBO_TYPE || queryText == VIEWER_TYPE) {
            *botState = CR_EVENT;
            user.eventUser->SetBody((review_bot::BodyType)GetIndex({MIND_TYPE, RUN_TYPE, COMBO_TYPE, VIEWER_TYPE}, queryText));
            review_bot::CreateEvent(bot, chatId, *(user.eventUser));
        }

        // =========================== STRUCT QUESTIONS TYPE ===========================
        else if (queryText == SET_QUESTION) {
            review_bot::SetStructState(bot, chatId);
        }
        
        else if (queryText == RELAY_TYPE || queryText == CP_TYPE || queryText == TASKS_TYPE || queryText == NO_TASKS_TYPE) {
            *botState = CR_EVENT;
            user.eventUser->SetStruct((review_bot::StructType)GetIndex({CP_TYPE, RELAY_TYPE, TASKS_TYPE, NO_TASKS_TYPE}, queryText));
            review_bot::CreateEvent(bot, chatId, *(user.eventUser));
        }


        // =========================== COMMAND TYPE ===========================
        else if (queryText == SET_COMMAND) {
            review_bot::SetCommandState(bot, chatId);
        }

        else if (queryText == COMMAND_TYPE || queryText == ALONE_TYPE || queryText == ALL_TYPE) {
            *botState = CR_EVENT;
            user.eventUser->SetCommand((review_bot::CommandType)GetIndex({COMMAND_TYPE, ALONE_TYPE, ALL_TYPE}, queryText));
            review_bot::CreateEvent(bot, chatId, *(user.eventUser));
        }

        else if (queryText == ADD_EVENT_BD) {
            if (!user.eventUser->Valid()) {
                bot.getApi().sendMessage(chatId, "Мероприятие задано не полностью! Проверьте, установили ли вы все поля.");
                *botState = CR_EVENT;
                review_bot::CreateEvent(bot, chatId, *(user.eventUser));
            }
            else {
                std::vector<int> typesConfig = user.eventUser->Config();
                conn.AddEvent(user.eventUser->Name(), user.eventUser->Time(), typesConfig[0], typesConfig[1], typesConfig[2]);
                user.Clear();
                bot.getApi().editMessageText("Спасибо за мероприятие!", chatId, query->message->messageId);
                *botState = W_COMMAND_REVIEW;
                review_bot::InitBot(bot, chatId, true);
                
            }
        }
    });


    bot.getEvents().onCommand("start", [&bot, &Users](TgBot::Message::Ptr message) {
        if (Users.find(message->from->id) == Users.end()) {
            Users[message->from->id] = User();
            
        }
        State *botState = Users[message->from->id].BotState;
        *botState = W_COMMAND_REVIEW;
        review_bot::InitBot(bot, message->chat->id, true);
    });


    TgBot::TgLongPoll longPoll(bot);
    while (true) {
        std::cout << "Long poll started" << "\n";
        longPoll.start();
    }

}