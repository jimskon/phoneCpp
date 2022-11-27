#include <mariadb/conncpp.hpp>
#include "PhoneEntry.h"

PhoneEntry::PhoneEntry() {
}

PhoneEntry::PhoneEntry(sql::SQLString f, sql::SQLString l, sql::SQLString p, sql::SQLString t, sql::SQLString I) {
    first = f;
    last = l;
    phone = p;
    type = t;
    ID=I;
}
