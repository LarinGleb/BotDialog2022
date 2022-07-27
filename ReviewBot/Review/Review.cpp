#include <iostream>

#include "Review.h"

namespace review_bot {
    review_bot::vector_string Review::Ests() {return ests;}
    std::string Review::AdditionalReview() {return additional_review;}
    bool Review::MoreEvent() {return more_event;}
    std::string Review::NameEvent() {return name_event;}

    void Review::AddEst(std::string est) {ests.push_back(est);}
    void Review::AddReview(std::string review) {additional_review = review;}
    void Review::SetMoreEvent(bool need) {more_event = need;}
    void Review::SetNameEvent(std::string name) {name_event = name;}
};