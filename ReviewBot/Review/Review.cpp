#include <iostream>

#include "Review.h"

namespace review_bot {
    review_bot::vector_string Review::ActiveEst() {return active_est;}
    review_bot::vector_string Review::StructEst() {return struct_est;}
    review_bot::vector_string Review::CommandEst() {return command_est;}
    std::string Review::AdditionalReview() {return additional_review;}
    bool Review::MoreEvent() {return more_event;}

    void Review::AddActiveEst(std::string est) {active_est.push_back(est);}
    void Review::AddStructEst(std::string est) {struct_est.push_back(est);}
    void Review::AddCommandEst(std::string est) {command_est.push_back(est);}
    void Review::AddReview(std::string review) {additional_review = review;}
    void Review::SetMoreEvent(bool need) {more_event = need;}
};