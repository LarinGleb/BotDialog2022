#include <ctime>
#include <iostream>
#include <fstream>

#include "../ReviewBot/Time/Time.h"

void ErrorLog(std::string ex) {
    time_t now = time(0);
    tm *currentTime = localtime(&now);
    std::string timeString = StringFromTime(now, ".");
    std::ofstream error_log;
    error_log.open("/home/gleb/CXX/BotDialog/Error/error_log.txt");
    error_log << "[" << timeString << " " << currentTime->tm_hour << currentTime->tm_min << "] " << ex << std::endl;
    error_log.close();
    std::cout << "[" << timeString << " " << currentTime->tm_hour << currentTime->tm_min << "] " << ex << std::endl;
}
