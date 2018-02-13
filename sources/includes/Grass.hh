#ifndef _GRASS_HH_
#define _GRASS_HH_

#include "Rasterization.hh"
#include "IslandGenerator.hh"

#define SIZE_GRASS ((size - y) / 5)
#define SIZEY_MAX_GRASS (this->island.getSizeY() / 30)

class Grass
{
private:
  enum WitchLine
  {
    START,
    END,
  };

  struct Point2D
  {
    unsigned int x, y;
  } pt1, pt2;

  IslandGenerator &island;

  void addPoint(unsigned int x, unsigned int y, const WitchLine &type);
  void addGrass(unsigned int x, unsigned int y);
  void choseType(unsigned int x, unsigned int y);

public:
  Grass(IslandGenerator &is);
  ~Grass();

  void findWhereToPutGrass();

};

#endif /* !GRASS_HH_ */
