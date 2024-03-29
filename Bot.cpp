#include <iostream> // standart lib
#include <algorithm>
#include <vector>
#include <functional>  // for hashing
#include <map>
#include <stdio.h>

#include <tgbot/tgbot.h> // bot th lib

#include "Connector/DataBaseReview.h"
#include "Json/json.h"
#include "ReviewBot/ReviewBot.h"
#include "Bot.h"
#include "Connector/DataBase.h" // for working with sql
#include "BotTools/BotTools.h"
#include "ReviewBot/Event/Event.h"
#include "ReviewBot/Time/Time.h"
#include "Error/ErrorSave.h"

#define PATH_JSON "/home/gleb/CXX/BotDialog/defaultSettings.json"
int main() {
    try {
        const std::string username = USER_NAME;
        const std::string hostname = HOST_DB;
        const std::string password = PASSWORD;
	bool test = false;
	bool tech_work =false;
        db_api::Connector conn(hostname.c_str(), username.c_str(), password.c_str(), DIALOG_DB);
        std::string token = GetProperty((test)? "test_token": "token", PATH_JSON);
        std::string passwordAdmin = GetProperty("password", PATH_JSON);
        TgBot::Bot bot(token);
        std::map<std::int64_t, User> Users = {};
	char tmp[256];
	getcwd(tmp, 256);
        std::cout << "Current working directory: " << tmp << std::endl;
        bot.getEvents().onAnyMessage([&bot, &Users, &tech_work, &conn](TgBot::Message::Ptr message) {
            if (message->from->isBot) {return;}
	    if (tech_work) {bot.getApi().sendMessage(message->from->id, "Я на техработах, вернусь в 17"); return;}
       	    if (Users.count(message->from->id) == 0) {
                Users[message->from->id] = User();

            }
            std::int64_t chatId = message->chat->id;
            User user = Users[message->from->id];
            State* botState = user.BotState;

            if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/password")) {
                return;
            }

            switch (*botState)
            {   
                case W_START:
                    review_bot::InitBot(bot, chatId, IsAdmin(message->from->id, PATH_JSON));
                    *botState = W_START;
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

                case W_NEW_TIME: 
                    *botState = W_START;
                    conn.UpdateTime(user.reviewUser->NameEvent(), message->text);
                    bot.getApi().sendMessage(chatId, "Успешно изменено!");
                    user.Clear();
                    review_bot::InitBot(bot, chatId, IsAdmin(message->from->id, PATH_JSON));
                    break;
                    
                case W_YEAR: {
                    std::cout << message->text;
                    std::vector<std::string> events = conn.GetEventsBeetwenTime(std::string("01.01.") + message->text,
                    std::string("01.01.") + std::to_string(std::stoi(message->text) + 1));
                    if (events.size() == 0 ) {
                        bot.getApi().sendMessage(chatId, "Мероприятий не найдено!");
                        return;
                    }
                    review_bot::ChooseEvent(bot, chatId, events);
                    *botState = CHOOSE_EVENT;
                    break;
                }
                case EST: {
                    if (!review_bot::IsInt(message->text)) {
                        bot.getApi().sendMessage(chatId, "Неверная оценка: она должна лежать между 0 и 10 включительно!");
                        return;
                    }
		    
                    user.reviewUser->AddEst(message->text);  
                    
                    if (*(user.flagQuestion) >= user.questions->size()) {
                        review_bot::MoreEventQuestions(bot, chatId);
                        return;

                    }
		    while (user.questions->at(*(user.flagQuestion)) == NO_QUESTION) {
                        *(user.flagQuestion) += 1;
                        if (*(user.flagQuestion)>= user.questions->size()) {review_bot::MoreEventQuestions(bot, chatId);return;}
                    }
		    bot.getApi().sendMessage(chatId, user.questions->at(*(user.flagQuestion)));
		    *(user.flagQuestion) += 1;
		    break;
                }

                case ADDITIONAL_EST: {
                    user.reviewUser->AddReview(message->text);
                    conn.AddReview(user.reviewUser->NameEvent(), review_bot::EstString(user.reviewUser->Ests()), hashInt(message->from->id), user.reviewUser->MoreEvent(),
                    user.reviewUser->AdditionalReview());
                    *botState = W_START;
                    bot.getApi().sendMessage(chatId, "Спасибо за отзыв!");
                    user.Clear();
                    review_bot::InitBot(bot, chatId, IsAdmin(message->from->id, PATH_JSON));

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
            
            if (queryText == EVENT_WORKING) {
                review_bot::MenuEvent(bot, chatId);
            }
            else if (queryText == RETURN_TO_MAIN) {
                user.Clear();
                *botState = W_START;
                review_bot::InitBot(bot, chatId, IsAdmin(query->from->id, PATH_JSON));
            }
            else if (queryText == FIND_EVENT) {
                *botState = W_YEAR;
                review_bot::ChooseYear(bot, chatId);
            }
            else if (queryText == CHANGE_TIME) {
                *botState = W_NEW_TIME;
                bot.getApi().sendMessage(chatId, "Введите новую дату в формате дд.мм.ггг:");
                
            }
            else if (queryText == ADD_REVIEW) {
                *botState = CHOOSE_EVENT_REVIEW_ADD;
                user.AddReview(new review_bot::Review());
                std::vector<std::string> possibleEvents = conn.PossibleEvents(hashInt(query->from->id));
                if (possibleEvents.size() == 0) {
                    bot.getApi().sendMessage(chatId, "Доступных мероприятий пока нет!");
                    user.Clear();
                    *botState = W_START;
                    review_bot::InitBot(bot, chatId, IsAdmin(query->from->id, PATH_JSON));
                }
                else {
                    review_bot::ChooseEvent(bot, chatId, possibleEvents);
                }
                
            }

            // REEEEEEEEEEAAAAAAAADDDDDDDDDDDD REVIEW!!!!!!!!!!!!!!!!!!
            else if(queryText == SKIPADD) {
                user.reviewUser->AddReview(NO_ADDITIONAL);
                conn.AddReview(user.reviewUser->NameEvent(), review_bot::EstString(user.reviewUser->Ests()), hashInt(query->from->id), user.reviewUser->MoreEvent(),
                user.reviewUser->AdditionalReview());

		bot.getApi().sendMessage(chatId, "Спасибо за отзыв!");
                user.Clear();
                review_bot::InitBot(bot, chatId, IsAdmin(query->from->id, PATH_JSON));
            }
        
            else if(queryText == CURRENT_YEAR) {
                review_bot::ChooseEvent(bot, chatId, conn.GetEventsBeetwenTime(std::string("01.01.") + std::to_string(GetTmCurrentDay()->tm_year + 1900), 
                std::string("01.01.") + std::to_string(GetTmCurrentDay()->tm_year + 1901)));
                *botState = CHOOSE_EVENT;
            }
            else if (queryText == YES || queryText == NO) {
                *botState = ADDITIONAL_EST;
                user.reviewUser->SetMoreEvent(queryText == YES);
                review_bot::AddReviewAdditional(bot, chatId);
            }
            else if (queryText == READ_REVIEW) {
    	        if (user.reviewUser->NameEvent() != "") {

		
	            std::vector<int> types = conn.TypeEventByName(user.reviewUser->NameEvent());
		    
		    user.QuestionsByTypes(types);

		    std::string columns = ("CR_Id;");
            	
		    for (int i = 0; i <  user.questions->size(); i ++) {
		        if (user.questions->at(i) != NO_QUESTION) {

			   columns += std::string("\"\"\"") + user.questions->at(i) + std::string("\"\"\";");
		        }
            	    }
		    columns += "Need_More;Review\n";
		    std::string fileName  = "/home/gleb/CXX/BotDialog/temp/" + GenerateFormatSession(TimeFromString(conn.GetTime(user.reviewUser->NameEvent()), SQL_DATA_FORMAT)) +"_" + user.reviewUser->NameEvent() + ".csv";

		    std::fstream csvFile;
		    csvFile.open(fileName, std::ios::out | std::ios::app);
		    TgBot::InputFile fileCSV = TgBot::InputFile();
		    fileCSV.data += columns;
		    
		    std::vector<ReviewDataBase> reviews = conn.AllStructReviews(user.reviewUser->NameEvent());
		    if (reviews.size() == 0) {
			bot.getApi().sendMessage(chatId, "Отзывов пока нет");
		    } 
		    else {
			for (std::size_t i = 0; i < reviews.size(); i++) {
		            fileCSV.data += reviews.at(i).SaveCSV();
			}
			fileCSV.fileName = fileName;
	                bot.getApi().sendDocument(chatId, std::make_shared<TgBot::InputFile>(fileCSV));	
		    }
			
		   // std::remove(fileName.c_str());
	       }
	       else {
	            bot.getApi().sendMessage(chatId, "Какой-то баг! Пустое имя! Попробуйте ещё раз");
	       }
	       review_bot::InitBot(bot, chatId, true);
               *botState = W_START;

		
            }

            // AAAAAAAAAAAAADDDDDDDDDDDDDDDDDDDDDDDDDDDD EEEEEEEEEEEEEVVVVVVVVVVVVVVVVVEEEEEEEEEEEEEEEEENNNNNNNNNNNNNNNNNTTTTTTTTTTTT
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
            

            // AAADDDDDDD TOOOOOOOOOOO BD FINALYYYYYYYYYYYYYYYYYY
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
                    *botState = W_START;
                    review_bot::InitBot(bot, chatId, true);

                }
            }
            // CHOOSE QUERY VALUES
            else if (*botState == CHOOSE_EVENT) {
		user.reviewUser->SetNameEvent(queryText);
                review_bot::ChooseWork(bot, chatId);
            }
            
            else if (*botState == CHOOSE_EVENT_REVIEW_ADD) {
                user.QuestionsByTypes(conn.TypeEventByName(queryText));
                *botState = EST;
                user.reviewUser->SetNameEvent(queryText);
                
		bot.getApi().sendMessage(chatId, user.questions->at(*(user.flagQuestion)));  
	   	*(user.flagQuestion)+=1;
	    }
        });


        bot.getEvents().onCommand("start", [&bot, &Users](TgBot::Message::Ptr message) {
            if (Users.find(message->from->id) == Users.end()) {
                Users[message->from->id] = User();

            }
            State *botState = Users[message->from->id].BotState;
            *botState = W_START;
            review_bot::InitBot(bot, message->chat->id, IsAdmin(message->from->id, PATH_JSON));
        });

        bot.getEvents().onCommand("password", [&bot, &passwordAdmin](TgBot::Message::Ptr message) {
            std::stringstream ss(message->text);
            std::vector<std::string> command;
            std::string item;
            while(std::getline(ss, item, ' ')) {
                command.push_back(item);
            }
            if (passwordAdmin == command.at(1)) {
                AddAdmin(message->from->id, PATH_JSON);
            }

        });


        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            std::cout << "Long poll started" << std::endl;
            longPoll.start();
        }
    }
    catch (const std::string& ex) {
        ErrorLog(ex);
    }

}
