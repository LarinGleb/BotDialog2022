#ifndef __BOT_H__
#define __BOT_H__

#include <tgbot/tgbot.h>

#include "ReviewBot/ReviewBot.h"
#include "ReviewBot/Event/Event.h"
#include "ReviewBot/Review/Review.h"

#define USER_NAME "admin"
#define HOST_DB "localhost"
#define PASSWORD "19572006gG."

#define PATH_TO_TEMP_REVIEW "ReviewBot/Review/temp_reviews.txt"

enum state_t {
    W_START,
    CR_EVENT,
    W_NAME,
    W_TIME,
    CHOOSE_EVENT_REVIEW_ADD,
    CHOOSE_EVENT_REVIEW_READ,
    EST,
    ADDITIONAL_EST
};
typedef enum state_t State;

struct user_t {
    state_t* BotState = new state_t(W_START);
    review_bot::Review* reviewUser = new review_bot::Review();
    review_bot::Event* eventUser = new review_bot::Event();
    std::vector<review_bot::vector_string>* questions = new std::vector<review_bot::vector_string>();
    int* flagQuestion = new int(0);
    int* flagTypeQuestion = new int(0);
    std::string* nameEvent = new std::string("");
    void QuestionsByTypes(std::vector<int> types) {
        questions->push_back(review_bot::ActiveQuestion((review_bot::BodyType)types.at(0)));
        questions->push_back(review_bot::StructQuestion((review_bot::StructType)types.at(1)));
        questions->push_back(review_bot::CommandQuestion((review_bot::CommandType)types.at(2)));
    }

    void AddEvent(review_bot::Event *event) {
        *eventUser = *event;
    }

    void AddReview(review_bot::Review *review) {
        *reviewUser = *review;
    }

    void Clear() {
        BotState = new state_t(W_START);
        reviewUser = new review_bot::Review();
        eventUser = new review_bot::Event();
        questions = new std::vector<review_bot::vector_string>();
        flagQuestion = new int(0);
        flagTypeQuestion = new int(0);
        nameEvent = new std::string("");
    }

};
typedef struct user_t User;
bool IsAdmin(const char* id);
std::string GetPropertyFromFile(std::string fileDir);
int GetIndex(const std::string array[], const std::string elem);

int main(); // main function 



typedef state_t State;

#endif