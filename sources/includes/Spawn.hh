#ifndef _SPAWN_HH_
#define _SPAWN_HH_

#include "StringObject.hh"
#include "IslandGenerator.hh"

#define MIDDLE_FALL (this->widthWorms / 2)
#define MAX_GRAVITY_FALL ((this->heightWorms / 2) + 1)

class Spawn
{
private:
  unsigned int widthWorms;
  unsigned int heightWorms;
  unsigned int tmpOfX;

  IslandGenerator &island;
  StringObject &obj;
  std::vector<unsigned int> previousVec;

  std::vector<std::vector<unsigned int> > newListObj;

public:
  Spawn(IslandGenerator &is, StringObject &obj);
  ~Spawn();

  void createNewObj();

  bool testIsHeightOk(unsigned int x, unsigned int y) const;
  bool testIfWormsTouch(unsigned int x, unsigned int y);
  bool testIsWidthOk(unsigned int x, unsigned int y);
  bool testIfGravity(unsigned int x, unsigned int y);
  bool testIfOk(unsigned int x, unsigned int y);

  //void changeWindByTmp(unsigned int x, unsigned int y, unsigned int i);
  //void changeTmpByWind();

  unsigned int getWidthWorms() const;
  unsigned int getHeightWorms() const;
  void setWidthWorms(unsigned int width);
  void setHeightWorms(unsigned int height);
  IslandGenerator &getIsland();

  std::vector<std::vector<unsigned int> > &getListObj();
};


#endif /* !SPAWN_HH_ */
