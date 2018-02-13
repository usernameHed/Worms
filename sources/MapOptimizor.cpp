#include "MapOptimizor.hh"
#include "Map.hh"

MapOptimizor::MapOptimizor(std::vector<std::vector<Mapping> > &tmpMap)
  : Rasterization(tmpMap)
{

}

MapOptimizor::~MapOptimizor()
{

}

void MapOptimizor::optimise(int xmin, int xmax, int ymin, int ymax)
{
  this->count = 0;
  this->total = this->getSizeY() * this->getSizeX();

  if (XY_NOT_OK)
    return;
  xmin = (xmin < 1) ? 0 : xmin;
  ymin = (ymin < 1) ? 0 : ymin;
  ymin = (ymin >= (int)this->getSizeY()) ? this->getSizeY() - 1 : ymin;
  ymax = (ymax >= (int)this->getSizeY()) ? this->getSizeY() - 1 : ymax;

  Edge edge;
  edge.xMin = xmin;
  edge.xMax = xmax - 1;
  edge.yMin = ymin;
  edge.yMax = ymax - 1;
  unsigned int tmpSiseX = xmax - xmin;
  unsigned int tmpSiseY = ymax - ymin;
  if (tmpSiseX * tmpSiseY <= MAX_RECURSIVE)
  {
    this->count_island(edge);
    this->changeOptiToMap(edge);
  }
  else
  {
    /*
    this->optimise(xmin, (xmin + tmpSiseX) / 2, ymin, (ymin + tmpSiseY) / 2);
    this->optimise((xmin + tmpSiseX) / 2, xmax, ymin, (ymin + tmpSiseY) / 2);
    this->optimise(xmin, (xmin + tmpSiseX) / 2, (ymin + tmpSiseY) / 2, ymax);
    this->optimise((xmin + tmpSiseX) / 2, xmax, (ymin + tmpSiseY) / 2, ymax);
    if (((tmpSiseX / 2) * (tmpSiseY / 2)) <= MAX_RECURSIVE)
    {
      this->optimise(xmin, xmin + (tmpSiseX / 3),                       ymin, ymin + (tmpSiseY / 3));
      this->optimise(xmin + (tmpSiseX / 3), xmin + (tmpSiseX / 3) * 2,  ymin, ymin + (tmpSiseY / 3));
      this->optimise(xmin + (tmpSiseX / 3) * 2, xmax,                   ymin, ymin + (tmpSiseY / 3));

      this->optimise(xmin, xmin + (tmpSiseX / 3),                       ymin + (tmpSiseY / 3), ymin + (tmpSiseY / 3) * 2);
      this->optimise(xmin + (tmpSiseX / 3), xmin + (tmpSiseX / 3) * 2,  ymin + (tmpSiseY / 3), ymin + (tmpSiseY / 3) * 2);
      this->optimise(xmin + (tmpSiseX / 3) * 2, xmax,                   ymin + (tmpSiseY / 3), ymin + (tmpSiseY / 3) * 2);

      this->optimise(xmin, xmin + (tmpSiseX / 3),                       ymin + (tmpSiseY / 3) * 2, ymin + (tmpSiseY / 3) * 3);
      this->optimise(xmin + (tmpSiseX / 3), xmin + (tmpSiseX / 3) * 2,  ymin + (tmpSiseY / 3) * 2, ymin + (tmpSiseY / 3) * 3);
      this->optimise(xmin + (tmpSiseX / 3) * 2, xmax,                   ymin + (tmpSiseY / 3) * 2, ymin + (tmpSiseY / 3) * 3);
    }
    */
  }
}


bool MapOptimizor::isOpti(const Mapping &mapping) const
{
  if (mapping == OPTI_SAND || mapping == OPTI_GRASS || mapping == OPTI_GRASS_PLANE)
    return (true);
  return (false);
}

void MapOptimizor::changeDestructByOpti(unsigned int i, unsigned int j)
{
  if (this->getMapping(i, j) == SAND)
    this->change(i, j, OPTI_SAND);
  if (this->getMapping(i, j) == GRASS)
    this->change(i, j, OPTI_GRASS);
  if (this->getMapping(i, j) == GRASS_PLANE)
    this->change(i, j, OPTI_GRASS_PLANE);
}

void MapOptimizor::changeOptiByDestruct(unsigned int i, unsigned int j)
{
  if (this->getMapping(i, j) == OPTI_SAND)
    this->change(i, j, SAND);
  if (this->getMapping(i, j) == OPTI_GRASS)
    this->change(i, j, GRASS);
  if (this->getMapping(i, j) == OPTI_GRASS_PLANE)
    this->change(i, j, GRASS_PLANE);
}

void MapOptimizor::count_close(unsigned int i, unsigned int j, const Edge edge)
{
  if (this->getMapping(i, j) == ERROR_MAP)
    return;
  this->changeDestructByOpti(i, j);
  ++this->count;
  if (j + 1 >= edge.yMax || j - 1 <= edge.yMin || i + 1 >= edge.xMax || i - 1 <= edge.xMin)
    this->stop = true;

  if (j + 1 < edge.yMax && this->isDestructible(this->getMapping(i, j + 1)))
    this->count_close(i, j + 1, edge);

  if (j > edge.yMin && this->isDestructible(this->getMapping(i, j - 1)))
    this->count_close(i, j - 1, edge);

  if (i > edge.xMin && this->isDestructible(this->getMapping(i - 1, j)))
    this->count_close(i - 1, j, edge);

  if (i + 1 < edge.xMax && this->isDestructible(this->getMapping(i + 1, j)))
    this->count_close(i + 1, j, edge);
}

void MapOptimizor::island_wind(unsigned int i, unsigned int j, const Edge edge)
{
  this->change(i, j, WIND);
  ++this->count;

  if (j + 1 < edge.yMax && this->isOpti(this->getMapping(i, j + 1)))
    this->island_wind(i, j + 1, edge);

  if (j > edge.yMin && this->isOpti(this->getMapping(i, j - 1)))
    this->island_wind(i, j - 1, edge);

  if (i > edge.xMin && this->isOpti(this->getMapping(i - 1, j)))
    this->island_wind(i - 1, j, edge);

  if (i + 1 < edge.xMax && this->isOpti(this->getMapping(i + 1, j)))
    this->island_wind(i + 1, j, edge);
}

void MapOptimizor::changeOptiToMap(const Edge edge)
{
  unsigned int i = 0;
  i = edge.xMin;
  unsigned int j = 0;
  j = edge.yMin;
  while(j < edge.yMax)
  {
    i = 0;
    i = edge.xMin;
    while (i < edge.xMax)
    {
      if (this->isOpti(this->getMapping(i, j)))
        this->changeOptiByDestruct(i, j);
      ++i;
    }
    ++j;
  }
}

void MapOptimizor::count_island(const Edge edge)
{
  unsigned int i = edge.xMin;
  unsigned int j = edge.yMin;
  while (j < edge.yMax)
  {
    i = edge.xMin;
    while (i < edge.xMax)
    {
      if (this->isDestructible(this->getMapping(i, j)))
      {
        this->count_close(i, j, edge);
        double tmp = ((double)this->count * 100.0) / (double)this->total;
        if (tmp < MAX_ISLAND && !stop)
          this->island_wind(i, j, edge);
        this->count = 0;
        stop = false;
      }
      ++i;
    }
    ++j;
  }
}
