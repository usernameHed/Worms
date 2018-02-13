#include "Grass.hh"

Grass::Grass(IslandGenerator &is)
  : island(is)
{

}

Grass::~Grass()
{

}

void Grass::addPoint(unsigned int x, unsigned int y, const WitchLine &type)
{
  if (type == START)
  {
    pt1.x = x;
    pt1.y = y;
  }
  else if (type == END)
  {
    pt2.x = x;
    pt2.y = y;
    this->addGrass(x, y);
  }
}

void Grass::findWhereToPutGrass()
{
  unsigned int i = 0;
  int j;
  bool ground;
  while (i < this->island.getMap()[0].size())
  {
    j = this->island.getMap().size() - 1;
    ground = false;
    Mapping tmpMapping;
    while (j >= 0)
    {
      if (this->island.isDestructible(this->island.getMap()[j][i]) && !ground) //if start object
      {
        tmpMapping = this->island.getMap()[j][i];
        this->addPoint(i, j, START);
        ground = true;
      }
      else if (!this->island.isDestructible(this->island.getMap()[j][i]) && ground) //if finish object
      {
        this->addPoint(i, j + 1, END);
        ground = false;
      }
      else if (this->island.isDestructible(this->island.getMap()[j][i]) && ground && this->island.getMap()[j][i] != tmpMapping)
      {
        //un object à commencé, mais un autre object commence
        this->addPoint(i, j + 1, END);//fini l'ancien
        this->addPoint(i, j, START);//commence le nouveau
        tmpMapping = this->island.getMap()[j][i];//set le nouveau tmpMapping
        //et ground est toujorus true !
      }
      --j;
    }
    if (ground) //si objet à commencé mais qu'on a fini...
      this->addPoint(i, 0, END);
    ++i;
  }
}

void Grass::choseType(unsigned int x, unsigned int y)
{
  if (this->island.getGeneratorType() == ISLAND)
    this->island.change(x, y, GRASS);
  else if (this->island.getGeneratorType() == PLANE)
    this->island.change(x, y, GRASS_PLANE);
}

void Grass::addGrass(unsigned int x, unsigned int y)
{
  Mapping mapping = this->island.getMap()[y][x];
  if (!this->island.isDestructible(mapping))
    return;
  unsigned int size = y;
  while (size < this->island.getSizeY())
  {
    if (this->island.getMap()[size][x] != mapping)
      break;
    size++;
  }
  unsigned int tmp = SIZE_GRASS;
  if (tmp > SIZEY_MAX_GRASS)
    tmp = SIZEY_MAX_GRASS;
  unsigned int tmpy = y;
  while (tmpy < y + tmp)
  {
    this->choseType(x, tmpy);
    tmpy++;
  }
}
