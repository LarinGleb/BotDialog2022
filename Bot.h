#ifndef __BOT_H__
#define __BOT_H__

#include <map>
#include <string>
#include <vector>
#include <array>

#include <tgbot/tgbot.h>

#include "ReviewBot/ReviewBot.h"
#include "ReviewBot/Event/Event.h"
#include "ReviewBot/Review/Review.h"

#define USER_NAME "admin"
#define HOST_DB "localhost"
#define PASSWORD "19572006gG."

enum class State
{
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
    ADDITIONAL_EST,
    NUM_BOT_STATES,
};

struct User
{
    state_t BotState = State::W_START;
    review_bot::Review reviewUser;
    review_bot::Event eventUser;
    std::vector<std::string> questions;
    int flagQuestion;

    void GetQuestions(const Event event)
    {
        review_bot::ActiveQuestion(event...);
        review_bot::StructQuestion(event...);
        review_bot::CommandQuestion(event...);
    }

    void AddEvent(review_bot::Event &event)
    {
        eventUser = event;
    }

    void AddReview(review_bot::Review &review)
    {
        reviewUser = review;
    }
};

int main(); // main function

typedef state_t State;

#endif
