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

	bool checkEmail(std::string& email);
	bool checkPassword(std::string& password);

	void saveToFile(const std::string& fileName);
	void loadFromFile(const std::string& fileName);

private:
	const char specialCharacters[10] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')' };

	std::string email;
	std::string password;
	std::string firstName;
	std::string lastName;
};