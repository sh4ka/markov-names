#include <iostream>
#include <string>
#include <set>
#include <iterator>
#include <random>
#include "CRandomName.h"
using namespace std;

CRandomName::CRandomName()
{
    srand(time(NULL));
}

CRandomName::~CRandomName()
{
    fileStreamOut->close();
    fileStreamIn->close();
}

void CRandomName::inputFile(std::ifstream &streamHandle)
{
    fileStreamIn = &streamHandle;
}

// Set the boolean to true if you have a file that contains names with whitespaces. This does mean that the
// end of each name should be marked by a end of line character.
// Also the words will be converted to uppercase automatically
void CRandomName::processFile(bool NoWhiteSpaceSkip)
{

    std::string word;
    std::set<char> startCharsSet;     // these sets are used to list the different starting and available chars.
    std::set<char> availableCharsSet; // they will be converted to vectors later.
                                      // I needed sets for their key ability, and vectors later because they
                                      // offer better access to the elements contained in the vector.
    char base;
    char sequence;
    int wordPosition;

    startChars.clear();
    availableChars.clear();

    while (fileStreamIn->good())
    {
        // Ignore whitespaces between words. Different names should be seperated by a '\n'
        if (NoWhiteSpaceSkip)
        {
            getline(*fileStreamIn, word);
        }
        else
        {
            *fileStreamIn >> word;
        }

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

// Known bugs, if there are not enough names in the seed the program will crash.
std::string CRandomName::outputName(double minLength, double maxLength)
{
    std::string name;
    std::vector<char> freqVector;
    double range = static_cast<double>((maxLength - minLength) + 1);
    int rangeLength = static_cast<int>(minLength + (range * ((double)rand() / (double)(RAND_MAX + 1))));
    char a = startChars.at(static_cast<int>(startChars.size() * rand() / (RAND_MAX + 1.0)));
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
    std:
        mt19937 g(rd());
        std::shuffle(freqVector.begin(), freqVector.end(), g);
        std::shuffle(freqVector.begin(), freqVector.end(), g);
        std::shuffle(freqVector.begin(), freqVector.end(), g);
        int c = (int)(((cdc)*rand() / (RAND_MAX + 1.0)));
        name += freqVector.at(c);
        a = freqVector.at(c);
    }
    return name;
}