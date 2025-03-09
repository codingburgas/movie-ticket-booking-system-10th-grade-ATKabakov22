#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <regex>

using std::string;
using std::cout;

class User
{
public:
	User(string email, string password, string firstName, string lastName);
	~User();

	string getEmail();
	string getPassword();
	string getFirstName();
	string getLastName();

	bool checkEmail(string& email);
	bool checkPassword(string& password);

private:
	const char specialCharacters[10] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')' };

	string email;
	string password;
	string firstName;
	string lastName;
};