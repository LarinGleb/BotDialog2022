#ifndef __BOT_H__
#define __BOT_H__

#include <tgbot/tgbot.h> // bot th lib
#include <iostream> // standart lib
#include "Connector/DataBase.h" // for working with sql
#include <functional>  // for hashing
#include "ReviewBot/ReviewBot.h"
#include "SecretFriends/SecretFriends.h"


// Errors and Succes keys
#define ErrorCommandInit 2
#define ErrorCommandWork 3
#define Success 0

#define EVENT_CP 1
#define EVENT_NOT_CP 1

struct CP {
    std::string name;
    std::string information;
    std::vector<std::string> onCpTeacher;
};


struct Command {
    std::string name;
    std::string capitan;
    std::vector<std::string> members;
};

struct Event {
    std::string information;
    std::string date;
    std::string name;
    std::vector<std::string> onTeacher;
};

struct EventCP {
    std::vector<std::string> onTeacher;
    Event InformationAll;
    std::vector<CP> CPS;  
};


typedef enum reviewBot_t {
    WAITING_INIT,
    WAITING_COMMAND,
    WAITING_EVENT_FOR_ADD,
    WAITING_EVENT_FOR_DELETE

} ReviewBotState;

typedef enum createstate_t {
    WAITING_CREATION,
    MENU_CP,
    DELETING_CP,
    MENU_CREATE_EVENT,
    WAITING_NAME_EVENT,
    WAITING_INFO_EVENT,
    WAITING_DATE_EVENT,
    WAITING_NAME_CP, 
    WAITING_INFO_CP,
    WAITING_NAMETEACHER_CP_ADD,
    WAITING_NAMETEACHER_CP_DELETE,
} CreateState;

typedef enum secretfriends_t {
    WAITING_ONE,
    WAITING_ADD
} SecretFriendsState;

// Get hash by string 
size_t GetId(std::string String); 


// Standart init commands for Bot
int InitBotCommands(TgBot::Bot& bot); 
int ClearCP(CP *TempCP);
std::vector<std::string> GetAllNamesCP(EventCP event);

int main(); // main function 

#endif