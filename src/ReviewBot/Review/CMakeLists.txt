cmake_minimum_required(VERSION 3.10)

add_library(Review SHARED Review.cpp AddReview.cpp ReadReview.cpp)

set_target_properties(Review PROPERTIES LINKER_LANGUAGE CXX)
message("Added bot reviews")