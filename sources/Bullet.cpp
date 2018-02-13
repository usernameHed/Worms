#include "Bullet.hh"

Bullet::Bullet(int x, int y, int angle, int velocity)
{
  this->XPos = x;
  this->YPos = y;
  this->angle = angle - 5 + rand() % 11;
  this->vel = 2 + velocity / 2;
  this->XVel = cos(this->angle / 180.0 * M_PI) * this->vel;
  this->YVel = - sin(this->angle / 180.0 * M_PI) * this->vel;
}

Bullet::~Bullet()
{

}

void Bullet::advance()
{
  this->XPos += this->XVel;
  this->YPos += this->YVel;
}

void Bullet::setSpeed(int speed)
{
  this->vel = speed;
  this->XVel = cos(this->angle / 180.0 * M_PI) * this->vel;
  this->YVel = - sin(this->angle / 180.0 * M_PI) * this->vel;
}
