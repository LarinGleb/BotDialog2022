#ifndef __STATES_H__
#define __STATES_H__

#define NULL_TYPE -1

namespace review_bot {
    enum EventType {
        MIND,
        RUNNING,
        COMBO,
        VIEWER,
        NUM_EVENT_TYPE,
        INVALID_EVENT_TYPE
    };

    enum EventStructType {
        CP,
        RELAY,
        TASKS,
        NO_TASKS,
        NUM_EVENT_STRUCT_TYPE,
        INVALID_EVENET_STRUCT_TYPE
    };

    enum EventCommandType {
        COMMAND,
        ALONE,
        ALL_TOGETHER,
        NUM_EVENT_COMMAND_TYPE,
        INVALID_EVENT_COMMAND_TYPE
    };

};

#endif