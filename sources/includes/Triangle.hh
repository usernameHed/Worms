#ifndef _TRIANGLE_HH_
#define _TRIANGLE_HH_

#include "Rasterization.hh"
#include "MapOptimizor.hh"

class Triangle : public Rasterization
{
private:
  struct Point2D
  {
    int x, y;
  };
  MapOptimizor *opti;

  void drawTri(const Point2D &v0, const Point2D &v1, const Point2D &v2, std::vector<std::vector<Mapping> > &tmpVectorMap, const Mapping &mapping);
  int orient2d(const Point2D& a, const Point2D& b, const Point2D& c);

public:
  Triangle(std::vector<std::vector<Mapping> > &tmpMap);
  ~Triangle();

  void drawTriangle(unsigned int x1, unsigned int y1,
       unsigned int x2, unsigned int y2,
       unsigned int x3, unsigned int y3,
       const Mapping &mapping);
};

#endif /* !LINE_HPP_ */
