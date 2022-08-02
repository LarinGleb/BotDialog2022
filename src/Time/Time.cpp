#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include "Time.h"

tm* GetTmCurrentDay() {
    time_t now = time(0);
    tm *currentTime = localtime(&now);
    return currentTime;
}
std::string TimeToSQL(const time_t time) {
    tm* currentTime = localtime(&time);
    std::string day = (currentTime->tm_mday < 10? "0": "") + std::to_string(currentTime->tm_mday);
    return day + "." + std::to_string(currentTime->tm_mon + 1) + "." + std::to_string(currentTime->tm_year + 1900);
}

std::string StringFromTime(const time_t time, const std::string separator) {
    tm* currentTime = localtime(&time);
    std::string day = (currentTime->tm_mday < 10? "0": "") + std::to_string(currentTime->tm_mday);
    std::string month =  (currentTime->tm_mon + 1 < 10 ? "0": "") + std::to_string(currentTime->tm_mon + 1);
    return day + separator + month + separator + std::to_string(currentTime->tm_year + 1900);
}
std::string GenerateFormatSession(const time_t time) {
    tm* currentTime = localtime(&time);
    std::string day = (currentTime->tm_mday < 10? "0": "") + std::to_string(currentTime->tm_mday);
    std::string month =  (currentTime->tm_mon + 1 < 10 ? "0": "") + std::to_string(currentTime->tm_mon + 1);
    return std::to_string(currentTime->tm_year + 1900) + "_" + month + "_" + day;
}

std::string GetStringDay() {
    return StringFromTime(mktime(GetTmCurrentDay()), ".");
}

time_t TimeFromString(const std::string time_s, const char* format) {
    struct std::tm tm = {};
    std::istringstream ss(time_s);
    ss >> std::get_time(&tm, format);
    return mktime(&tm);
}

