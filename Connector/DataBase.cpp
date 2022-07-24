#include <vector>

#include "DataBase.h"
#include "../ReviewBot/Time/Time.h"

namespace db_api {

    void Connector::ExecuteRequest(const std::string request) {
        std::cout << request << "\n";
        stmt_->execute(request.c_str());
    }
    void Connector::AddEvent(const std::string name, const time_t data, const int bodyType, const int structType, const int commandType){
        Connector::ExecuteRequest(std::string("INSERT INTO ") + DIALOG_DB + "." + EVENTS_TABLE + std::string("(Name,Time,BodyType,StructType,CommandType) VALUES(\"") + name + std::string("\",STR_TO_DATE(\"") +  TimeToSQL(data) + std::string("\",\'") + DATA_FORMAT +  "\')," + std::to_string(bodyType) + ',' + 
        std::to_string(structType) + ',' + std::to_string(commandType) + std::string(");"));     
    }

    void Connector::AddReview(const std::string name, const std::string activeEst, const std::string structEst, const std::string commandEst, const std::string review, const bool more) {
        Connector::ExecuteRequest(std::string("INSERT INTO ") + DIALOG_DB + "." + REVIEW_TABLE + std::string(" VALUES (\"") + name + std::string("\", \"") + activeEst + 
        std::string("\", \"") + structEst + std::string("\", \"") + commandEst + std::string("\", \"") + review + std::string("\", ") + std::to_string((int)more) + std::string(");"));
    }

    std::vector<int> Connector::TypeEventByName(const std::string name) {
        sql::ResultSet* typesFromSQL = stmt_->executeQuery(std::string("SELECT * FROM ") + DIALOG_DB + "." + EVENTS_TABLE + std::string(" WHERE Time > CURDATE() - INTERVAL ") 
        + MAX_INTERVAL_DAY + std::string(" DAY AND name = ") + std::string("\"") + name + "\"");
        std::vector<int> types;
        while(typesFromSQL->next()) {
            types.push_back(typesFromSQL->getInt("BodyType"));
            types.push_back(typesFromSQL->getInt("StructType"));
            types.push_back(typesFromSQL->getInt("CommandType"));
        }
        
        return types;
    }
    std::vector<std::string> Connector::PossibleEvents() {
        std::vector<std::string> names;
        sql::ResultSet* eventsNames = stmt_->executeQuery(std::string("SELECT Name FROM ") + DIALOG_DB + "." + EVENTS_TABLE + std::string(" WHERE Time > CURDATE() - INTERVAL ") + MAX_INTERVAL_DAY + std::string(" DAY"));
        while(eventsNames->next()) {
            names.push_back(eventsNames->getString("Name"));
        }
        return names;
    }

    // Get Time event by it name
    std::string Connector::GetTime(std::string name) {
        sql::ResultSet* timeFromDB = stmt_->executeQuery(std::string("SELECT * FROM ") + DIALOG_DB + "." + EVENTS_TABLE + std::string(" WHERE Time > CURDATE() - INTERVAL ") 
        + MAX_INTERVAL_DAY + std::string(" DAY AND name = ") + std::string("\"") + name + "\"");
        std::string timeEvent;
        while(timeFromDB->next()) {
            timeEvent = timeFromDB->getString("Time");
        }
        return timeEvent;
    }

    // Get All reviews event by it name
    std::vector<std::string> Connector::AllReviews(std::string name) {
        sql::ResultSet* eventsReviews = stmt_->executeQuery(std::string("SELECT * FROM ") + DIALOG_DB + "." + REVIEW_TABLE + std::string(" WHERE NameEvent = \"") + name + std::string("\";"));
        std::vector<std::string> reviews;
        while(eventsReviews->next()) {
            reviews.push_back(eventsReviews->getString("Review"));
        }
        return reviews;
    }

    // Get all ests event by it name
    std::vector<std::vector<std::string>> Connector::AllEsts(std::string name) {
        sql::ResultSet* eventsEsts = stmt_->executeQuery(std::string("SELECT * FROM ") + DIALOG_DB + "." + REVIEW_TABLE + std::string(" WHERE NameEvent = \"") + name + std::string("\";"));
        std::vector<std::vector<std::string>> ests;
        while(eventsEsts->next()) {
            ests.push_back({eventsEsts->getString("ActionEsts"), eventsEsts->getString("StructEsts"), eventsEsts->getString("CommandEsts")});
        }
        return ests;
    }

    std::vector<int> Connector::MoreEvent(std::string name) {
        sql::ResultSet* eventMore = stmt_->executeQuery(std::string("SELECT * FROM ") + DIALOG_DB + "." + REVIEW_TABLE + std::string(" WHERE NameEvent = \"") + name + std::string("\";"));
        std::vector<int> more;
        while(eventMore->next()) {
            more.push_back(eventMore->getInt("More"));
        }
        return more;
    }

};