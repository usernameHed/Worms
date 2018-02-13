#ifndef _BULLET_HH_
#define _BULLET_HH_

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

class Bullet
{
public:
  double XPos = 0.0;
  double YPos = 0.0;
  double XVel = 0.0;
  double YVel = 0.0;
  int angle = 0;
  int vel = 5;
  int holy = 10;

public:
    Bullet(int x, int y, int angle, int velocity);
    ~Bullet();
    void setSpeed(int speed);
    void advance();
};


#endif /* !_HH */
