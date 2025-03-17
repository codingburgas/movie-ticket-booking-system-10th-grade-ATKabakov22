#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Utiles
{
public:
	static void loadFile(const std::string& fileName, std::string& dataToSave);
	static void loadFile(const std::string& fileName, nlohmann::json& dataToSave);

	static void saveToFile(const std::string& fileName, const nlohmann::json& data);
	static bool isFileEmpty(const std::string& fileName);
};