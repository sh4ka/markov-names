#include <iostream>
#include <string>
#include <set>
#include <random>
#include <cctype>
#include "CRandomName.h"
#include "RandomNumberGenerator.h"

using namespace std;

CRandomName::CRandomName()
= default;

CRandomName::~CRandomName()
{
    fileStreamOut->close();
    fileStreamIn->close();
}

void CRandomName::inputFile(std::ifstream &streamHandle)
{
    fileStreamIn = &streamHandle;
}

void CRandomName::processFile()
{

    std::string word;
    std::set<char> startCharsSet;
    std::set<char> availableCharsSet;

    char base;
    char sequence;
    int wordPosition;

    startChars.clear();
    availableChars.clear();

    while (fileStreamIn->good())
    {
        *fileStreamIn >> word;

        if (word.length() > 1)
        {
            startCharsSet.insert(word[0]);
            availableCharsSet.insert(word[0]);

            for (wordPosition = 0; (wordPosition + 1) < (word.length()); wordPosition++)
            {
                availableCharsSet.insert(word[wordPosition + 1]);
                base = word[wordPosition];
                sequence = word[wordPosition + 1];

                CWordFrequency &wf = baseMap[base][sequence];

                if (wordPosition == 0)
                {
                    wf.incrementCountBeginning();
                }
                else if ((wordPosition + 1) >= (word.length() - 1))
                {
                    wf.incrementCountEnd();
                }
                else if ((wordPosition > 0) && ((wordPosition + 1) < (word.length() - 1)))
                {
                    wf.incrementCountWithin();
                }
            }
        }
    }

    set<char>::iterator it;
    for ((it = startCharsSet.begin()); it != startCharsSet.end(); it++)
        startChars.push_back(*it);
    for ((it = availableCharsSet.begin()); it != availableCharsSet.end(); it++)
        availableChars.push_back(*it);
}

void CRandomName::outputList(std::ofstream &streamHandle)
{
    fileStreamOut = &streamHandle;

    std::map<char, std::map<char, CWordFrequency>>::iterator itr;

    std::map<char, CWordFrequency>::iterator itr2;

    for (itr = baseMap.begin(); itr != baseMap.end(); itr++)
    {
        sequenceFrequencyMap = itr->second;
        for (itr2 = sequenceFrequencyMap.begin(); itr2 != sequenceFrequencyMap.end(); itr2++)
        {
            tempFrequency = itr2->second;
            *fileStreamOut << itr->first << " " << itr2->first << " "
                           << tempFrequency.returnCountBeginning() << " " << tempFrequency.returnCountWithin() << " "
                           << tempFrequency.returnCountEnd() << std::endl;
        }
    }
}

std::string CRandomName::outputName(double minLength, double maxLength)
{
    RandomDoubleGenerator rdg(0.0, 1.0);
    std::string name;
    std::vector<char> freqVector;
    double range = (maxLength - minLength) + 1;
    int rangeLength = static_cast<int>(minLength + (range * (rdg.getRandomDouble())));
    char a = startChars.at(static_cast<int>(startChars.size() * rdg.getRandomDouble()));
    name += a;

    for (int counter = 1; counter < rangeLength; counter++)
    {
        int cdc = 0;
        if (baseMap.find(a) != baseMap.end())
        {
            for (int count = 0; count < availableChars.size(); count++)
            {
                char b = availableChars.at(count);
                if (baseMap[a].find(b) != baseMap[a].end())
                {
                    if (counter == 1)
                    {
                        for (int cc = 0; cc < (baseMap[a][b].returnCountBeginning()); cc++)
                        {
                            freqVector.push_back(b);
                            cdc++;
                        }
                    }
                    else if ((counter + 1) >= (rangeLength - 1))
                    {
                        for (int cc = 0; cc < baseMap[a][b].returnCountEnd(); cc++)
                        {
                            freqVector.push_back(b);
                            cdc++;
                        }
                    }
                    else
                    {
                        for (int cc = 0; cc < baseMap[a][b].returnCountWithin(); cc++)
                        {
                            freqVector.push_back(b);
                            cdc++;
                        }
                    }
                }
            }
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(freqVector.begin(), freqVector.end(), g);
        std::shuffle(freqVector.begin(), freqVector.end(), g);
        std::shuffle(freqVector.begin(), freqVector.end(), g);
        int generated = rdg.getRandomDouble() * cdc;
        name += freqVector.at(generated);
        a = freqVector.at(generated);
    }

    int vowels = 0, consonants = 0;

    for (char ch : name) {
        if (std::isalpha(ch)) { // Check if the character is a letter
            if (isVowel(ch)) {
                vowels++;
            } else {
                consonants++;
            }
        }
    }

    if (consonants > 0) {
        double proportion = static_cast<double>(vowels) / consonants;
        if (proportion >= DesiredConsonantVowelProportion) {
            return name;
        }
    }

    return outputName(minLength, maxLength);
}

bool CRandomName::isVowel(char ch) {
    // Convert character to lowercase to handle both cases
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}