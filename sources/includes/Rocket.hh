#ifndef _ROCKET_HH_
#define _ROCKET_HH_

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

class Rocket
{
public:
  double XPos = 0.0;
  double YPos = 0.0;
  double XVel = 0.0;
  double YVel = 0.0;
  int angle = 0;
  int vel = 20;
  int holy = 40;

public:
    Rocket(int x, int y, int angle, int velocity);
    ~Rocket();
    void advance();
};


#endif /* !_HH */
