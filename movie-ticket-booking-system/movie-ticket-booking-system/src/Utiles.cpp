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
