#ifndef __REVIEW_DATABASE_STRUCT__

#define __REVIEW_DATABASE_STRUCT__


struct review_database_t {

	int cr_id;
	std::string review;
	int need_more;
	std::string ests;

	std::string SaveCSV() {
	    return std::to_string(cr_id) + std::string(";") + ests + std::string(";") + std::to_string(need_more) + std::string( ";\"") + review + std::string("\"\n");		    
	}
};

typedef struct review_database_t ReviewDataBase;

#endif
