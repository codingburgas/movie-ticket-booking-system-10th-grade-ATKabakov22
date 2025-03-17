#include "../include/Utiles.h"

#include <fstream>
#include <iostream>

void Utiles::loadFile(const std::string& fileName, std::string& dataToSave)
{
	std::ifstream file(fileName);

	if (file.is_open()) {
		file >> dataToSave;
		file.close();
	}
	else {
		std::cerr << "Could not open file for reading!" << std::endl;
	}
}

void Utiles::loadFile(const std::string& fileName, nlohmann::json& dataToSave)
{
	std::ifstream file(fileName);

	if (file.is_open()) {
		file >> dataToSave;
		file.close();
	}
	else {
		std::cerr << "Could not open file for reading!" << std::endl;
	}
}

void Utiles::saveToFile(const std::string& fileName, const nlohmann::json& data) {
	nlohmann::json existingData;
	nlohmann::json inData = data;

	if (!Utiles::isFileEmpty(fileName)) {
		Utiles::loadFile(fileName, existingData);
	}

	if (!existingData.is_array()) {
		existingData = nlohmann::json::array();
	}

	inData["id"] = existingData.size() + 1;


	existingData.push_back(inData);

	std::ofstream outFile(fileName);
	if (outFile.is_open()) {
		outFile << existingData.dump(4);
		outFile.close();
		std::cout << "Data saved to " << fileName << std::endl;
	}
	else {
		std::cerr << "Could not open file for writing!" << std::endl;
	}
}


bool Utiles::isFileEmpty(const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return false; 
    }

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();

    file.close();
    return fileSize == 0;
}
