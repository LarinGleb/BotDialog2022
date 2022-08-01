#ifndef __GET_INDEX_H__
#define __GET_INDEX_H__

#include <vector> 
#include <iostream>
#include <algorithm>

//Get index elem from array
inline int GetIndex(const std::vector<std::string> array, const std::string elem) {
    return std::distance(std::begin(array), std::find(std::begin(array), std::end(array), elem));
}

#endif