#include "CWordFrequency.h"

CWordFrequency::CWordFrequency() : countBeginning(0), countEnd(0),
countWithin(0)
{

}

CWordFrequency::~CWordFrequency()
{

}

void CWordFrequency::incrementCountBeginning()
{
    ++countBeginning;
}

void CWordFrequency::incrementCountEnd()
{
    ++countEnd;
}

void CWordFrequency::incrementCountWithin()
{
    ++countWithin;
}

int CWordFrequency::returnCountBeginning()
{
    return countBeginning;
}

int CWordFrequency::returnCountEnd()
{
    return countEnd;
}

int CWordFrequency::returnCountWithin()
{
    return countWithin;
}