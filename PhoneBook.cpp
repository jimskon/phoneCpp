#include <vector>
#include <iostream>
#include <mariadb/conncpp.hpp>
#include "PhoneBook.h"
#include "PhoneEntry.h"



PhoneBook::PhoneBook() {
  	// Instantiate Driver
  	driver = sql::mariadb::get_driver_instance();
  	
 	// Configure Connection
  	// The URL or TCP connection string format is
  	// ``jdbc:mariadb://host:port/database``.
  	sql::SQLString url(db_url);

}


vector<PhoneEntry> PhoneBook::findByLast(string last) {

	cout << "Find:" << last << endl;

    vector<PhoneEntry> list;
    
    // Use a properties map for the other connection options
  	sql::Properties properties({{"user", user}, {"password",pass}});

    // Establish Connection
  	std::unique_ptr<sql::Connection>  conn(driver->connect(db_url, properties));
    
    if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
   	}
 	cout << "Start1! " << endl;  	
    // Create a new Statement
	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
	cout << "Start2! " << endl;
    
    // Execute query
    sql::ResultSet *res = stmnt->executeQuery("SELECT * FROM PhoneBook WHERE Last like '%"+last+"%'");
    
    // Loop through and print results
    while (res->next()) {
    	PhoneEntry entry(res->getString("First"),res->getString("Last"),
			res->getString("Phone"),res->getString("Type"),
	    	res->getString("ID"));
	    	
	    list.push_back(entry);

    }
    return list;

}

vector<PhoneEntry> PhoneBook::findByFirst(string first) {

  // Establish Connection
  std::unique_ptr<sql::Connection>  conn(driver->connect(db_url, properties));
    
  if (!conn) {
   	cerr << "Invalid database connection" << endl;
   	exit (EXIT_FAILURE);
  }
   	
  std::auto_ptr<sql::Statement> stmt(conn->createStatement());

  vector<PhoneEntry> list;
  stmt->execute("SELECT * FROM PhoneBook WHERE First like '%"+first+"%'");
  std::auto_ptr< sql::ResultSet > res;
  do {
    res.reset(stmt->getResultSet());
    while (res->next()) {
      PhoneEntry entry(res->getString("First"),res->getString("Last"),
		       res->getString("Phone"),res->getString("Type"),
	res->getString("ID"));
        list.push_back(entry);

    }
  } while (stmt->getMoreResults());
  return list;

}

vector<PhoneEntry> PhoneBook::findByType(string type) {

  // Establish Connection
  std::unique_ptr<sql::Connection>  conn(driver->connect(db_url, properties));
    
  if (!conn) {
   	cerr << "Invalid database connection" << endl;
   	exit (EXIT_FAILURE);
  }
   	
  std::auto_ptr<sql::Statement> stmt(conn->createStatement());

  vector<PhoneEntry> list;
  stmt->execute("SELECT * FROM PhoneBook WHERE Type like '%"+type+"%'");
  std::auto_ptr< sql::ResultSet > res;
  do {
    res.reset(stmt->getResultSet());
    while (res->next()) {
      PhoneEntry entry(res->getString("First"),res->getString("Last"),
		       res->getString("Phone"),res->getString("Type"),
	res->getString("ID"));
      list.push_back(entry);

    }
  } while (stmt->getMoreResults());
  return list;

}

void PhoneBook::addEntry(string first,string last,string phone, string type){
  // Establish Connection
  std::unique_ptr<sql::Connection>  conn(driver->connect(db_url, properties));
    
  if (!conn) {
   	cerr << "Invalid database connection" << endl;
   	exit (EXIT_FAILURE);
  }
  std::auto_ptr<sql::Statement> stmt(conn->createStatement());

  if(type != "Friend" && type != "Family" && type!="Business"){
      type="Other";
  }
  stmt->execute("INSERT INTO PhoneBook(First,Last,Phone,Type) VALUES ('"+first+"','"+last+"','"+phone+"','"+type+"')");
}


void PhoneBook::editEntry(string idnum,string first,string last,string phone, string type){
  // Establish Connection
  std::unique_ptr<sql::Connection>  conn(driver->connect(db_url, properties));
    
  if (!conn) {
   	cerr << "Invalid database connection" << endl;
   	exit (EXIT_FAILURE);
  }
  std::auto_ptr<sql::Statement> stmt(conn->createStatement());

  if(type != "Friend" && type != "Family" && type!="Business"){
    type="Other";
  }
  stmt->execute("UPDATE PhoneBook SET First = '"+first+"', Last ='"+last+"', Phone ='"+phone+"', Type ='"+type+"' WHERE ID='"+idnum+"'");
}


void PhoneBook::deleteEntry(string idnum){
  // Establish Connection
  std::unique_ptr<sql::Connection>  conn(driver->connect(db_url, properties));
    
  if (!conn) {
   	cerr << "Invalid database connection" << endl;
   	exit (EXIT_FAILURE);
  }

  std::auto_ptr<sql::Statement> stmt(conn->createStatement());

  stmt->execute("DELETE FROM PhoneBook WHERE ID='"+idnum+"'");
}
