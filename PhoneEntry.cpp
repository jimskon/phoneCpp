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

string PhoneEntry::text() {
	string result = ID + ". ";
	result += first + " ";
	result += last + " ";
	result += phone + " ";
	result += type;
	return result;

}

string PhoneEntry::json() {
	string result = "{\"ID\":\"" + ID + "\",";
	result += "\"first\":\"" + first + "\",";
	result += "\"last\":\"" + last + "\",";
	result += "\"phone\":\"" + phone + "\",";
	result += "\"type\":\"" + type + "\"}";
	return result;

}