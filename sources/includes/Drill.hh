#ifndef _DRILL_HH_
#define _DRILL_HH_

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

class Drill
{
public:
  double XPos = 0.0;
  double YPos = 0.0;
  double XVel = 0.0;
  double YVel = 0.0;
  int angle = 0;
  int vel = 20;
  int holy = 10;
  int cran = 0;
  int maxCran = 6;

public:
    Drill(int x, int y, int angle, int velocity);
    ~Drill();
    void advance();
};


#endif /* !_HH */
