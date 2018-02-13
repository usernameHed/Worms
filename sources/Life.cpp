#include "Life.hh"
#include <iostream>

Life::Life(int pv) : _pv(pv)
{
  std::cout << "Adding Life for Worms" << std::endl;
}

Life::~Life()
{

}

int Life::getPv() const
{
  return (this->_pv);
}

Position Life::getPosLife() const
{
  return (this->_posLife);
}

std::vector<int> &Life::getSlifeLifePos()
{
  return (this->_slideLifePos);
}

void Life::setPv(int pv)
{
  this->_pv = pv;

}

void Life::setPosLife(int x, int y)
{
  this->_posLife.x = x;
  this->_posLife.y = y;
}

void Life::setSlideLifePos(int x1, int y1, int x2, int y2)
{
  this->_slideLifePos.clear();
  this->_slideLifePos.push_back(x1);
  this->_slideLifePos.push_back(y1);
  this->_slideLifePos.push_back(x2);
  this->_slideLifePos.push_back(y2);
}

bool Life::isAlive() const
{
  if (this->_pv > 0)
    return (true);
  return (false);
}
