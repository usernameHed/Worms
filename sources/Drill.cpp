#include "Drill.hh"

Drill::Drill(int x, int y, int angle, int velocity)
{
  this->XPos = x;
  this->YPos = y;
  this->angle = angle;
  this->vel = velocity;
  this->XVel = cos(this->angle / 180.0 * M_PI) * this->vel;
  this->YVel = - sin(this->angle / 180.0 * M_PI) * this->vel;
}

Drill::~Drill()
{

}

void Drill::advance()
{
  this->XPos += this->XVel;
  this->YPos += this->YVel;
  ++this->cran;
}
