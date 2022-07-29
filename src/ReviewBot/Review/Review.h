
#ifndef __REVIEW_CLASS_H__
#define __REVIEW_CLASS_H__

#include <iostream>
#include <vector>

#include "../States.h"
#include "../Event/Event.h"

#define NO_EST "none_est"
#define NO_QUESTION "none_question"
#define NO_ADDITIONAL "none_additional"

// estimation = est
namespace review_bot {
    typedef std::vector<std::string> vector_string;
    class Review {
        private:
            vector_string ests;
            std::string name_event;
            std::string additional_review;
            bool more_event;
        public:
            vector_string Ests();
            bool MoreEvent();
            std::string AdditionalReview();
            std::string NameEvent();

            void SetMoreEvent(bool need);
            void AddEst(std::string est);
            void AddReview(std::string review);
            void SetNameEvent(std::string name);
    };

};


#endif