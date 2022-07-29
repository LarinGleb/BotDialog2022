#ifndef __DIALOGUE_DB_API_H_INCLUDED__
#define __DIALOGUE_DB_API_H_INCLUDED__

#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>

#include <sstream>
#include <iostream>
#include <vector>

#define DIALOG_DB "Dialog"
#define EVENTS_TABLE "Events"
#define REVIEW_TABLE "Reviews"

namespace db_api {

class Connector {
  public:
    Connector() = delete;
    Connector(const char* hostname, const char* username, const char* password,
              const char* db_name) {
        try {
            driver_ = get_driver_instance();

            con_ = driver_->connect(hostname, username, password);

            con_->setSchema(db_name);

            stmt_ = con_->createStatement();

        } catch (sql::SQLException& e) {
            std::cerr << "# ERR: SQLException in " << __FILE__;
            std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
            std::cerr << "# ERR: " << e.what();
            std::cerr << " (MySQL error code: " << e.getErrorCode();
            std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        } catch (std::exception& ex) {
            std::cerr << "STD EXCEPTION: " << ex.what() << std::endl;
        } catch (const char* ex) {
            std::cerr << "EXCEPTION: " << ex << std::endl;
        }
    }

    ~Connector() {
        delete stmt_;
        delete con_;
    }
    void ExecuteRequest(const std::string request);
    sql::ResultSet* GetReviewByName(std::string name);

    void AddEvent(const std::string name, const time_t data, const int bodyType, const int structType, const int commandType);
    void AddReview(const std::string name, const std::string ests, const int id, const bool more, const std::string review);
    void UpdateTime(const std::string name, const std::string time);

    std::vector<std::string> PossibleEvents(const int id);

    std::vector<int> TypeEventByName(const std::string name);

    std::vector<std::string> AllReviews(std::string name);
    std::vector<std::string> AllEsts(std::string name);
    std::vector<int> MoreEvent(std::string name);

    std::string GetEventName(std::string name);
    std::vector<std::string> GetEventsBeetwenTime(const std::string down_end, const std::string up_end);
    

  private:
    sql::Driver*     driver_;
    sql::Connection* con_;
    sql::Statement*  stmt_;
};
}; // namespace db_api

//
#endif
