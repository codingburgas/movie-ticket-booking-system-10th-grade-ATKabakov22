#include "../include/Member.h"

#include <iostream>
#include <string>
#include <ctime>
#include <cctype>
#include <thread>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using std::string;
using std::cout;

size_t Member::writeCallback(void* contents, size_t size, size_t nmemb, string* output)
{
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

bool Member::luhnCheck(const string& cardNumber)
{
    int sum = 0;
    bool doubleDigit = false;

    for (int i = cardNumber.length() - 1; i >= 0; i--) {
        if (!std::isdigit(cardNumber[i])) {
            return false;
        }
        int digit = cardNumber[i] - '0';

        if (doubleDigit) {
            digit = digit * 2;
            if (digit > 9) {
                digit = digit - 9;
            }
        }

		sum = digit + sum;
        doubleDigit = !doubleDigit;
    }

    return (sum % 10 == 0);
}

bool Member::isValidExpirationDate(int month, int year)
{
    if (month < 1 || month > 12) {
        return false;
    }

    time_t t = time(nullptr);
    tm now;
    localtime_s(&now, &t);

    int currentYear = now.tm_year % 100;
    int currentMonth = now.tm_mon + 1;

    return (year > currentYear) || (year == currentYear && month >= currentMonth);
}

bool Member::isValidCVV(const string& cvv, const string& cardType)
{
    if (cardType == "American Express") {
        return cvv.length() == 4;
    }
    return cvv.length() == 3;
}

string Member::getCardInfoFromAPI(const string& bin) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        return "Error initializing cURL";
    }

    string url = "https://lookup.binlist.net/" + bin;
    string responseData;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        return "Error fetching data";
    }

    if (res == CURLE_HTTP_RETURNED_ERROR) {
        long responseCode;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        if (responseCode == 429) {
            std::cerr << "Rate limit exceeded. Retrying in 30 seconds..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(30));  
            res = curl_easy_perform(curl);
        }
    }
    return responseData;
}

bool Member::verifyCardDetails(const string& cardNumber, int month, int year, const string& cvv) {
    if (!luhnCheck(cardNumber)) {
        cout << "Invalid card number.\n";
        return false;
    }

    string bin = cardNumber.substr(0, 6);
    string apiResponse = getCardInfoFromAPI(bin);
    nlohmann::json parsedData = nlohmann::json::parse(apiResponse, nullptr, false);

    if (parsedData.is_discarded()) {
        cout << "BIN lookup failed.\n";
        return false;
    }

    string cardType = parsedData["scheme"].is_string() ? parsedData["scheme"] : "Unknown";
    string bank = parsedData["bank"]["name"].is_string() ? parsedData["bank"]["name"] : "Unknown";

    if (cardType == "Unknown") {
        cout << "Invalid BIN (unknown issuer).\n";
        return false;
    }

    if (!isValidExpirationDate(month, year)) {
        cout << "Expired card.\n";
        return false;
    }

    if (!isValidCVV(cvv, cardType)) {
        cout << "Invalid CVV format for " << cardType << ".\n";
        return false;
    }

    cout << "Card is valid! Issued by: " << bank << " (" << cardType << ")\n";
    return true;
}