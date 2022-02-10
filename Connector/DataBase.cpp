#include "DataBase.h"

namespace db_api {

    void Connector::ExecuteRequest(const std::string request) {
        std::cout << request.str() << "\n";
        stmt_->execute(request.str().c_str());
    }
    void Connector::AddEvent(const std::string nameEvent, const size_t idEvent){
        Connector::ExecuteRequest("INSERT INTO Reviews.Events (id, name) VALUES (\"" << idEvent << "\", \"" << nameEvent << "\"" << ')');     
    }

    void Connector::DeleteEvent(const size_t idEvent) {
        Connector::ExecuteRequest("DELETE * from  Reviews.Events WHERE id = " << idEvent);
    }

    void Connector::AddReview(const std::string review, const size_t idEvent, const size_t idUser) {
        Connector::ExecuteRequest("INSERT INTO Reviews.Events (id, reviews) VALUES (" << idEvent << ", " << review << ")");
    }

};