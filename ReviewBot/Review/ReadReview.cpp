#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
// merge with Review.cpp

#include "../ReviewBot.h"
#include "../Review/Review.h"

namespace review_bot
{
    std::vector<std::string> SeparateEst(std::string est)
    {
        std::vector<std::string> estsVector = {};

        std::stringstream ss(est);
        std::string item;
        while (std::getline(ss, item, (char)SEPARATOR_DEFAULT))
        {
            estsVector.push_back(item);
        }
        return estsVector;
    }

    std::string StatisticEst(std::vector<std::string> ests)
    {
        std::string statistic = std::string("");
        for (int i = 0; i <= 10; i++)
        {
            statistic += std::string("Количество оценок ") + std::to_string(i) + std::string(" составляет ") + std::to_string(std::count(ests.begin(), ests.end(), std::to_string(i))) + std::string(".\n");
        }
        return statistic;
    }

    std::string StatisticMore(std::vector<int> more)
    {
        std::string statistic = std::string("");
        statistic += std::string("Количество \"да, мы хотим ещё!\": ") + std::to_string(std::count(more.begin(), more.end(), 1)) + std::string(".\n");
        statistic += std::string("Количество \"нет, не хотим!\": ") + std::to_string(std::count(more.begin(), more.end(), 0)) + std::string(".\n");
        return statistic;
    }

    std::string SaveReviews(std::string nameEvent, std::string data, review_bot::vector_string reviews)
    {
        std::ofstream reviewFile;
        std::string fileDir = "../tempReviews/" + data + "_" + nameEvent + ".txt";
        reviewFile.open(fileDir, std::ofstream::out | std::ofstream::trunc);
        if (reviewFile.is_open())
        {
            for (std::string review : reviews)
            {
                if (review != NO_ADDITIONAL)
                {
                    reviewFile << review + "\n";
                }
            }
            reviewFile.close();
        }
        else
            std::cout << "Файл не открылся для записи";
        return fileDir;
    }

};
