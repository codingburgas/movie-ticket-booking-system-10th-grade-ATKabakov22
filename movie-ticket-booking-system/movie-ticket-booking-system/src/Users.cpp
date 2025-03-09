#include "../include/users.h"

User::User(string Email, string Password, string FirstName, string LastName)
{
	setEmail(Email);
	setPassword(Password);
	setFirstName(FirstName);
	setLastName(LastName);
}

User::~User()
{
}

void User::setEmail(string& Email)
{
	std::regex email_regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
	if (!std::regex_match(Email, email_regex)) {
		cout << "Invalid email" << std::endl;
		return;
	}

	string domain = Email.substr(Email.find('@') + 1);
	string command = "nslookup -type=MX " + domain + " > nul 2>&1";

	if (std::system(command.c_str()) == 0) {
		this->Email = Email;
	}
	else {
		cout << "Invalid email domain" << std::endl;
	}
}

void User::setPassword(string& Password)
{
	if (Password.size() < 6)
	{
		cout << "Password must be at least 6 characters long" << std::endl;
		return;
	}
	for (size_t i = 0; i < 10; i++)  
	{
		if (Password.find(specialCharacters[i]) != string::npos) {  
			this->Password = Password;
			return;
		}
	}
	cout << "Password must contain at least one special character" << std::endl;
}

void User::setFirstName(string& FirstName)
{
	this->FirstName = FirstName;
}

void User::setLastName(string& LastName)
{
	this->LastName = LastName;
}



string User::getEmail()
{
	return this->Email;
}

string User::getPassword()
{
	return this->Password;
}

string User::getFirstName()
{
	return this->FirstName;
}

string User::getLastName()
{
	return this->LastName;
}
