#pragma once

#include <nlohmann/json.hpp>
#include <string>

class User
{
public:
	User(std::string email = "", std::string password = "", std::string firstName = "", std::string lastName = "");
	~User();

	size_t getId();
	std::string getEmail();
	std::string getPassword();
	std::string getFirstName();
	std::string getLastName();

	bool checkEmail(const std::string& email, const std::string& fileName);
	bool checkPassword(const std::string& password);

	nlohmann::json saveAsJson();
	void loadFromFile(const std::string& fileName, const std::string& emailToFind);
	void loadFromFile(const std::string& fileName, const size_t& index);
	void deleteFromFile(const std::string& fileName);

	void displayUser();
	void eraseUser();
private:
	const char specialCharacters[10] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')' };

	size_t id;
	std::string email;
	std::string password;
	std::string firstName;
	std::string lastName;
};