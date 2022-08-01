#ifndef __BOT_H__
#define __BOT_H__

#include <map>
#include <algorithm>

#include <tgbot/tgbot.h>

#include "ReviewBot/ReviewBot.h"
#include "ReviewBot/Event/Event.h"
#include "ReviewBot/Review/Review.h"

#define USER_NAME "admin"
#define HOST_DB "localhost"
#define PASSWORD "19572006gG."

#define PATH_JSON "../Settings.json"

enum state_t {
    W_START,
    CR_EVENT,
    W_NAME,
    W_TIME,
    W_YEAR,
    W_NEW_TIME,
    CHOOSE_EVENT_YEAR,
    CHOOSE_EVENT_REVIEW_ADD,
    CHOOSE_EVENT,
    EST,
    ADDITIONAL_EST
};
typedef enum state_t State;

struct user_t {
    state_t BotState = W_START;
    review_bot::Review reviewUser = review_bot::Review();
    review_bot::Event eventUser = review_bot::Event();
    std::vector<std::string> questions = {};
    void QuestionsByTypes(const int types[]) {
	    if (questions.size() != 0) {return;}
        questions.insert(std::end(questions), std::begin(review_bot::ActiveQuestion((review_bot::EventType)types[0])), std::end(review_bot::ActiveQuestion((review_bot::EventType)types[0])));
        questions.insert(std::end(questions), std::begin(review_bot::StructQuestion((review_bot::EventStructType)types[1])), std::end(review_bot::StructQuestion((review_bot::EventStructType)types[1])));
        questions.insert(std::end(questions), std::begin(review_bot::CommandQuestion((review_bot::EventCommandType)types[2])), std::end(review_bot::ActiveQuestion((review_bot::EventType)types[2])));
    }
};
typedef struct user_t User;

int hashInt(int x);

int GetIndex(const std::vector<std::string> array, const std::string elem);

int main(); // main function 



typedef state_t State;

#endif