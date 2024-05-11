#ifndef CWORDFREQUENCY_H_
#define CWORDFREQUENCY_H_

class CWordFrequency
{

   private:
       int countBeginning;
       int countEnd;
       int countWithin;

   public:
       CWordFrequency();
       ~CWordFrequency();
       void incrementCountBeginning();
       void incrementCountEnd();
       void incrementCountWithin();
       int returnCountBeginning();
       int returnCountEnd();
       int returnCountWithin();

};

#endif