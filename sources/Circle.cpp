#include "Circle.hh"

Circle::Circle(std::vector<std::vector<Mapping> > &tmpMap)
  : Rasterization(tmpMap)
{

}


Circle::~Circle()
{

}

void Circle::drawCircle(unsigned int x1, unsigned int y1, unsigned int r, const Mapping &mapping, bool fill)
{
  if (fill)
  {
    unsigned int i = 0;
    change(x1, y1, mapping);
    while (++i < r)
      this->drawCircle(x1, y1, i, mapping);
  }
  else
    this->drawCircle(x1, y1, r, mapping);
}

void Circle::drawCircle(unsigned int x1, unsigned int y1, unsigned int r, const Mapping &mapping)
{
  pts.x_mid = x1;
  pts.y_mid = y1;
  pts.y = r;
  pts.x = 0;
  pts.r = r;
  pts.di = r - 1;
  while (pts.y >= pts.x)
  {
    change(pts.x_mid + pts.x, pts.y_mid + pts.y, mapping);
    change(pts.x_mid + pts.y, pts.y_mid + pts.x, mapping);
    change(pts.x_mid - pts.x, pts.y_mid + pts.y, mapping);
    change(pts.x_mid - pts.y, pts.y_mid + pts.x, mapping);
    change(pts.x_mid + pts.x, pts.y_mid - pts.y, mapping);
    change(pts.x_mid + pts.y, pts.y_mid - pts.x, mapping);
    change(pts.x_mid - pts.x, pts.y_mid - pts.y, mapping);
    change(pts.x_mid - pts.y, pts.y_mid - pts.x, mapping);
    if (pts.di >= (2 * pts.x))
    {
      pts.di = pts.di - (2 * pts.x) - 1;
      pts.x++;
    }
    else if (pts.di < 2 * (pts.r - pts.y))
    {
      pts.di =  pts.di + (2 * pts.y) - 1;
      pts.y--;
    }
    else
    {
      pts.di = pts.di + 2 * (pts.y - pts.x - 1);
      pts.y = pts.y - 1;
      pts.x = pts.x + 1;
    }
  }
}
