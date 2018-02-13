#include "Dynamit.hh"

Dynamit::Dynamit(int x, int y)
{
  this->XPos = x;
  this->YPos = y;
}

Dynamit::~Dynamit()
{

}

void Dynamit::fall(int fall)
{
  this->YPos += fall;
}
