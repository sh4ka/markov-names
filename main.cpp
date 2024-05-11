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

    inFile.close();

    std::cout << name.outputName(4, 8) << '\n';
}