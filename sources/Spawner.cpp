#include "Spawner.hh"
#include "template.hh"

Spawner::Spawner(Spawn &spa, std::vector<Team> &tea)
  : spawn(spa), teams(tea)
{
  this->spawnTeam();
}

Spawner::~Spawner()
{

}

void Spawner::setPositionWorms(unsigned int idTeam, unsigned int idWorms, unsigned int x, unsigned int y)
{
  this->teams[idTeam].getWorms(idWorms).setPos(x, y);
}

void Spawner::setTallWorms(unsigned int idTeam, unsigned int idWorms)
{
  this->teams[idTeam].getWorms(idWorms).setWidth(this->spawn.getWidthWorms());
  this->teams[idTeam].getWorms(idWorms).setHeight(this->spawn.getHeightWorms());
}

void Spawner::setRotationWorms(unsigned int idTeam, unsigned int idWorms)
{
  unsigned int x = this->teams[idTeam].getWorms(idWorms).getPos().x;
  unsigned int y = this->teams[idTeam].getWorms(idWorms).getPos().y;

  unsigned int leftX = x - this->spawn.getWidthWorms() / 2;
  unsigned int rightX = x + this->spawn.getWidthWorms() / 2;
  unsigned int cntXLeft = 0;
  unsigned int cntXRight = 0;
  unsigned int j = y;
  while (j < this->spawn.getIsland().getSizeY())
  {
    if (this->spawn.getIsland().isDestructible(this->spawn.getIsland().getMapping(leftX, j)))
      break;
    ++cntXLeft;
    ++j;
  }
  j = y;
  while (j < this->spawn.getIsland().getSizeY())
  {
    if (this->spawn.getIsland().isDestructible(this->spawn.getIsland().getMapping(rightX, j)))
      break;
    ++cntXRight;
    ++j;
  }
  if (cntXLeft < cntXRight)
    this->teams[idTeam].getWorms(idWorms).setDirection(LEFT);
  else
    this->teams[idTeam].getWorms(idWorms).setDirection(RIGHT);
}

void Spawner::setLifePosition(unsigned int idTeam, unsigned int idWorms)
{
  this->teams[idTeam].getWorms(idWorms).lifePosition();
}

void Spawner::setLenghtX()
{
  if (this->sizeTeam != 0)
    this->lengthX = this->sizeObj / this->sizeTeam;
  else
    this->lengthX = 1;
}

void Spawner::spawnTeam()
{
  this->sizeTeam = this->teams.size();
  this->sizeObj = this->spawn.getListObj().size();
  this->setLenghtX();

  unsigned int i = 0;
  unsigned int j = 0;
  std::vector<unsigned int> tmpX;
  unsigned int tmpPosX = 0;
  while (i < this->sizeTeam)
  {
    this->startX = this->lengthX * i;

    j = 0;
    while (j < this->teams[i].getTeamNbWorms())
    {
      if (std::rand() % 4 < 3)
      {
        tmpPosX = (std::rand() % this->lengthX) * (i + 1);
        tmpX = this->spawn.getListObj()[tmpPosX];
        this->spawn.getListObj().erase (this->spawn.getListObj().begin() + (tmpPosX));
        --this->sizeObj;
        this->setLenghtX();
      }
      else
      {
        tmpPosX = (std::rand() % this->sizeObj);
        tmpX = this->spawn.getListObj()[tmpPosX];
        this->spawn.getListObj().erase (this->spawn.getListObj().begin() + (tmpPosX));
        --this->sizeObj;
        this->setLenghtX();
      }
      this->setTallWorms(i, j);
      this->setPositionWorms(i, j, tmpX[0], tmpX[1]);
      this->setRotationWorms(i, j);
      this->setLifePosition(i, j);
      ++j;
    }
    ++i;
  }
}
