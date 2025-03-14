#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Utiles
{
public:
	static void loadFile(const std::string& fileName, std::string& dataToSave);
	static void loadFile(const std::string& fileName, nlohmann::json& dataToSave);
	static bool isFileEmpty(const std::string& fileName);
};