/* Phonebook console test program using mariaDB
 * By James Skon, Kenyon College, 2022
 */
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "PhoneBook.h"
#include "PhoneEntry.h"


using namespace std;

int main(){
    PhoneBook pb;
    vector<PhoneEntry> pbResults;
    char o;

    cout << "Phone Book test program" << endl;

    cout << "Select an option (1-search first, 2-search last, 3-search type, 4-add, 5-edit, 6-delete, 7-end): ";
    cin >> o;

    while (o!='7') {
      if (o=='1') {
        cout << "Enter first name to find:";
        string firstMatch;
        cin >> firstMatch;

        pbResults = pb.findByFirst(firstMatch);

        for (int i = 0; i<pbResults.size(); i++) {
        	cout << pbResults[i].text() << endl;
        }
      } else if (o=='2') {

        cout << "Enter last name to find:";
        string lastMatch;
        cin >> lastMatch;

        pbResults = pb.findByLast(lastMatch);

        for (int i = 0; i<pbResults.size(); i++) {
			cout << pbResults[i].text() << endl;
        }
      } else if (o=='3') {
        cout << "Enter type to find:";
        string typeMatch;
        cin >> typeMatch;
        pbResults = pb.findByType(typeMatch);

        for (int i = 0; i<pbResults.size(); i++) {
			cout << pbResults[i].text() << endl;
        }
      } else if (o=='4') {

        cout <<"Enter a first name to add: ";
        string first,last,phone,type;
        cin >> first;
        cout << "Enter a last name to add: ";
        cin >>last;
        cout << "Enter a phone number: ";
        cin >> phone;
        cout << "lastly, end a type: ";
        cin >> type;

        pb.addEntry(first,last,phone,type);
        cout << "Entry added";

      } else if (o=='5') {
        string first,last,phone,type, IDnum;
        cout << "Leave blank to keep same."  << endl;
        cout << "Enter an ID number to edit: ";
        cin >> IDnum;
        PhoneEntry entry=pb.fetchEntry(IDnum);
        cout  << IDnum << endl;
        if (entry.ID.empty()) {
        	cout << "Entry with ID = " << IDnum << " not found!" << endl;
        } else {
        	cout << "Editing: " << entry.text() << endl;
        	cin.ignore();
        	cout << "Enter a new first name("+entry.first+"): ";
        	getline(cin,first);
        	if (first.size()>0) entry.first = first;

        	cout << "Enter a new last name("+entry.last+"): ";
        	getline(cin,last);
        	if (last.size()>0) entry.last = last;
        	
        	cout << "Enter a new phone number("+entry.phone+"): ";
        	getline(cin,phone);
        	if (phone.size()>0) entry.phone = phone;
        	
        	cout << "Enter a new type("+entry.type+"): ";
        	getline(cin,type);
        	if (type.size()>0) entry.type = type;
        	
        	pb.editEntry(entry.ID,entry.first,entry.last,entry.phone,entry.type);
        	cout << "Done!" << endl;
        }
      } else if (o=='6') {

        string IDnum;
        cout << "Enter an ID number to delete: ";
        cin >> IDnum;
        pb.deleteEntry(IDnum);
        cout << "Deleted!" << endl;
      }
      cout << "Seect an option (1-serach first, 2-search last, 3-search type, 4-add, 5-edit, 6-delete, 7-end): ";
      cin >> o;
    }
return 0;
}
