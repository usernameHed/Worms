#ifndef _GRENADE_HH_
#define _GRENADE_HH_

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

class Grenade
{
public:
  double XPos = 0.0;
  double YPos = 0.0;
  double XVel = 0.0;
  double YVel = 0.0;
  int angle = 0;
  int vel = 3;
  int bounce = 4;
  int holy = 40;

public:
    Grenade(int x, int y, int angle, int velocity);
    ~Grenade();
    void advance();
    void setNewAngle(/*int angle*/);
    void subBounce(int bounce);
};


#endif /* !_HH */
