#include "Hole.hh"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Forme2D.hh"

Hole::Hole(std::vector<std::vector<Mapping> > &tmpMap)
  : Rasterization(tmpMap)
{
  this->opti = new MapOptimizor(tmpMap);
}

Hole::~Hole()
{

}

void Hole::drawHole(unsigned int x1, unsigned int y1, unsigned int r, const Mapping &mapping, const TypeHole &typeHole)
{
  if (typeHole == PERFECT || typeHole == SINUSED)
    this->drawHolePerfect(x1, y1, r, mapping, typeHole);
  else
    this->drawRipple(x1, y1, r, mapping, typeHole);
  //this->opti->optimise(x1 - (r * 2), x1 + (r * 2), y1 - (r * 2), y1 + (r * 2));
}

std::vector<int> Hole::testVector(std::vector<int> test)
{
  if (test[0] < 0)
    test[0] = 0;
  else if (test[0] >= (int)this->tmpVectorMap[0].size())
    test[0] = this->tmpVectorMap[0].size() - 1;

  if (test[1] < 0)
    test[1] = 0;
  else if (test[1] >= (int)this->tmpVectorMap.size())
    test[1] = this->tmpVectorMap.size() - 1;
  return (test);
}

void Hole::drawRipple(int x1, int y1, int r, const Mapping &mapping, const TypeHole &typeHole)
{
  (void)typeHole;
  this->pts.clear();

  int rq = (r / 4);
  int tmp, tmp2;
  std::vector<int> up       {  x1,                        (y1 - (rq * 3) - RAND_RQ2)  };
  tmp = RAND_RQ2; tmp2 = RAND_RQ1_2; std::vector<int> upRightBefore  {  (int)(x1 + rq + tmp2 + (tmp / 2)),  (int)(y1 - (rq * 2) - (tmp2 * 2) - tmp) };
  tmp = RAND_RQ2;  std::vector<int> upRight  {  x1 + (rq * 2) + tmp,  y1 - (rq * 2) - tmp  };
  tmp = RAND_RQ2; tmp2 = RAND_RQ1_2; std::vector<int> upRightAfter  {  (int)(x1 + (rq * 2) + tmp2 + tmp),  (int)(y1 - rq - (tmp2 * 2) - (tmp / 2)) };
  std::vector<int> right    {  x1 + (rq * 3) + RAND_RQ2,  y1                          };

  tmp = RAND_RQ2; tmp2 = RAND_RQ1_2; std::vector<int> downRightBefore  {  (int)(x1 + (rq * 2) + tmp2 + tmp),  (int)(y1 + rq + (tmp2 * 2) + (tmp / 2)) };
  tmp = RAND_RQ2;  std::vector<int> downRight  {  x1 + (rq * 2) + tmp,  y1 + (rq * 2) + tmp  };
  tmp = RAND_RQ2; tmp2 = RAND_RQ1_2; std::vector<int> downRightAfter  {  (int)(x1 + rq + tmp2 + (tmp / 2)),  (int)(y1 + (rq * 2) + (tmp2 * 2) + tmp) };
  std::vector<int> down     {  x1,                        y1 + (rq * 3) + RAND_RQ2    };


  tmp = RAND_RQ2; tmp2 = RAND_RQ1_2; std::vector<int> downLeftBefore  {  (int)(x1 - rq - tmp2 - (tmp / 2)),  (int)(y1 + (rq * 2) + (tmp2 * 2) + tmp) };
  tmp = RAND_RQ2;  std::vector<int> downLeft  {  x1 - (rq * 2) - tmp,  y1 + (rq * 2) + tmp  };
  tmp = RAND_RQ2; tmp2 = RAND_RQ1_2; std::vector<int> downLeftAfter  {  (int)(x1 - (rq * 2) - tmp2 - tmp),  (int)(y1 + rq + (tmp2 * 2) + (tmp / 2)) };
  std::vector<int> left     {  x1 - (rq * 3) - RAND_RQ2,  y1                          };

  tmp = RAND_RQ2; tmp2 = RAND_RQ1_2; std::vector<int> upLeftBefore  {  (int)(x1 - (rq * 2) - tmp2 - tmp),  (int)(y1 - rq - (tmp2 * 2) - (tmp / 2)) };
  tmp = RAND_RQ2;  std::vector<int> upLeft  {  x1 - (rq * 2) - tmp,  y1 - (rq * 2) - tmp  };
  tmp = RAND_RQ2; tmp2 = RAND_RQ1_2; std::vector<int> upLeftAfter  {  (int)(x1 - rq - tmp2 - (tmp / 2)),  (int)(y1 - (rq * 2) - (tmp2 * 2) - tmp) };

  this->pts.push_back(this->testVector(up));
  this->pts.push_back(this->testVector(upRightBefore));
  this->pts.push_back(this->testVector(upRight));
  this->pts.push_back(this->testVector(upRightAfter));
  this->pts.push_back(this->testVector(right));
  this->pts.push_back(this->testVector(downRightBefore));
  this->pts.push_back(this->testVector(downRight));
  this->pts.push_back(this->testVector(downRightAfter));
  this->pts.push_back(this->testVector(down));
  this->pts.push_back(this->testVector(downLeftBefore));
  this->pts.push_back(this->testVector(downLeft));
  this->pts.push_back(this->testVector(downLeftAfter));
  this->pts.push_back(this->testVector(left));
  this->pts.push_back(this->testVector(upLeftBefore));
  this->pts.push_back(this->testVector(upLeft));
  this->pts.push_back(this->testVector(upLeftAfter));
  Forme2D forme(pts, tmpVectorMap, mapping, FILL, LINEMAKE, 4);
}

void Hole::drawHolePerfect(unsigned int x1, unsigned int y1, unsigned int r, const Mapping &mapping, const TypeHole &typeHole)
{
  int rr = r;
  for(int y = -rr ; y <= rr ; y++)
    for(int x = -rr ; x <= rr ; x++)
    {
      if (x * x + y * y <= rr * rr && typeHole == PERFECT)
        this->change(x1 + x, y1 + y, mapping);
      else if (x * x + y * y <= rr * rr + (rr * 2 * sin(x * 0.9)) - (rr * 0.05 * sin(y * 0.02))
                && typeHole == SINUSED)
        this->change(x1 + x, y1 + y, mapping);
    }
}
