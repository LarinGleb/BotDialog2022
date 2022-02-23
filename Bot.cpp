#include "Bot.h"

int ClearCP(CP *TempCP) {
    TempCP->name = "";
    TempCP->information = "";
    TempCP->onCpTeacher = {};
}


std::vector<std::string> GetAllNamesCP(EventCP event) {
    std::vector<std::string> names = {};
    for (int i = 0; i < event.CPS.size(); i++) {
        names.push_back(event.CPS[i].name);
    }
    return names;
}


int InitBotCommands(TgBot::Bot& bot, ReviewBotState *ReviewState) {
    bot.getEvents().onCommand("start", [&bot, ReviewState](TgBot::Message::Ptr message) {
        *ReviewState = WAITING_COMMAND;
        InitReviewBot(bot, message);
    });

    std::cout << "Command init successful" << "\n";
    return Success;
}


size_t GetId(std::string String) {
    std::hash<std::string> hashThisString;
    return hashThisString(String);
}


int main() {

    TgBot::Bot bot("1940339152:AAG0jf4jVUk62ZmSHyPmrjlYCoMYPR-qjNk");
    const std::string username = "admin";
    const std::string hostname = "localhost";
    const std::string password = "19572006gG.";

    db_api::Connector conn(hostname.c_str(), username.c_str(), password.c_str(), "Reviews");


    ReviewBotState ReviewState = WAITING_INIT;
    CreateState CreateStateEvent = WAITING_CREATION;
    bool waitingInput = false;
    int pageList = 0;


    std::vector<std::string> events = conn.GetAllEvents();
    std::string inputMessage = "None";

    CP TempCP;
    Event TempEvent;
    EventCP TempEventCP;
    int typeTempEvent = EVENT_NOT_CP;
    

    InitBotCommands(bot, &ReviewState);
    
    bot.getEvents().onAnyMessage([&bot, &conn, &ReviewState, &events, &waitingInput, &inputMessage, &CreateStateEvent, &TempEvent, &TempCP](TgBot::Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        if (waitingInput) {
            waitingInput = false;
            inputMessage = message->text;
        }

        switch (ReviewState)
        {
            
            case WAITING_INIT: {
                bot.getApi().sendMessage(message->chat->id, "Привет! Я бот способный оставлять отзывы. Напиши /start для того, чтобы начать! \n");
            } break;

            // ----------- ADDED EVENT -----------

            case WAITING_EVENT_FOR_ADD: {
                switch(CreateStateEvent) {
                    
                    // ----------- EVENTCP NAME AND INFO -----------

                    case WAITING_NAME_EVENT: {
                        TempEvent.name = inputMessage;
                        CreateStateEvent = MENU_CREATE_EVENT;
                        bot.getApi().sendMessage(message->chat->id, "Название установлено. \n");
                        StartCreatingState(bot, message);

                    }  break;

                    case WAITING_INFO_EVENT: {
                        TempEvent.information = inputMessage;
                        bot.getApi().sendMessage(message->chat->id, "Информация записана. \n");
                        StartCreatingState(bot, message);
                        CreateStateEvent = MENU_CREATE_EVENT;
                        
                    } break;

                    case WAITING_DATE_EVENT: { // YYYY-MM-DD hh:mm
                        TempEvent.date = inputMessage;
                        bot.getApi().sendMessage(message->chat->id, "Дата установлена. \n");
                        StartCreatingState(bot, message);
                        
                        CreateStateEvent = MENU_CREATE_EVENT;
                    } break;

                    // ----------- CP NAME AND INFO ----------- 

                    case WAITING_NAME_CP: {
                        TempCP.name = inputMessage;
                        bot.getApi().sendMessage(message->chat->id, "Название установлено. \n");
                        MenuCreateCP(bot, message);
                        CreateStateEvent = MENU_CP;
                        
                    } break;

                    case WAITING_INFO_CP: {
                        TempCP.information = inputMessage;
                        bot.getApi().sendMessage(message->chat->id, "Информация записана. \n");
                        MenuCreateCP(bot, message);
                        CreateStateEvent = MENU_CP;
                        
                    } break;

                    // ----------- ADD AND DELETE TEACHER FROM CP -----------

                    case WAITING_NAMETEACHER_CP_ADD: {
                        TempCP.onCpTeacher.push_back(inputMessage);
                        bot.getApi().sendMessage(message->chat->id, "Препод добавлен!\n");
                        CreateStateEvent = MENU_CP;
                        MenuCreateCP(bot, message);

                    } break;

                    case WAITING_NAMETEACHER_CP_DELETE: {
                        if (std::find(events.begin(), events.end(), inputMessage) != events.end()) {
                            TempCP.onCpTeacher.push_back(inputMessage);
                            bot.getApi().sendMessage(message->chat->id, "Препод удалён!\n");
                            CreateStateEvent = MENU_CP;
                            MenuCreateCP(bot, message);

                        }
                        else {
                            bot.getApi().sendMessage(message->chat->id, "Препод не найден. Пожалуйста, перепроверьте имя препода. \n");
                        }
                        
                        
                    } break;

                }
                
            } break;

            // ----------- DELETE EVENT -----------

            case WAITING_EVENT_FOR_DELETE: {
                if (std::find(events.begin(), events.end(), inputMessage) != events.end()) {
                    conn.DeleteEvent(GetId(inputMessage));
                    bot.getApi().sendMessage(message->chat->id, "Успешно удалено! \n");
                    ReviewState = WAITING_COMMAND;
                    events = conn.GetAllEvents();
                }
                else {
                    bot.getApi().sendMessage(message->chat->id, "Мероприятие не найдено \n");
                }
                
            } break;

            default:
                break;
        }
    });


    bot.getEvents().onCallbackQuery([&bot, &conn, &ReviewState, &pageList, &events, &waitingInput, &CreateStateEvent, &TempCP, &TempEventCP, &typeTempEvent](TgBot::CallbackQuery::Ptr query) {
        

        // ----------- WORKING WITH LOT OF BUTTONS -----------

        if (CreateStateEvent == DELETING_CP) {
            for (int i = 0; i < TempEventCP.CPS.size(); i ++) { 
                if (query->data == "CP" + std::to_string(i)) {
                    TempEventCP.CPS.erase(TempEventCP.CPS.begin() + i - 1);
                    MenuCreateEventCP(bot, query->message);
                    CreateStateEvent = MENU_CP;
                    break;
                }
            }
        }

        // ----------- WORKING WITH EVENTS ------------

        if (query->data == "AddEvent") {
            StartCreatingState(bot, query->message);
            ReviewState = WAITING_EVENT_FOR_ADD;
        }

        else if(query->data == "DeleteEvent") {
            DeleteEventState(bot, query->message);
            waitingInput = true;
            ReviewState = WAITING_EVENT_FOR_DELETE;
        }

        // ----------- LIST OF EVENTS ----------- 

        else if (query->data == "List") {
            events = conn.GetAllEvents();
            ListEventsState(bot, query->message);
            bot.getApi().sendMessage(query->message->chat->id, GetPageMessage(pageList, events));
        }
        
        else if(query->data == "->" && pageList < ceil(events.size() / COUNT_EVENT_IN_PAGE)) {
            pageList += 1;

            bot.getApi().sendMessage(query->message->chat->id, GetPageMessage(pageList, events));
        }
        else if(query->data == "<-" && pageList != 0) {
            pageList -= 1;

            bot.getApi().sendMessage(query->message->chat->id, GetPageMessage(pageList, events));
        }

        // ----------- RETURNS -----------

        else if (query->data == "ReturnToMenuCreateEvent") {
            StartCreatingState(bot, query->message);
            CreateStateEvent = MENU_CREATE_EVENT;
        }

        else if (query->data == "ReturnToMenuCreateEventСP") {
            MenuCreateEventCP(bot, query->message);
            CreateStateEvent = MENU_CP;
        }

        // ----------- CREATE EVENTS -----------
        else if(query->data == "CreateEventWithCP") {
            MenuCreateEventCP(bot, query->message);
            typeTempEvent = EVENT_CP;
            CreateStateEvent = MENU_CP;
            
        }

        else if(query->data == "CreateEventWithOUTCP") {
            StartCreatingState(bot, query->message);
            typeTempEvent = EVENT_NOT_CP;
            CreateStateEvent = MENU_CREATE_EVENT;
        }

        else if (query->data == "ChooseType") {
            ChooseTypeEvent(bot, query->message);
        }

        // ----------- WORKING WITH CP -----------

        else if (query->data == "AddNameCP") {
            CreateStateEvent = WAITING_NAME_CP;
            waitingInput = true;
            bot.getApi().sendMessage(query->message->chat->id, "Введите имя КП: \n");
        }

        else if (query->data == "AddNameInfoCP") {
            CreateStateEvent = WAITING_INFO_CP;
            waitingInput = true;
            bot.getApi().sendMessage(query->message->chat->id, "Введите информацию КП: \n");
        }

        else if (query->data == "AddNameTeacherCP") {
            CreateStateEvent = WAITING_NAMETEACHER_CP_ADD;
            waitingInput = true;
            bot.getApi().sendMessage(query->message->chat->id, "Введите имя препода для добавления: \n");
        }

        else if (query->data == "AddDeleteTeacherCP") {
            waitingInput = true;
            CreateStateEvent = WAITING_NAMETEACHER_CP_DELETE;
            bot.getApi().sendMessage(query->message->chat->id, "Введите имя препода для удаления: \n");
        }

        else if (query->data == "AddCP") {
            CreateStateEvent = MENU_CP;
            MenuCreateCP(bot, query->message);
        }

        else if (query->data == "AddNewCP") {
            TempEventCP.CPS.push_back(TempCP);
            ClearCP(&TempCP);
            bot.getApi().sendMessage(query->message->chat->id, "КП добавлено! \n");
            MenuCreateCP(bot, query->message);
        }

        else if(query->data == "ClearCP") {
            ClearCP(&TempCP);
            TempEventCP.CPS = {};
            bot.getApi().sendMessage(query->message->chat->id, "КП полностью очищенно! \n");
            MenuCreateCP(bot, query->message);
        }

        else if(query->data == "DeleteCP") {
            MenuDeleteCP(bot, query->message, GetAllNamesCP(TempEventCP));
            CreateStateEvent = DELETING_CP;
        }
        
        // ----------- WORKING WITH EVENT CP -----------

        else if(query->data == "Name") {
            bot.getApi().sendMessage(query->message->chat->id, "Введите название мероприятия: \n");
            waitingInput = true;
            CreateStateEvent = WAITING_NAME_EVENT;

        }

        else if(query->data == "Information") {
            bot.getApi().sendMessage(query->message->chat->id, "Введите информацию об мероприятии: \n");
            waitingInput = true;
            CreateStateEvent = WAITING_INFO_EVENT;
        }

        else if(query->data == "Date") {
            bot.getApi().sendMessage(query->message->chat->id, "Введите дату проведения мероприятия в формате гггг.мм.дд чч:мм : \n");
            waitingInput = true;
            CreateStateEvent = WAITING_DATE_EVENT;
        }

        else {
            return;
        }
        
    });


    TgBot::TgLongPoll longPoll(bot);
    while (true) {
        std::cout << "Long poll started" << "\n";
        longPoll.start();
    }

    return Success;
}