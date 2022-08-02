#ifndef __EVENT_CLASS_H__
#define __EVENT_CLASS_H__

#include <ctime>
#include <iostream>
#include <vector>

#include "../States.h"
#include "../../Time/Time.h"

namespace review_bot {
    
    class Event {
        private:
            std::string name = "";
            time_t time_ = mktime(GetTmCurrentDay());
            review_bot::EventType body_type = (review_bot::EventType)NULL_TYPE;
            review_bot::EventStructType struct_type = (review_bot::EventStructType)NULL_TYPE;
            review_bot::EventCommandType command_type = (review_bot::EventCommandType)NULL_TYPE;
            //review_bot::MovementType movement_type = (review_bot::MovementType)NULL_TYPE;
        public:
            Event() {
            }
            inline void SetName(const std::string nameEvent) {name = nameEvent;}
            inline void SetTime(const time_t timeEvent) {time_ = timeEvent;}
            inline void SetBody(const EventType type) {body_type = type;}
            inline void SetStruct(const EventStructType type) {struct_type = type;}
            inline void SetCommand(const EventCommandType type) {command_type = type;}
            std::string GetEventType();
            std::string GetEventStructType();
            std::string GetEventCommandType();
            inline std::string Name() {return name;}
            inline time_t Time() {return time_;}
            inline std::vector<int> Config() {return std::vector<int>{(int)body_type, (int)struct_type, (int)command_type};}
            std::string Info();
            void Clear();
            inline bool Valid() {return (name != "" && (int)body_type != NULL_TYPE && (int)struct_type != NULL_TYPE && (int)command_type != NULL_TYPE);}
    };

    
};

#endif