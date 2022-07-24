#include "Event.h"

namespace review_bot {

    // =========== GET AND SET
    void Event::SetName(std::string nameEvent) {name = nameEvent;}
    void Event::SetTime(time_t timeEvent) {time_ = timeEvent;}
    void Event::SetBody(BodyType type) {body_type = type;}
    void Event::SetStruct(StructType type) {struct_type = type;}
    void Event::SetCommand(CommandType type) {command_type = type;}
    /*void SetMovement(MovementType type) {
        movement_type = type;
    }*/
    std::string Event::GetBodyType() {
        switch(body_type) {
            case MIND:
                return "думательная";
            case RUNNING:
                return "бегательная";
            case COMBO:
                return "думательно-бегательная";
            case VIEWER:
                return "зрительная, без участия";

            case NONE_BODY:
                throw std::invalid_argument("NULL type in switch! ");
        }
    }
    std::string Event::GetStructType() {
        switch(struct_type) {
            case CP:
                return "КП-шное";
            case RELAY:
                return "эстафеты";
            case TASKS:
                return "задания";
            case NO_TASKS:
                return "без заданий";

            case NONE_STRUCT: 
                throw std::invalid_argument("NULL type in switch! ");
        }
    }
    std::string Event::GetCommandType() {
        switch(command_type) {
            case ALONE:
                return "по одиночке";
            case COMMAND:
                return "несколько человек";
            case ALL_TOGETHER:
                return "весь лагерь вместе";
                
            case NONE_COMMAND:
                throw std::invalid_argument("NULL type in switch! ");
        }
    }
    /*std::string Event::GetMovementType() {
        switch(movement_type) {
            case ROUTE:
                return "по маршруту";
                break;
            case FREEDOM:
                return "свободное";
                break;
        }
    }*/

    std::string Event::Name() {return name;}
    time_t Event::Time() {return time_;}
    std::vector<int> Event::Config() {return std::vector<int>{(int)body_type, (int)struct_type, (int)command_type};}

    std::string Event::Info() {
        return "Название: " + ((name == "") ? "не задано" : name) + "\n" +
                "Дата проведения: " + StringFromTime(time_, ".") + "\n" +
                "Активность: " + ((body_type == NULL_TYPE) ? "не задано" : GetBodyType()) + "\n" + 
                "Структура заданий: " +  ((struct_type == NULL_TYPE) ? "не задано" : GetStructType()) + "\n" + 
                "Разбиение на команды: " + ((command_type == NULL_TYPE) ? "не задано" : GetCommandType()) +  "\n";
       //         "Перемещение: " + ((movement_type == NULL_TYPE) ? "не задано" : GetMovementType()) + "\n";
    }
    void Event::Clear() {
        name = std::string("");
        time_ = TimeFromString(GetStringDay(), DATA_FORMAT);
        body_type = (BodyType)NULL_TYPE;
        struct_type = (StructType)NULL_TYPE;
        command_type = (CommandType)NULL_TYPE;
        //movement_type = (MovementType)NULL_TYPE;
    }   
    bool Event::Valid() {
        return (name != "" && (int)body_type != NULL_TYPE && (int)struct_type != NULL_TYPE && (int)command_type != NULL_TYPE);
    }
}