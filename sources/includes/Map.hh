#ifndef _MAP_HH_
# define _MAP_HH_

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>

#define SMOOTH (500)
#define SIZEX_1_P (tmpVectorMap[0].size() / 100)
#define SIZEY_1_P (tmpVectorMap.size() / 100)

#define XORSWAP(a, b)   ((&(a) == &(b)) ? (a) : ((a)^=(b),(b)^=(a),(a)^=(b)))
//#define PEAK (14 + std::rand() % 10) //PLUS DE SOMMET
//#define MAX_SPACE_BETWEEN_PEAK (this->_spaceBetweenGraph * 1) //PLUS HAUT
#define PEAK (14 + std::rand() % 10) //PLUS DE SOMMET
#define MAX_SPACE_BETWEEN_PEAK (this->_spaceBetweenGraph * 2) //PLUS HAUT
#define LIMIT_GROUND (10)

enum TypeOfGenerator
{
  ISLAND,
  PLANE,
  SKYISLAND,
  ANTHILL,
  DEFAULT,
};

enum Mapping
{
  ////////////////////////// indestructible
  WIND,
  WATER,
  ////////////////////////// destructible
  SAND,
  GRASS,
  GRASS_PLANE,
  ////////////////////////// other
  OPTI_SAND,
  OPTI_GRASS,
  OPTI_GRASS_PLANE,
  POS_WORMS,
  ERROR_MAP,
  ////////////////////////// tmpPLAYER
  TMP_TEAM_1,
  TMP_TEAM_2,
  TMP_TEAM_3,
  TMP_TEAM_4,
  SIZE_LIFE,
};

enum TypeConstruct
{
  FILL = 0,
  NOFILL = 1,
};

enum LineType
{
  LINENORMAL = 0,
  LINEMAKE = 1,
};

class Map
{
protected:

  unsigned int _sizeX = 0;
  unsigned int _sizeY = 0;
  unsigned int _minSizeX = 50;//200
  unsigned int _minSizeY = 50;
  unsigned int _maxSizeX = 2000;//200
  unsigned int _maxSizeY = 2000;

  std::vector<std::vector<Mapping> > miniMap;

public:
  Map ();
  virtual ~Map ();

  bool init(unsigned int x, unsigned int y);
  void aff() const;
  void change(int x, int y, const Mapping &mapping);
  void fillY(int x, int startY, int endY, const Mapping &mapping);
  std::vector<std::vector<Mapping> > &getMap();
  std::vector<std::vector<Mapping> > const &getMapConst() const;

  bool isDestructible(const Mapping &mapping) const;

  int getVolume(const Mapping &mapping) const;
  unsigned int getSizeX() const;
  unsigned int getSizeY() const;

  virtual const TypeOfGenerator &getGeneratorType() const = 0;
  virtual void constructMap(unsigned int x, unsigned int y, TypeOfGenerator typeOfGenerator) = 0;

  std::string convertMapToString() const;
  void swapMapValue(const Mapping &mapping1, const Mapping &mapping2);
  void saveMap(std::string const &fileName);
  void loadMap(std::string const &fileName);
  std::string openFiles(std::string const &fileName) const;

  Mapping getMapping(int x, int y);
};

#endif /* !MAP_HH_ */
