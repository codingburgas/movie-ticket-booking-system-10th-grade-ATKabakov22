#include "include/User.h"
#include "include/Admin.h"

#include <iostream>

int main() {
	User user("example@gmail.com", "Password", "FirstName", "LastName");
	user.saveToFile("files/user.json");
	user.loadFromFile("files/user.json");
	std::cout << "Email: " << user.getEmail() << std::endl;
}