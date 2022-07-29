#ifndef __STATES_H__
#define __STATES_H__

#define NULL_TYPE -1

namespace review_bot
{
    enum EventType
    {
        MIND,
        RUNNING,
        COMBO,
        VIEWER,
        NUM_EVENT_TYPES,
        INVALID_EVENT_TYPE,
    };

    enum EventTaskType
    {
        CP,
        RELAY,
        TASKS,
        NO_TASKS,
        NUM_TASK_TYPES,
        INVALID_TASK_TYPE,
    };

    enum EventGroupType
    {
        COMMAND,
        ALONE,
        ALL_TOGETHER,
        NUM_GROUP_TYPES,
        INVALID_GROUP_TYPE,
    };

    /*enum movement_t {
        NONE_MOVEMENT = -1,
        ROUTE,
        FREEDOM
    };
    typedef enum movement_t MovementType; */

};

#endif