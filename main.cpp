#include <iostream>
#include "CRandomName.h"

int main()
{
    CRandomName name;

    std::ifstream inFile("list.txt");
    std::ofstream outFile("Stats.txt", std::ios_base::trunc);

    name.inputFile(inFile);
    name.processFile(true);
    name.outputList(outFile);

    std::cout << name.outputName(3, 9) << '\n'
              << name.outputName(3, 9) << '\n'
              << name.outputName(3, 9) << '\n'
              << name.outputName(3, 9) << '\n'
              << name.outputName(3, 9) << '\n';
}