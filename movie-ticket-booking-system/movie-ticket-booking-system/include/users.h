#pragma once

#include <string>
#include <iostream>
#include <cstdlib>

using std::string;

class User
{
public:
	User(string Email, string Password, string FirstName, string LastName);
	~User();

	string GetEmail();
	string GetPassword();
	string GetFirstName();
	string GetLastName();

private:
	string Email;
	string Password;

	string FirstName;
	string LastName;

	void SetEmail(string& Email);
	void SetPassword(string& Password);
	void SetFirstName(string& FirstName);
	void SetLastName(string& LastName);
};