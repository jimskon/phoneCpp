#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
/* uncomment for applications that use vectors */
#include <vector>

//#include "mysql_connection.h"
//#include "mysql_driver.h"
#include <mariadb/conncpp.hpp>

//#include <cppconn/driver.h>
//#include <cppconn/exception.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>
//#include <cppconn/prepared_statement.h>
#include "PhoneEntry.h"

#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#define DB_URL "jdbc:mariadb://localhost:3306/kenyon"
#define USER "kenyon"
#define PASS "GambierOwls"

using namespace std;

class PhoneBook {
public:
    PhoneBook();
    vector<PhoneEntry> find(string search);
    vector<PhoneEntry> findByFirst(string first);
    vector<PhoneEntry> findByLast(string last);
    vector<PhoneEntry> findByType(string type);
    PhoneEntry fetchEntry(string id);
    void addEntry(string first,string last,string phone,string type);
    void editEntry(string idnum,string first,string last,string phone,string type);
    void deleteEntry(string idnum);
private:
    const string db_url=DB_URL;
    const string user=USER;
    const string pass=PASS;
    sql::Driver* driver;
    sql::Properties properties;
    std::unique_ptr<sql::Connection> conn;

};

#endif /* PHONEBOOK_H */
