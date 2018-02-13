#ifndef _ISLANDGENERATOR_HH_
# define _ISLANDGENERATOR_HH_

#include "Map.hh"
#include <cstdlib>
#include <climits>
#define _USE_MATH_DEFINES
#include <math.h>
#include <map>

enum Coffe
{
  COFFE_ISLAND = 0,
  COFFE_HOLE = 1,
};

class IslandGenerator : public Map
{
private:
  unsigned int _minX;
  unsigned int _maxX;
  unsigned int _maxHeight;
  unsigned int _peak;
  unsigned int _spaceBetweenGraph;
  unsigned int _spaceChange;
  std::vector<std::vector<int> > graph;

  TypeOfGenerator typeOfGenerator;
  Mapping typeOfSand;
  Mapping typeOfGrass;

  typedef void (IslandGenerator::*MFP)();
  std::map <TypeOfGenerator, MFP> fmap;

public:
  IslandGenerator ();
  IslandGenerator (IslandGenerator &other);
  virtual ~IslandGenerator ();

  void createEdge();
  bool generate();
  bool isFlow();

  void makeCoffe(const Coffe &coffe);
  void makeIsland();
  void makePlane();
  void makeSkyIsland();
  void makeAnthill();

  virtual void constructMap(unsigned int x, unsigned int y, TypeOfGenerator typeOfGenerator);
  virtual const TypeOfGenerator &getGeneratorType() const;
};

#endif /* !ISLANDGENERATOR_HH_ */
