#include "AddWater.hh"

AddWater::AddWater(std::vector<std::vector<Mapping> > &tmpMap)
  : Rasterization(tmpMap)
{

}

AddWater::~AddWater()
{

}

void AddWater::addWater()
{
  unsigned int i = 0;
  while (i < this->tmpVectorMap[0].size())
  {
    this->change(i, this->tmpVectorMap.size() - 1, WATER);
    this->change(i, this->tmpVectorMap.size() - 2, WATER);
    i++;
  }
}
