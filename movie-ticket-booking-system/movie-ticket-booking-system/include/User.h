#pragma once

#include <string>

class User
{
public:
	User(std::string email, std::string password, std::string firstName, std::string lastName);
	~User();

	std::string getEmail();
	std::string getPassword();
	std::string getFirstName();
	std::string getLastName();

	bool checkEmail(const std::string& email);
	bool checkPassword(const std::string& password);

	void saveToFile(const std::string& fileName);
	void loadFromFile(const string& fileName, const string& index);

private:
	const char specialCharacters[10] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')' };

	std::string email;
	std::string password;
	std::string firstName;
	std::string lastName;
};