#ifndef __STATES_H__
#define __STATES_H__

#define NULL_TYPE -1

namespace review_bot {
    enum body_t {
        NONE_BODY = -1,
        MIND,
        RUNNING,
        COMBO,
        VIEWER
    };
    typedef enum body_t BodyType;

    enum struct_t {
        NONE_STRUCT = -1,
        CP,
        RELAY,
        TASKS,
        NO_TASKS
    };
    typedef enum struct_t StructType;

    enum command_t {
        NONE_COMMAND = -1,
        COMMAND,
        ALONE,
        ALL_TOGETHER
    };
    typedef enum command_t CommandType;

    /*enum movement_t {
        NONE_MOVEMENT = -1,
        ROUTE,
        FREEDOM
    };
    typedef enum movement_t MovementType; */

};

#endif