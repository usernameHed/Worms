#include "Grenade.hh"

Grenade::Grenade(int x, int y, int angle, int velocity)
{
  this->XPos = x;
  this->YPos = y;
  this->angle = angle;
  this->vel = 2 + velocity;
  this->XVel = cos(this->angle / 180.0 * M_PI) * this->vel;
  this->YVel = - sin(this->angle / 180.0 * M_PI) * this->vel;
}

Grenade::~Grenade()
{

}

void Grenade::advance()
{
  this->XPos += this->XVel;
  this->YPos += this->YVel;

  //if (angle > 90 && angle <= 0)
  if (angle < 90)
    this->angle -= 4;
  else
    this->angle += 4;
  if (this->angle < -90)
    this->angle = -90;
  if (this->angle > 270)
    this->angle = 270;

  std::cout << "angle: " << angle << std::endl;

  this->XVel = cos(this->angle / 180.0 * M_PI) * this->vel;
  this->YVel = - sin(this->angle / 180.0 * M_PI) * this->vel;
}

void Grenade::setNewAngle(/*int angl*/)
{
  this->angle *= -1;
  this->vel--;
  if (this->vel < 2)
    this->vel = 2;
  this->XVel = cos(this->angle / 180.0 * M_PI) * this->vel;
  this->YVel = - sin(this->angle / 180.0 * M_PI) * this->vel;
}

void Grenade::subBounce(int bounce)
{
  --this->bounce;
  if (this->bounce < 0)
    this->bounce = 0;
}
