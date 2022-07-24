
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
            vector_string active_est;
            vector_string struct_est;
            vector_string command_est;

            std::string additional_review;
            bool more_event;
        public:
            vector_string ActiveEst();
            vector_string StructEst();
            vector_string CommandEst();
            std::string AdditionalReview();
            bool MoreEvent();

            void SetMoreEvent(bool need);
            void AddActiveEst(std::string est);
            void AddStructEst(std::string est);
            void AddCommandEst(std::string est);
            void AddReview(std::string review);
    };

};


#endif