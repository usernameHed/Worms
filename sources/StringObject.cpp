#include "StringObject.hh"
#include "template.hh"

StringObject::StringObject()
{

}

StringObject::~StringObject()
{

}

void StringObject::addObject(IslandGenerator const &island)
{
  std::vector<unsigned int> tmp;
  tmp.push_back(pt1.x);
  tmp.push_back(pt1.y);
  tmp.push_back(pt2.x);
  tmp.push_back(pt2.y);

  tmp.push_back((int)island.getMapConst()[tmp[1]][tmp[0]]);
  listObject.push_back(tmp);
}

void StringObject::addPoint(unsigned int x, unsigned int y, const WitchLine &type, IslandGenerator const &island)
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
    this->addObject(island);
  }
}

void StringObject::makeStringObject(IslandGenerator const &island)
{
  unsigned int i = 0;
  int j;
  bool ground;
  this->listObject.clear();

  while (i < island.getMapConst()[0].size())
  {
    j = island.getMapConst().size() - 1;
    ground = false;
    Mapping tmpMapping;
    while (j >= 0)
    {
      if (island.isDestructible(island.getMapConst()[j][i]) && !ground) //if start object
      {
        tmpMapping = island.getMapConst()[j][i];
        this->addPoint(i, j, START, island);
        ground = true;
      }
      else if (!island.isDestructible(island.getMapConst()[j][i]) && ground) //if finish object
      {
        this->addPoint(i, j + 1, END, island);
        ground = false;
      }
      else if (island.isDestructible(island.getMapConst()[j][i]) && ground && island.getMapConst()[j][i] != tmpMapping)
      {
        //un object à commencé, mais un autre object commence
        this->addPoint(i, j + 1, END, island);//fini l'ancien
        this->addPoint(i, j, START, island);//commence le nouveau
        tmpMapping = island.getMapConst()[j][i];//set le nouveau tmpMapping
        //et ground est toujorus true !
      }
      --j;
    }
    if (ground) //si objet à commencé mais qu'on a fini...
      this->addPoint(i, 0, END, island);
    ++i;
  }
}

std::vector<std::vector<unsigned int> > const &StringObject::getListObject() const
{
  return (this->listObject);
}
