#include "Spawn.hh"
#include "Map.hh"

Spawn::Spawn(IslandGenerator &is, StringObject &object)
  : island(is), obj(object)
{
  this->tmpOfX = 0;

  this->setWidthWorms(island.getSizeX() / 200);
  this->setHeightWorms(this->widthWorms * 2);

  this->createNewObj();
  //this->changeTmpByWind();
}

Spawn::~Spawn()
{

}

unsigned int Spawn::getWidthWorms() const
{
  return (this->widthWorms);
}

unsigned int Spawn::getHeightWorms() const
{
  return (this->heightWorms);
}

void Spawn::setWidthWorms(unsigned int width)
{
  this->widthWorms = width;
  this->widthWorms = (this->widthWorms % 2 == 0) ? this->widthWorms + 1 : this->widthWorms;
}

void Spawn::setHeightWorms(unsigned int height)
{
  this->heightWorms = height;
}

IslandGenerator &Spawn::getIsland()
{
  return (this->island);
}
/*
void Spawn::changeTmpByWind()
{
  unsigned int i = 0;
  unsigned int j = 0;
  while (j < this->island.getSizeY())
  {
    i = 0;
    while (i < this->island.getSizeX())
    {
      if (this->island.getMap()[j][i] == TMP_TEAM_1
          || this->island.getMap()[j][i] == TMP_TEAM_2
          || this->island.getMap()[j][i] == TMP_TEAM_3
          || this->island.getMap()[j][i] == TMP_TEAM_4)
        this->island.change(i, j, WIND);
      ++i;
    }
    ++j;
  }
}*/

bool Spawn::testIsHeightOk(unsigned int x, unsigned int y) const
{
  unsigned int tmpLength = 0;

  --y;
  if (x < 1 || x >= this->island.getSizeX() - 1 || y >= this->island.getSizeY() - 1)
    return (false);
  while (y > 0)
  {
    if (this->island.isDestructible(this->island.getMap()[y][x]))
      break;
    ++tmpLength;
    --y;
  }
  if (y == 0) //if supérieur à la map, ok free
    return (true);
  if (tmpLength >= this->heightWorms)
    return (true);
  return (false);
}
/*
void Spawn::changeWindByTmp(unsigned int x, unsigned int y, unsigned int i)
{
  unsigned int mini = x - (this->widthWorms / 2);
  unsigned int maxi = x + (this->widthWorms / 2);
  unsigned int minj = y - this->heightWorms;
  unsigned int maxj = y;

  while (mini <= maxi)
  {
    minj = y - this->heightWorms;
    while (minj < maxj)
    {
      if (i == 0)
        this->island.change(mini, minj, TMP_TEAM_1);
      else if (i == 1)
        this->island.change(mini, minj, TMP_TEAM_2);
      else if (i == 2)
        this->island.change(mini, minj, TMP_TEAM_3);
      else if (i == 3)
        this->island.change(mini, minj, TMP_TEAM_4);
      ++minj;
    }
    ++mini;
  }
}*/

bool Spawn::testIfWormsTouch(unsigned int x, unsigned int y)
{
  unsigned int mini = x - (this->widthWorms / 2);
  unsigned int maxi = x + (this->widthWorms / 2);
  unsigned int minj = y - this->heightWorms;
  unsigned int maxj = y;

  while (mini <= maxi)
  {
    minj = y - this->heightWorms;
    while (minj < maxj)
    {
      if (this->island.isDestructible(this->island.getMap()[minj][mini])
          && this->island.getMap()[minj][mini] != POS_WORMS)
        return (false);
      ++minj;
    }
    ++mini;
  }
  //this->changeWindByTmp(x, y);
  return (true);
}

bool Spawn::testIsWidthOk(unsigned int x, unsigned int y)
{
  unsigned int tmpXmore = x;
  unsigned int tmpXless = x;

  while (std::abs((int)tmpXmore - (int)x) <= (int)(this->widthWorms / 2) + 1)
  {
    if(this->testIfWormsTouch(tmpXmore, y))
    {
      this->tmpOfX = tmpXmore - x;
      return (true);
    }
    if(this->testIfWormsTouch(tmpXless, y))
    {
      this->tmpOfX = tmpXless - x;
      return (true);
    }
    --tmpXless;
    ++tmpXmore;
  }
  return (false);
}

bool Spawn::testIfOk(unsigned int x, unsigned int y)
{
  if (y >= this->island.getSizeY() - 3
      || !this->testIsWidthOk(x, y))
    return (false);
  return (this->testIsHeightOk(x, y));
}

bool Spawn::testIfGravity(unsigned int x, unsigned int y)
{
  unsigned int j = y + 1;
  unsigned int cnt = 0;
  while (j < this->island.getSizeY())
  {
    if (this->island.isDestructible(this->island.getMapping(x, j)))
      break;
    ++cnt;
    ++j;
  }
  if (cnt >= MAX_GRAVITY_FALL)
    return (false);
  return (true);
}

void Spawn::createNewObj()
{
  unsigned int i = 0;
  unsigned int k = 0;
  bool first = false;
  while (i < this->obj.getListObject().size())
  {
    std::vector<unsigned int> tmpVec = this->obj.getListObject()[i];
    tmpVec.erase(tmpVec.begin(), tmpVec.begin() + 2);

    if (this->testIfOk(tmpVec[0], tmpVec[1]))
    {
      if (this->tmpOfX != 0)
      {
        tmpVec[0] += this->tmpOfX;
        if (std::abs((int)this->tmpOfX) >= (int)MIDDLE_FALL
            && !this->testIfGravity(tmpVec[0], tmpVec[1]))
        {
          ++i;
          continue;
        }
      }
      if (first)
      {
        unsigned int tmpSizeBetween = std::abs((int)this->previousVec[0] - (int)tmpVec[0]);
        //unsigned int tmpHeightBetween = std::abs((int)this->previousVec[1] - (int)tmpVec[1]);
        if (tmpSizeBetween < this->widthWorms * 2/* && tmpHeightBetween < this->heightWorms * 2*/)
        {

          //std::cout << this->previousVec[1] << ":" << tmpVec[1] << "," << tmpHeightBetween << std::endl;
          //exit(0);
          ++i;
          continue;
        }
      }
      this->newListObj.push_back(tmpVec);
      //unsigned int tmpX = this->newListObj[k][0];
      //unsigned int tmpY = this->newListObj[k][1];
      //TODO: enlever change après
      //this->island.change(tmpX, tmpY, POS_WORMS);
      this->previousVec = tmpVec;
      first = true;
      ++k;
    }
    ++i;
  }
}

std::vector<std::vector<unsigned int> > &Spawn::getListObj()
{
  return (this->newListObj);
}
