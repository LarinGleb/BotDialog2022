
#include <iostream>
#include <vector>

#include "Bot.h"
int unhashInt(int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
int hashInt(int x) {
    x = ((x >> 16) ^ x) * 0x119de1f3;
    x = ((x >> 16) ^ x) * 0x119de1f3;
    x = (x >> 16) ^ x;
    return x;
}

int GetIndex(const std::vector<std::string> array, const std::string elem) {
    return std::distance(std::begin(array), std::find(std::begin(array), std::end(array), elem));
}