#include "../include/users.h"

User::User(string Email, string Password, string FirstName, string LastName)
{
	SetEmail(Email);
	SetPassword(Password);
	SetFirstName(FirstName);
	SetLastName(LastName);
}

User::~User()
{
}

void User::SetEmail(string& Email)
{
	string domain = Email.substr(Email.find('@') + 1);
	string command = "nslookup -type=MX " + domain + " > nul 2>&1";

	if (std::system(command.c_str()) != 0) {
		this->Email = Email;
	}
	else {
		std::cout << "Invalid email address" << std::endl;
		exit(1);
	}
}

void User::SetPassword(string& Password)
{
	this->Password = Password;
}

void User::SetFirstName(string& FirstName)
{
	this->FirstName = FirstName;
}

void User::SetLastName(string& LastName)
{
	this->LastName = LastName;
}



string User::GetEmail()
{
	return this->Email;
}

string User::GetPassword()
{
	return this->Password;
}

string User::GetFirstName()
{
	return this->FirstName;
}

string User::GetLastName()
{
	return this->LastName;
}
