#include "../include/User.h"
#include "../include/Utiles.h"

#include <iostream>
#include <cstdlib>
#include <regex>
#include <fstream>

using std::string;
using std::cout;

User::User(std::string email, std::string password, std::string firstName, std::string lastName)
	: email(email), password(password), firstName(firstName), lastName(lastName)
{
}

User::~User()
{
}

bool User::checkEmail(const string& email, const string& fileName)
{
	nlohmann::json data;
	if (!Utiles::isFileEmpty(fileName)) {
		Utiles::loadFile(fileName, data);
	}

	for (const auto& item : data) {
		if (item["email"] == email) {
			cout << "Email already exists" << std::endl;
			return false;
		}
	}
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

bool User::checkPassword(const string& password)
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

nlohmann::json User::saveAsJson() {
	nlohmann::json data;
	data["email"] = this->email;
	data["password"] = this->password;
	data["firstName"] = this->firstName;
	data["lastName"] = this->lastName;
	return data;
}

void User::loadFromFile(const string& fileName, const string& emailToFind)
{
	nlohmann::json data;
	if (!Utiles::isFileEmpty(fileName)) {
		Utiles::loadFile(fileName, data);
	}

	for (const auto& item : data) {
		if (item["email"] == emailToFind) {
			this->id = item["id"];
			this->email = item["email"];
			this->firstName = item["firstName"];
			this->lastName = item["lastName"];
			this->password = item["password"];
			displayUser();
			return;
		}
	}
	std::cerr << "User not found!" << std::endl;
}

void User::loadFromFile(const string& fileName, const size_t& index)
{
	nlohmann::json data;
	if (!Utiles::isFileEmpty(fileName)) {
		Utiles::loadFile(fileName, data);
	}
	if (index < data.size()) {
		this->id = data[index]["id"];
		this->email = data[index]["email"];
		this->firstName = data[index]["firstName"];
		this->lastName = data[index]["lastName"];
		this->password = data[index]["password"];
		displayUser();
	}
	else {
		std::cerr << "Index out of range!" << std::endl;
	}
}

void User::deleteFromFile(const string& fileName){
	nlohmann::json data;
	if (!Utiles::isFileEmpty(fileName)) {
		Utiles::loadFile(fileName, data);
	}
	nlohmann::json newData = nlohmann::json::array();
	for (const auto& item : data) {
		if (item["email"] != this->email) {
			newData.push_back(item);
		}
	}
	std::ofstream outFile(fileName);
	if (outFile.is_open()) {
		outFile << newData.dump(4);
		outFile.close();
		std::cout << "User deleted" << std::endl;
	}
	else {
		std::cerr << "Could not open file for writing!" << std::endl;
	}
}

void User::displayUser()
{
	cout << "id: " << this->id << "\n";
	cout << "Email: " << this->email << "\n";
	cout << "First Name: " << this->firstName << "\n";
	cout << "Last Name: " << this->lastName << "\n";
	cout << "Password: " << this->password << "\n";
}

void User::eraseUser() {
	this->email = "";
	this->firstName ="";
	this->lastName = "";
	this->password = "";
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

size_t User::getId()
{
	return this->id;
}