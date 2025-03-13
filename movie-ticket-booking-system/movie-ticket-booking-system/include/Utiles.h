#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Utiles
{
public:
	void loadFile(const std::string& fileName, std::string& dataToSave);
	void loadFile(const std::string& fileName, nlohmann::json& dataToSave);
	bool isFileEmpty(const std::string& fileName);
};