#include "DataBase.h"

namespace db_api {

    void Connector::AddEvent(const std::string nameEvent, const int idEvent){
        std::stringstream sql_request;
        sql_request.str("");
        sql_request << "INSERT INTO Reviews.Events (id, name) VALUES (\"" << idEvent
                    << "\", \"" << nameEvent << "\"" << ')';

        std::cout << sql_request.str() << "\n";
        stmt_->execute(sql_request.str().c_str());
        printf("Created Event\n ");
    }

};