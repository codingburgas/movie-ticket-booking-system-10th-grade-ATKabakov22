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
	User(string Email, string Password, string FirstName, string LastName);
	~User();

	string getEmail();
	string getPassword();
	string getFirstName();
	string getLastName();

private:
	string Email;
	string Password;

	string FirstName;
	string LastName;

	const char specialCharacters[10] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')' };

	void setEmail(string& Email);
	void setPassword(string& Password);
	void setFirstName(string& FirstName);
	void setLastName(string& LastName);
};