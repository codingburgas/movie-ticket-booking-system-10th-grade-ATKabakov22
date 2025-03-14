#pragma once

#include <string>

#include "User.h"

using std::string;

class Member : public User
{
	using User::User;
public:
	bool verifyCardDetails(const std::string& cardNumber, int month, int year, const std::string& cvv);
private:
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output);
    bool luhnCheck(const std::string& cardNumber);
    bool isValidExpirationDate(int month, int year);
    bool isValidCVV(const std::string& cvv, const std::string& cardType);
    std::string getCardInfoFromAPI(const std::string& bin);
};