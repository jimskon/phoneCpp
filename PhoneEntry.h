#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef PHONEENTRY_H
#define PHONEENTRY_H

class PhoneEntry {
public:
     PhoneEntry();
     PhoneEntry(sql::SQLString f, sql::SQLString l, sql::SQLString p, sql::SQLString t,sql::SQLString I);
     string text();
     string json();
     
     string first;
     string last;
     string phone;
     string type;
     string ID;

private:

};

#endif /* PHONEENTRY_H */

