#include "../include/User.h"

User::User(string email, string password, string firstName, string lastName)
{
	this->password = password;
	this->email = email;
	this->firstName = firstName;
	this->lastName = lastName;
}

User::~User()
{
}

bool User::checkEmail(string& email)
{
	std::regex email_regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
	if (!std::regex_match(email, email_regex)) {
		cout << "Invalid email" << std::endl;
		return false;
	}

	string domain = email.substr(email.find('@') + 1);
	string command = "nslookup -type=MX " + domain + " > nul 2>&1";

	if (std::system(command.c_str()) == 0) {
		return true;
	}
	else {
		cout << "Invalid email domain" << std::endl;
		return false;
	}
}

bool User::checkPassword(string& password)
{
	if (password.size() < 6)
	{
		cout << "password must be at least 6 characters long" << std::endl;
		return false;
	}
	for (size_t i = 0; i < 10; i++)  
	{
		if (password.find(specialCharacters[i]) != string::npos) {  
			return true;
		}
	}
	cout << "password must contain at least one special character" << std::endl;
	return false;
}


string User::getEmail()
{
	return this->email;
}

string User::getPassword()
{
	return this->password;
}

string User::getFirstName()
{
	return this->firstName;
}

string User::getLastName()
{
	return this->lastName;
}
