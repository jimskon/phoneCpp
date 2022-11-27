#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:
USER= skon

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++14  -Wno-deprecated-declarations

RM= /bin/rm -f

all: TestPhoneBook phoneApp PutHTML 

PhoneEntry.o: PhoneEntry.cpp PhoneEntry.h
	$(CC) -c $(CFLAGS) PhoneEntry.cpp

PhoneBook.o: PhoneBook.cpp PhoneBook.h
	$(CC) -c $(CFLAGS) -I/usr/include/cppconn PhoneBook.cpp

TestPhoneBook.o: TestPhoneBook.cpp PhoneEntry.h	PhoneBook.h
	$(CC) -c $(CFLAGS) TestPhoneBook.cpp

TestPhoneBook: TestPhoneBook.o PhoneBook.o PhoneEntry.o
	$(CC) TestPhoneBook.o PhoneBook.o PhoneEntry.o -L/usr/lib -o TestPhoneBook -L/usr/local/lib -lmariadbcpp

phoneApp.o: phoneApp.cpp httplib.h
	$(CC) -c $(CFLAGS) phoneApp.cpp

phoneApp: phoneApp.o PhoneBook.o PhoneEntry.o 
	$(CC) phoneApp.o PhoneBook.o PhoneEntry.o -o phoneApp -L/usr/local/lib -lmariadbcpp

PutHTML:
	cp phoneApp.html /var/www/html/phoneCpp/
	cp phoneApp.js /var/www/html/phoneCpp/
	cp phoneApp.css /var/www/html/phoneCpp/


	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/phoneCpp

clean:
	rm -f *.o  phoneApp TestPhoneBook
