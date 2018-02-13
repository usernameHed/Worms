#include "Line.hh"
#define _USE_MATH_DEFINES
#include <math.h>

Line::Line(std::vector<std::vector<Mapping> > &tmpMap)
  : Rasterization(tmpMap)
{
  this->opti = new MapOptimizor(tmpMap);
}

Line::~Line()
{

}

void Line::drawLine(int x1, int y1, int x2, int y2, unsigned int size, const Mapping &mapping, const TypeConstruct &type)
{
  int rr = size / 2;
  for(int y = -rr ; y <= rr ; y++)
    for(int x = -rr ; x <= rr ; x++)
      if(x * x + y * y <= rr * rr)
        this->drawLine(x1 + x, y1 + y, x2 + x, y2 + y, mapping, type);
  this->opti->optimise(x1 - (size * 2), x2 + (size * 2), y1 - (size * 2), y2 + (size * 2));
}

void Line::drawLine(int x1, int y1, int x2, int y2, const Mapping &mapping, const TypeConstruct &type)
{
  int x = x2;
  int y = y2;
  int dy = y2 - y1;
  int dx = x2 - x1;

  if (std::abs(dy) > std::abs(dx))
  {
    for(y = y1; y != y2; y += this->sign(dy))
    {
      x = x1 + ( y - y1 ) * dx / dy;
      if (type == FILL)
        this->fillY(x, y, tmpVectorMap.size(), mapping);
      else if (type == NOFILL)
        this->change(x, y, mapping);
    }
  }
  else
  {
    for( x = x1; x != x2; x += this->sign(dx))
    {
      y = y1 + ( x - x1 ) * dy / dx;
      if (type == FILL)
        this->fillY(x, y, tmpVectorMap.size(), mapping);
      else if (type == NOFILL)
        this->change(x, y, mapping);
    }
  }
  if (type == FILL)
    this->fillY(x2, y2, tmpVectorMap.size(), mapping);
  else if (type == NOFILL)
    this->change(x2, y2, mapping);
}

int Line::sign(int x) const
{
  if (x < 0)
    return (-1);
  return 1;
}
