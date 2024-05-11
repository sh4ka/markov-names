#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

#include "CWordFrequency.h"

#ifndef CRANDOMNAME_H_
#define CRANDOMNAME_H_

class CRandomName
{

    private:

        std::string errorMessage;
        std::ifstream *fileStreamIn;
        std::ofstream *fileStreamOut;
        std::map<char, std::map<char, CWordFrequency> > baseMap;
        std::map<char, CWordFrequency> sequenceFrequencyMap;
        std::vector<char> startChars;
        std::vector<char> availableChars;
        CWordFrequency tempFrequency;

    public:

        CRandomName();
        ~CRandomName();
        void inputFile(std::ifstream &streamHandle);
        void processFile(bool NoWhiteSpaceSkip);
        void outputList(std::ofstream &streamHandle);
        std::string outputName(double minLength, double maxLength);

};

#endif