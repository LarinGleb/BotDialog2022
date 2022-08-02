
#ifndef __REVIEW_CLASS_H__
#define __REVIEW_CLASS_H__

#include <iostream>
#include <vector>

#include "../States.h"
#include "../Event/Event.h"

#define NO_EST "none_est"
#define NO_QUESTION "none_question"
#define NO_ADDITIONAL "none_additional"

#define MIN_EST 0
#define MAX_EST 10

#define NEED_MORE_EVENT 1
#define DONT_NEED_MORE_EVENT 0 

// estimation = est
namespace review_bot {
    class Review {
        private:
            std::vector<std::string> ests;
            std::string name_event;
            std::string additional_review;
            bool more_event;
        public:
            inline std::vector<std::string> Ests() {return ests;}
            inline std::string AdditionalReview() {return additional_review;}
            inline bool MoreEvent() {return more_event;}
            inline std::string NameEvent() {return name_event;}

            inline void AddEst(const std::string est) {ests.push_back(est);}
            inline void AddReview(const std::string review) {additional_review = review;}
            inline void SetMoreEvent(const bool need) {more_event = need;}
            inline void SetNameEvent(const std::string name) {name_event = name;}
    };

};


#endif