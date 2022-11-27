/* Phonebook web microservice using mariaDB
 * By James Skon, Kenyon College, 2022
 */


#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "httplib.h"
#include "PhoneBook.h"
#include "PhoneEntry.h"
const int port = 5004;

using namespace std;

ofstream logfile; 

string jsonResults(vector<PhoneEntry> pbList) {
	string res = "{\"results\":[";
	for (int i = 0; i<pbList.size(); i++) {
		res += pbList[i].json();
		if (i < pbList.size()-1) {
			res +=",";
		}
	}
	res += "]}";
	return res;
}

int main() {
	httplib::Server svr;

  	PhoneBook pb; // Phone Book SQL Interface Object
  
  	vector<PhoneEntry> pbResults;

  	svr.Get("/", [](const httplib::Request & /*req*/, httplib::Response &res) {
    	res.set_header("Access-Control-Allow-Origin","*");
    	res.set_content("Phone API", "text/plain");
  	});
  	
  	svr.Get(R"(/phone/last/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string last = req.matches[1];
    	pbResults = pb.findByLast(last);
    	string json = jsonResults(pbResults);
    	res.set_content(json, "text/json");
    	res.status = 200;
  	});
  	
  	svr.Get(R"(/phone/first/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string first = req.matches[1];
    	pbResults = pb.findByFirst(first);
    	string json = jsonResults(pbResults);
    	res.set_content(json, "text/json");
    	res.status = 200;
  	});  	

  	svr.Get(R"(/phone/type/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string type = req.matches[1];
    	pbResults = pb.findByType(type);
    	string json = jsonResults(pbResults);
    	res.set_content(json, "text/json");
    	res.status = 200;
  	});  
  	
  	svr.Get(R"(/phone/add/(.*)/(.*)/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string first = req.matches[1];
    	string last = req.matches[2];
    	string phone = req.matches[3];
    	string type = req.matches[4];
    	pb.addEntry(first,last,phone,type);

    	res.set_content("{\"status\":\"success\"}", "text/json");
    	res.status = 200;
  	}); 	
 
   	svr.Get(R"(/phone/update/(.*)/(.*)/(.*)/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string ID = req.matches[1];
    	string first = req.matches[2];
    	string last = req.matches[3];
    	string phone = req.matches[4];
    	string type = req.matches[5];
    	pb.editEntry(ID,first,last,phone,type);

    	res.set_content("{\"status\":\"success\"}", "text/json");
    	res.status = 200;
  	}); 

  	svr.Get(R"(/phone/delete/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string ID = req.matches[1];
		pb.deleteEntry(ID);
    	res.set_content("{\"status\":\"success\"}", "text/json");
    	res.status = 200;
  	});  
  	 
  	cout << "Server listening on port " << port << endl;
  	svr.listen("0.0.0.0", port);

}
