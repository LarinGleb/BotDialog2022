#include "ReviewBot.h"

int InitReviewBot(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message) {

    TgBot::InlineKeyboardMarkup::Ptr keyboardInit(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> firstLineButtons;
    std::vector<TgBot::InlineKeyboardButton::Ptr> secondLineButtons;
    std::vector<TgBot::InlineKeyboardButton::Ptr> thirdLineButtons;

    firstLineButtons.push_back(CreateButtonTG("Добавить мероприятие", "AddEvent"));
    firstLineButtons.push_back(CreateButtonTG("Удалить мероприятие", "DeleteEvent"));

    secondLineButtons.push_back(CreateButtonTG("Add Review", "AddReview"));
    secondLineButtons.push_back(CreateButtonTG("Delete Review", "DeleteReview"));

    thirdLineButtons.push_back(CreateButtonTG("Список мероприятий", "List"));
    
    keyboardInit->inlineKeyboard.push_back(firstLineButtons);
    keyboardInit->inlineKeyboard.push_back(secondLineButtons);
    keyboardInit->inlineKeyboard.push_back(thirdLineButtons);

    bot.getApi().sendMessage(message->chat->id, "Hello", false, 0, keyboardInit);

    return Success;

}

int ChooseTypeEvent(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message) {

    TgBot::InlineKeyboardMarkup::Ptr keyboardChooseType(new TgBot::InlineKeyboardMarkup);
    
    std::vector<TgBot::InlineKeyboardButton::Ptr> firstLineButtons;
    std::vector<TgBot::InlineKeyboardButton::Ptr> secondLineButtons;

    firstLineButtons.push_back(CreateButtonTG("КП'шное", "CreateEventWithCP"));
    firstLineButtons.push_back(CreateButtonTG("Не КП'шное", "CreateEventWithOUTCP"));

    secondLineButtons.push_back(CreateButtonTG("Назад (в меню создания мероприятия)", "ReturnToMenuCreateEvent"));

    keyboardChooseType->inlineKeyboard.push_back(firstLineButtons);
    keyboardChooseType->inlineKeyboard.push_back(secondLineButtons);

    bot.getApi().sendMessage(message->chat->id, "Выберите тип мероприятия: ", false, 0, keyboardChooseType);
}   


int StartCreatingState(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message) {

    TgBot::InlineKeyboardMarkup::Ptr keyboardCreate(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> firstLineButtons;
    std::vector<TgBot::InlineKeyboardButton::Ptr> secondLineButtons;
    std::vector<TgBot::InlineKeyboardButton::Ptr> thirdLineButtons;
    
    firstLineButtons.push_back(CreateButtonTG("Выбрать имя", "Name")); 
    firstLineButtons.push_back(CreateButtonTG("Добавить информацию об мероприятии", "Information")); 
    firstLineButtons.push_back(CreateButtonTG("Указать дату проведения", "Date")); 

    secondLineButtons.push_back(CreateButtonTG("Выбрать тип мероприятия", "ChooseType"));

    thirdLineButtons.push_back(CreateButtonTG("Добавить команду", "CreateCommand"));
    thirdLineButtons.push_back(CreateButtonTG("Удалить команду", "DeleteCommand"));

    keyboardCreate->inlineKeyboard.push_back(firstLineButtons);
    keyboardCreate->inlineKeyboard.push_back(secondLineButtons);
    keyboardCreate->inlineKeyboard.push_back(thirdLineButtons);
    

    bot.getApi().sendMessage(message->chat->id, "Вы в меню создания мероприятия. Здесь вы можете настроить всё необходимое. По стандарту мероприятие не КП'шное. ", false, 0, keyboardCreate);

    return Success;
}


int MenuCreateCP(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message) {
    TgBot::InlineKeyboardMarkup::Ptr keyboardMenuCP(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> firstLineButtons;
    
    firstLineButtons.push_back(CreateButtonTG("Ввести имя КП", "AddNameCP")); // 
    firstLineButtons.push_back(CreateButtonTG("Ввести информацию об КП", "AddNameInfoCP")); //
    
    std::vector<TgBot::InlineKeyboardButton::Ptr> secondLineButtons;

    secondLineButtons.push_back(CreateButtonTG("Ввести имя препода на КП", "AddNameTeacherCP")); //
    secondLineButtons.push_back(CreateButtonTG("Удалить препода из КП", "AddDeleteTeacherCP")); //

    std::vector<TgBot::InlineKeyboardButton::Ptr> thirdLineButtons;

    thirdLineButtons.push_back(CreateButtonTG("Добавить данное КП", "AddNewCP")); // 
    thirdLineButtons.push_back(CreateButtonTG("Очистить информацию об КП", "ClearCP")); //

    std::vector<TgBot::InlineKeyboardButton::Ptr> fourthLineButtons;

    fourthLineButtons.push_back(CreateButtonTG("Назад (в меню создания КП'шного мероприятия)", "ReturnToMenuCreateEventСP"));

    keyboardMenuCP->inlineKeyboard.push_back(firstLineButtons);
    keyboardMenuCP->inlineKeyboard.push_back(secondLineButtons);
    keyboardMenuCP->inlineKeyboard.push_back(thirdLineButtons);
    keyboardMenuCP->inlineKeyboard.push_back(fourthLineButtons);
    
    bot.getApi().sendMessage(message->chat->id, "Вы в меню создания КП: ", false, 0, keyboardMenuCP);

    return Success;
}
//✓


int MenuDeleteCP(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message, std::vector<std::string> namesCP) {
    TgBot::InlineKeyboardMarkup::Ptr keyboardDeleteCP(new TgBot::InlineKeyboardMarkup);
    for (int i = 0; i < namesCP.size(); i ++) {
        std::vector<TgBot::InlineKeyboardButton::Ptr> LineButtons;
        LineButtons.push_back(CreateButtonTG(namesCP[i], "CP" + std::to_string(i)));
        keyboardDeleteCP->inlineKeyboard.push_back(LineButtons);
    }
    bot.getApi().sendMessage(message->chat->id, "Выберите КП для удаления: ", false, 0, keyboardDeleteCP);
}


int MenuCreateEventCP(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message) {

    TgBot::InlineKeyboardMarkup::Ptr keyboardMenuCreateEvent(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> firstLineButtons;

    firstLineButtons.push_back(CreateButtonTG("Добавить КП", "AddCP")); //
    firstLineButtons.push_back(CreateButtonTG("Удалить КП", "DeleteCP")); // 

    std::vector<TgBot::InlineKeyboardButton::Ptr> secondLineButtons;

    secondLineButtons.push_back(CreateButtonTG("Очистить всё", "Clear"));

    keyboardMenuCreateEvent->inlineKeyboard.push_back(secondLineButtons);
    keyboardMenuCreateEvent->inlineKeyboard.push_back(firstLineButtons);

    bot.getApi().sendMessage(message->chat->id, "Вы в меню создания КП'шного мероприятия: ", false, 0, keyboardMenuCreateEvent);

    return Success;
}


int DeleteEventState(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message) {

    TgBot::InlineKeyboardMarkup::Ptr keyboardDelete(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> firstLineButtons;
    firstLineButtons.push_back(CreateButtonTG("List", "List"));
    keyboardDelete->inlineKeyboard.push_back(firstLineButtons);

    bot.getApi().sendMessage(message->chat->id, "Введите название мероприятия: ", false, 0, keyboardDelete);

    return Success;

}


std::string GetPageMessage(int page, std::vector<std::string> events) {
    int countEvents = events.size();
    std::string eventMessage = "";
    for (int i = 0; i < countEvents; i++) {
        if (i >= page * COUNT_EVENT_IN_PAGE && i < (page + 1) * COUNT_EVENT_IN_PAGE) {
            eventMessage += events[i] + '\n';
        }
    }
    return eventMessage;
}


int ListEventsState(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message) {
    TgBot::InlineKeyboardMarkup::Ptr keyBoardList(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> firstLineButtons;

    firstLineButtons.push_back(CreateButtonTG("->", "->"));
    firstLineButtons.push_back(CreateButtonTG("<-", "<-"));
    
    keyBoardList->inlineKeyboard.push_back(firstLineButtons);

    bot.getApi().sendMessage(message->chat->id,"Вот список мероприятий: ", false, 0, keyBoardList);

    return 0;
}