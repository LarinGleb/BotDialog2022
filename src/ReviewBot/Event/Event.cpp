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

    int CreateEvent(TgBot::Bot& bot, std::int64_t chatId, review_bot::Event event) {
        TgBot::InlineKeyboardMarkup::Ptr createEvent(new TgBot::InlineKeyboardMarkup);
        createEvent->inlineKeyboard.push_back(CreateLineButtons({{"Название", SET_NAME}, {"Время", SET_TIME}}));
        createEvent->inlineKeyboard.push_back(CreateLineButtons({{"Вид активности", SET_ACTIVE}, {"Вид заданий", SET_QUESTION}}));
        createEvent->inlineKeyboard.push_back(CreateLineButtons({{"Разбиение на команды", SET_COMMAND}}));
        createEvent->inlineKeyboard.push_back(CreateLineButtons({{"Добавить мероприятие", ADD_EVENT_BD}}));
        std::string textEvent = std::string("Текущие характеристики мероприятия. ") + std::string("\n") + event.Info();
        bot.getApi().sendMessage(chatId, textEvent, false, 0, createEvent);
        return 0;
    }
    int SetTimeState(TgBot::Bot& bot, std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr nowTime(new TgBot::InlineKeyboardMarkup);
        nowTime->inlineKeyboard.push_back(CreateLineButtons({{"Поставить сегодняшнюю дату: " + GetStringDay(), SET_TIME_NOW}}));
        nowTime->inlineKeyboard.push_back(ButtonToMenu());

        bot.getApi().sendMessage(chatId, "Введите время в формате дд.мм.гггг", false, 0, nowTime);
        return 0;
    }

    int SetNameState(TgBot::Bot &bot, std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr name(new TgBot::InlineKeyboardMarkup);
        name->inlineKeyboard.push_back(ButtonToMenu());
        bot.getApi().sendMessage(chatId, "Введите название мероприятия:", false, 0, name);
        return 0;
    }

    int SetBodyState(TgBot::Bot& bot, std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr body(new TgBot::InlineKeyboardMarkup);
        body->inlineKeyboard.push_back(CreateLineButtons({{"Думательная", MIND_TYPE}, {"Бегательная", RUN_TYPE}}));
        body->inlineKeyboard.push_back(CreateLineButtons({{"Зрительная, без участия", VIEWER_TYPE}}));
        body->inlineKeyboard.push_back(CreateLineButtons({{"Смешанная", COMBO_TYPE}}));
        body->inlineKeyboard.push_back(ButtonToMenu());
        bot.getApi().sendMessage(chatId, "Выберите вид активности мероприятия:", false, 0, body);
        return 0;
    }

    int SetStructState(TgBot::Bot& bot, std::int64_t chatId) { 
        TgBot::InlineKeyboardMarkup::Ptr structQuestions(new TgBot::InlineKeyboardMarkup);
        structQuestions->inlineKeyboard.push_back(CreateLineButtons({{"Эстафеты", RELAY_TYPE}, {"КП", CP_TYPE}}));
        structQuestions->inlineKeyboard.push_back(CreateLineButtons({{"Задания", TASKS_TYPE}, {"Без заданий", NO_TASKS_TYPE}}));
        structQuestions->inlineKeyboard.push_back(ButtonToMenu());
        bot.getApi().sendMessage(chatId, "Выберите вид заданий мероприятия:", false, 0, structQuestions);
        return 0;
    }

    int SetCommandState(TgBot::Bot& bot, std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr structQuestions(new TgBot::InlineKeyboardMarkup);
        structQuestions->inlineKeyboard.push_back(CreateLineButtons({{"По одиночке", ALONE_TYPE}, {"По несколько человек", COMMAND_TYPE}}));    
        structQuestions->inlineKeyboard.push_back(CreateLineButtons({{"Весь лагерь вместе", ALL_TYPE},}));
        structQuestions->inlineKeyboard.push_back(ButtonToMenu());
        bot.getApi().sendMessage(chatId, "Выберите разбиение на команды:", false, 0, structQuestions);
        return 0;

    }

    int ChooseEvent(TgBot::Bot& bot, std::int64_t chatId, review_bot::vector_string names) {
        TgBot::InlineKeyboardMarkup::Ptr eventsButtons(new TgBot::InlineKeyboardMarkup);
        for(std::string name: names) {
            eventsButtons->inlineKeyboard.push_back(CreateLineButtons({{name, name}}));
        }
        bot.getApi().sendMessage(chatId, "Выберите мероприятие: ", false, 0, eventsButtons);
        return 0;
    }

    int ChooseYear(TgBot::Bot& bot, std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr yearCurrent(new TgBot::InlineKeyboardMarkup);
        int currentYear = GetTmCurrentDay()->tm_year + 1900;

        yearCurrent->inlineKeyboard.push_back(CreateLineButtons({{"Текущий год: " + std::to_string(currentYear), CURRENT_YEAR}}));

        bot.getApi().sendMessage(chatId, "Введите год, когда было мероприятие: ", false, 0, yearCurrent);
        return 0;
    }

    int MenuEvent(TgBot::Bot& bot, std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr menuEvent(new TgBot::InlineKeyboardMarkup);
        menuEvent->inlineKeyboard.push_back(CreateLineButtons({{"Нет, добавить новое", ADD_EVENT}}));
        menuEvent->inlineKeyboard.push_back(CreateLineButtons({{"Да, найти его", FIND_EVENT}}));

        bot.getApi().sendMessage(chatId, "Ваше мероприятие уже есть?", false, 0, menuEvent);
        return 0;
    }

    int ChooseWork(TgBot::Bot& bot, std::int64_t chatId) {
        TgBot::InlineKeyboardMarkup::Ptr menuEvent(new TgBot::InlineKeyboardMarkup);
        menuEvent->inlineKeyboard.push_back(CreateLineButtons({{"Прочитать отзывы", READ_REVIEW}}));
        menuEvent->inlineKeyboard.push_back(CreateLineButtons({{"Изменить время", CHANGE_TIME}}));
        menuEvent->inlineKeyboard.push_back(CreateLineButtons({{"Назад", RETURN_TO_MAIN}}));
        bot.getApi().sendMessage(chatId, "Ваше мероприятие уже есть?", false, 0, menuEvent);
        return 0;
    }
}