#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cctype>


#include "CWordFrequency.h"
#include "RandomNumberGenerator.h"

#ifndef CRANDOMNAME_H_
#define CRANDOMNAME_H_

class CRandomName
{

    private:

        std::string errorMessage;
        std::ifstream *fileStreamIn{};
        std::ofstream *fileStreamOut{};
        std::map<char, std::map<char, CWordFrequency> > baseMap;
        std::map<char, CWordFrequency> sequenceFrequencyMap;
        std::vector<char> startChars;
        std::vector<char> availableChars;
        CWordFrequency tempFrequency;

        const float DesiredConsonantVowelProportion {0.45};

    public:

        CRandomName();
        ~CRandomName();
        void inputFile(std::ifstream &streamHandle);
        void processFile();
        void outputList(std::ofstream &streamHandle);
        std::string outputName(double minLength, double maxLength);
        static bool isVowel(char ch);

};

#endif