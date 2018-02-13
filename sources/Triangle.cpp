#include "Triangle.hh"
#include "template.hh"
#define _USE_MATH_DEFINES
#include <math.h>

Triangle::Triangle(std::vector<std::vector<Mapping> > &tmpMap)
  : Rasterization(tmpMap)
{
  this->opti = new MapOptimizor(tmpMap);
}

void Triangle::drawTriangle(unsigned int x1, unsigned int y1,
     unsigned int x2, unsigned int y2,
     unsigned int x3, unsigned int y3,
     const Mapping &mapping)
{
  Point2D pt1;
  Point2D pt2;
  Point2D pt3;
  pt1.x = x1;  pt1.y = y1;
  pt2.x = x2;  pt2.y = y2;
  pt3.x = x3;  pt3.y = y3;
  this->drawTri(pt1, pt2, pt3, tmpVectorMap, mapping);
  this->opti->optimise( min3(x1, x2, x3) - 10, max3(x1, x2, x3) + 10,
                        max3(y1, y2, y3) - 10, max3(y1, y2, y3) + 10);
}

Triangle::~Triangle()
{

}

int Triangle::orient2d(const Point2D& a, const Point2D& b, const Point2D& c)
{
  return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

void Triangle::drawTri(const Point2D& v0, const Point2D& v1, const Point2D& v2, std::vector<std::vector<Mapping> > &tmpVectorMap, const Mapping &mapping)
{
  int minX = min3(v0.x, v1.x, v2.x);
  int minY = min3(v0.y, v1.y, v2.y);
  int maxX = max3(v0.x, v1.x, v2.x);
  int maxY = max3(v0.y, v1.y, v2.y);

  minX = max(minX, 0);
  minY = max(minY, 0);
  maxX = min(maxX, (int)(this->tmpVectorMap[0].size() - 1));
  maxY = min(maxY, (int)(this->tmpVectorMap.size() - 1));

  Point2D p;
  for (p.y = minY; p.y <= maxY; p.y++)
  {
      for (p.x = minX; p.x <= maxX; p.x++)
      {
          int w0 = orient2d(v1, v2, p);
          int w1 = orient2d(v2, v0, p);
          int w2 = orient2d(v0, v1, p);
          if (w0 >= 0 && w1 >= 0 && w2 >= 0)
            change(p.x, p.y, mapping);
      }
  }
}
