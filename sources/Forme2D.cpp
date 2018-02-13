#include "Forme2D.hh"
#include "Line.hh"
#include "Triangle.hh"
#include "LineMaker.hh"
#define _USE_MATH_DEFINES
#include <math.h>

/*
std::vector<std::vector<int>> pts {
                                    { 0, 0 },
                                    { 300, 0 },
                                    { 350, 50 },
                                    { 320, 200 },
                                    { 100, 100 },
                                  };

*/
Forme2D::Forme2D(const std::vector<std::vector<int> > &pts,
    std::vector<std::vector<Mapping> > &tmpVectorMap, const Mapping &mapping,
    const TypeConstruct &type, const LineType &lineType, int sizeLine)
{
  (void)lineType;
  Triangle triangle(tmpVectorMap);
  unsigned int i = 0;
  while (++i < pts.size())
  {
    if (!pts[i].size())
      continue;

      LineMaker lm(pts[i - 1][0], pts[i - 1][1], pts[i][0], pts[i][1]);
      lm.makeLine(mapping, SMOOTHFORME, tmpVectorMap, NOFILL, sizeLine);

      if (i + 1 >= pts.size())
      {
        lm.changePx(pts[i][0], pts[i][1], pts[0][0], pts[0][1]);
        lm.makeLine(mapping, SMOOTHFORME, tmpVectorMap, NOFILL, sizeLine);
      }

    //Line line(pts[i - 1][0], pts[i - 1][1], pts[i][0], pts[i][1], tmpVectorMap, mapping, 1, NOFILL);
      //Line line(pts[i][0], pts[i][1], pts[0][0], pts[0][1], tmpVectorMap, mapping, 1, NOFILL);
    if (type == FILL)
    {
      if (!(i + 1 >= pts.size()))
        continue;
      int f = i + 1;
      while (--f > 1)
      {
        triangle.drawTriangle(pts[0][0], pts[0][1],
          pts[f - 1][0], pts[f - 1][1],
          pts[f][0], pts[f][1], mapping);
      }
    }
  }
}

Forme2D::~Forme2D()
{

}
