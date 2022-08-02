#ifndef __EVENT_CLASS_H__
#define __EVENT_CLASS_H__

#include <ctime>
#include <iostream>
#include <vector>

#include "../States.h"
#include "../Time/Time.h"

namespace review_bot {
    
    class Event {
        private:
            std::string name = "";
            time_t time_ = mktime(GetTmCurrentDay());
            review_bot::BodyType body_type = (review_bot::BodyType)NULL_TYPE;
            review_bot::StructType struct_type = (review_bot::StructType)NULL_TYPE;
            review_bot::CommandType command_type = (review_bot::CommandType)NULL_TYPE;
            //review_bot::MovementType movement_type = (review_bot::MovementType)NULL_TYPE;
        public:
            Event() {
            }
            void SetName(std::string nameEvent);
            void SetTime(time_t timeEvent);
            void SetBody(BodyType type);
            void SetStruct(StructType type);
            void SetCommand(CommandType type);

            /*void SetMovement(MovementType type)*/
            std::string GetBodyType();
            std::string GetStructType();
            std::string GetCommandType();
            /*std::string GetMovementType()*/

            std::string Name();
            time_t Time();

            std::vector<int> Config();

            std::string Info();
            void Clear();

            bool Valid();
    };

    
};

#endif