#ifndef _DYNAMIT_HH_
#define _DYNAMIT_HH_

#include <iostream>

class Dynamit
{
public:
  int XPos = 0;
  int YPos = 0;
  int holy = 70;

public:
    Dynamit(int x, int y);
    ~Dynamit();

    void fall(int fall);
};


#endif /* !_HH */
