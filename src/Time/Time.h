#ifndef __TIME_H__
#define __TIME_H__

#include <ctime>
#include <iostream>

#define DATA_FORMAT "%d.%m.%Y"
#define SQL_DATA_FORMAT "%Y-%m-%d %H%m"
#define MAX_INTERVAL_DAY "4"

std::string StringFromTime(time_t time, std::string separator);
time_t TimeFromString(std::string time_s, const char* format);

tm* GetTmCurrentDay();
std::string GetStringDay();

std::string TimeToSQL(time_t time);
std::string GenerateFormatSession(time_t time);

#endif
