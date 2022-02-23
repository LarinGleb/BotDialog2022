#include "DataBase.h"

namespace db_api {

    void Connector::ExecuteRequest(const std::string request) {
        std::cout << request << "\n";
        stmt_->execute(request.c_str());
    }
    void Connector::AddEvent(const std::string nameEvent, const size_t idEvent){
        Connector::ExecuteRequest("INSERT INTO Reviews.Events (id, name) VALUES (\"" + std::to_string(idEvent) + "\", \"" + nameEvent + "\"" + ')');     
    }

    void Connector::DeleteEvent(const size_t idEvent) {
        Connector::ExecuteRequest("DELETE from  Reviews.Events WHERE id = " + std::to_string(idEvent));
    }

    void Connector::AddReview(const std::string review, const size_t idEvent, const size_t idUser) {
        Connector::ExecuteRequest("INSERT INTO Reviews.Events (id, reviews) VALUES (" + std::to_string(idEvent) + ", " + review + ")");
    }

    std::vector<std::string> Connector::GetAllEvents() {
        std::string request = "SELECT name FROM Reviews.Events";
        sql::ResultSet* eventsInTable = stmt_->executeQuery(request);
        std::vector<std::string> Events;

        while (eventsInTable->next()) {

            Events.push_back(eventsInTable->getString("name"));
        }
        return Events;
        
    }

};