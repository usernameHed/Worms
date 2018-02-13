#ifndef _MAPOPTIMIZOR_HH_
#define _MAPOPTIMIZOR_HH_

#include "Rasterization.hh"
#include "IslandGenerator.hh"

//#define MAX_ISLAND (10)
//#define MAX_ISLAND (1)
#define MAX_ISLAND (0.1)
#define MAX_RECURSIVE (600 * 200)

#define XY_NOT_OK (xmin > xmax || ymin > ymax)

class MapOptimizor : public Rasterization
{
private:
  int count;
  int total;
  bool stop = false;

  struct Edge
  {
    unsigned int xMin;
    unsigned int xMax;
    unsigned int yMin;
    unsigned int yMax;
  };

public:
  MapOptimizor(std::vector<std::vector<Mapping> > &tmpMap);
  ~MapOptimizor();

  bool isOpti(const Mapping &mapping) const;
  void changeDestructByOpti(unsigned int i, unsigned int j);
  void changeOptiByDestruct(unsigned int i, unsigned int j);

  void count_island(const Edge edge);
  void count_close(unsigned int i, unsigned int j, Edge const edge);
  void island_wind(unsigned int i, unsigned int j, Edge const edge);
  void changeOptiToMap(Edge const edge);

  void optimise(int xmin, int xmax, int ymin, int ymax);
};


#endif /* !MapOptimizor_HH_ */
