#ifndef __BOT_H__
#define __BOT_H__

#include <map>

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
    W_YEAR,
    W_NEW_TIME,
    CHOOSE_EVENT_YEAR,
    CHOOSE_EVENT_REVIEW_ADD,
    CHOOSE_EVENT,
    EST,
    ADDITIONAL_EST
};
typedef enum state_t State;
typedef review_bot::vector_string (*GetQuestions)(int);

struct user_t {
    state_t* BotState = new state_t(W_START);
    review_bot::Review* reviewUser = new review_bot::Review();
    review_bot::Event* eventUser = new review_bot::Event();
    std::vector<std::string>* questions = new std::vector<std::string>();
    int* flagQuestion = new int(0);
    std::map<int, GetQuestions> GetQuestionFunction = {{0, &review_bot::ActiveQuestion}, {1, &review_bot::StructQuestion}, {2, &review_bot::CommandQuestion}, };
    void QuestionsByTypes(std::vector<int> types) {
	questions->clear();
	for (int i = 0; i < 3; i ++) {
            for (std::string question: GetQuestionFunction[i](types.at(i))) {
                questions->push_back(question);
            }
        }
    }

    void AddEvent(review_bot::Event *event) {
        *eventUser = *event;
    }

    void AddReview(review_bot::Review *review) {
        *reviewUser = *review;
    }

    void Clear() {
        AddReview(new review_bot::Review());
        AddEvent(new review_bot::Event());
        questions->clear();
        *flagQuestion = 0;
    }

};

typedef struct user_t User;

int unhashInt(int x);
int hashInt(int x);

int GetIndex(const std::vector<std::string> array, const std::string elem);

int main(); // main function 



typedef state_t State;

#endif