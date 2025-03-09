#include "../include/User.h"

#include <iostream>
#include <cstdlib>
#include <regex>
#include <fstream>
#include <nlohmann/json.hpp>

using std::string;
using std::cout;

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


void User::saveToFile(const std::string& fileName)
{
	nlohmann::json data;
	data["email"] = this->email;
	data["password"] = this->password;
	data["firstName"] = this->firstName;
	data["lastName"] = this->lastName;

	std::ofstream file(fileName); 
	if (file.is_open()) {
		file << data.dump(4);  
		file.close();
		cout << "Data saved to " << fileName << std::endl;
	}
	else {
		std::cerr << "Could not open file for writing!" << std::endl;
	}
}

void User::loadFromFile(const std::string& fileName) 
{
	std::ifstream file(fileName);
	if (file.is_open()) {
		nlohmann::json data;
		file >> data;
		file.close();

		this->email = data["email"];
		this->password = data["password"];
		this->firstName = data["firstName"];
		this->lastName = data["lastName"];
		cout << "Data loaded from " << fileName << std::endl;
	}
	else {
		std::cerr << "Could not open file for reading!" << std::endl;
	}
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
