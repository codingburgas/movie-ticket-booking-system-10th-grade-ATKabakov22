#include "../include/users.h"


User::User(string Email, string Password, string FirstName, string LastName)
{
	SetLastName(LastName);
	SetFirstName(FirstName);
	SetPassword(Password);
	SetEmail(Email);
}

User::~User()
{
}

void User::SetEmail(string Email)
{
	this->Email = Email;
}

void User::SetPassword(string Password)
{
	this->Password = Password;
}

void User::SetFirstName(string FirstName)
{
	this->FirstName = FirstName;
}

void User::SetLastName(string LastName)
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
