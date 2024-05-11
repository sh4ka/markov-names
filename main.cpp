#include <iostream>
#include <fstream>
#include "CRandomName.h"

int main()
{
    CRandomName name;

    std::ifstream inFile("../list.txt");

    if (!inFile.is_open()) {
        std::cerr << "Failed to open name table file." << std::endl;
        return 1;
    }

    name.inputFile(inFile);
    name.processFile();

    std::string generatedName = name.outputName(4, 8);
    generatedName[0] = std::toupper(generatedName[0]);

    std::cout << generatedName << '\n';
}