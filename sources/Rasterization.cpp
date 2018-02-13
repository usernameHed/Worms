#include "Rasterization.hh"

Rasterization::Rasterization(std::vector<std::vector<Mapping> > &tmpMap)
  : tmpVectorMap(tmpMap)
{

}

Rasterization::~Rasterization()
{

}

Mapping Rasterization::getMapping(int x, int y)
{
  if (x < 0 || x >= this->getSizeX() || y < 0 || y >= this->getSizeY())
  {
    std::cout << "ERROR GET MAP OPTI" << std::endl;
    return (ERROR_MAP);
    //exit(0);
  }
  return (this->tmpVectorMap[y][x]);
}

int Rasterization::getSizeX() const
{
  if (this->tmpVectorMap.size() < 1)
    return (0);
  return (this->tmpVectorMap[0].size());
}

int Rasterization::getSizeY() const
{
  return (this->tmpVectorMap.size());
}

bool Rasterization::isDestructible(const Mapping &mapping) const
{
  if (mapping == SAND || mapping == GRASS || mapping == GRASS_PLANE)
    return (true);
  return (false);
}

void Rasterization::change(int x, int y, const Mapping &mapping)
{
  unsigned int xx = (x < 0) ? 0 : x;
  unsigned int yy = (y < 0) ? 0 : y;
  if (this->tmpVectorMap.size() < 1)
    return;
  if (xx >= this->tmpVectorMap[0].size())
    xx = this->tmpVectorMap[0].size() - 1;
  if (yy >= this->tmpVectorMap.size())
    yy = this->tmpVectorMap.size() - 1;
  tmpVectorMap[yy][xx] = mapping;
}

void Rasterization::fillY(int x, int startY, int endY, const Mapping &mapping)
{
  while(startY <= endY)
  {
    this->change(x, startY, mapping);
    ++startY;
  }
}
