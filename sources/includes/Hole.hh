#ifndef _HOLE_HH_
#define _HOLE_HH_

#include "Rasterization.hh"
#include "MapOptimizor.hh"

#define RAND_RQ2 (std::rand() % (1 + (rq * 2)))
//#define RAND_RQ2 (rq * 2)
#define RAND_RQ1_2 (std::rand() % (1 + (rq * 1)))
//#define RAND_RQ1_2 (rq * 1.2)
//#define RAND_RQ1_2 (rq * 0)

enum TypeHole
{
  PERFECT = 0,
  SINUSED = 1,
  BROKEN = 2,
};

class Hole : public Rasterization
{
private:
  std::vector<std::vector<int> > pts;
  MapOptimizor *opti;

  std::vector<int> testVector(std::vector<int> test);
  void drawHolePerfect(unsigned int x1, unsigned int y1, unsigned int r, const Mapping &mapping, const TypeHole &typeHole);
  void drawRipple(int x1, int y1, int r, const Mapping &mapping, const TypeHole &typeHole);

public:
  Hole(std::vector<std::vector<Mapping> > &tmpMap);
  ~Hole();

  void drawHole(unsigned int x1, unsigned int y1, unsigned int r, const Mapping &mapping, const TypeHole &typeHole);
};

#endif /* !LINE_HPP_ */
