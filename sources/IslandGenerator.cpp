#include "IslandGenerator.hh"
#include "LineMaker.hh"
#include "template.hh"
#include "Grass.hh"
#include "MapOptimizor.hh"
#include "AddWater.hh"
#include "Hole.hh"

IslandGenerator::IslandGenerator()
  : Map()
{
  this->fmap.clear();
  this->fmap[ISLAND] = &IslandGenerator::makeIsland;
  this->fmap[PLANE] = &IslandGenerator::makePlane;
  this->fmap[SKYISLAND] = &IslandGenerator::makeSkyIsland;
  this->fmap[ANTHILL] = &IslandGenerator::makeAnthill;
  this->fmap[DEFAULT] = &IslandGenerator::makeIsland;
}

IslandGenerator::~IslandGenerator()
{

}

void IslandGenerator::makeSkyIsland()
{

}

void IslandGenerator::makeAnthill()
{

}

void IslandGenerator::makePlane()
{
  this->createEdge();
  if (!this->generate())
    return;

  Grass grass(*this);
  grass.findWhereToPutGrass();

  AddWater aw(this->getMap());
  aw.addWater();
}

void IslandGenerator::makeCoffe(const Coffe &coffe)
{
  Hole hole(this->miniMap);
  unsigned int i = 0;

  if (coffe == COFFE_ISLAND)
  {
    i = 0;
    unsigned int nbIsland = rand() % 4;
    while (i < nbIsland)
    {
      hole.drawHole((this->_sizeX / 20) + (rand() % (this->_sizeX - ((this->_sizeX / 20) * 2))),
      (this->_maxHeight) + rand() % (this->_sizeY - this->_maxHeight * 2),
      3 + (rand() % (this->_sizeY / 8)),
      this->typeOfSand, BROKEN);//BROKEN
      ++i;
    }
  }
  else if (coffe == COFFE_HOLE)
  {
    unsigned int nbHole = rand() % 4;
    i = 0;
    while (i < nbHole)
    {
      hole.drawHole(rand() % this->_sizeX,
      (this->_sizeY / 2) + (rand() % (this->_sizeY / 2)),
      4 + (rand() % (this->_sizeY / 8)),
      WIND, BROKEN);//BROKEN
      ++i;
    }
  }
}

void IslandGenerator::makeIsland()
{
  this->createEdge();
  if (!this->generate())
    return;

  this->makeCoffe(COFFE_HOLE);
  this->makeCoffe(COFFE_ISLAND);

  //MapOptimizor opti(this->getMap());
  //opti.optimise(0, this->getSizeX(), 0, this->getSizeY());
  Grass grass(*this);
  grass.findWhereToPutGrass();


  /*TODO: add water bubule fall down ?*/
  AddWater aw(this->getMap());
  aw.addWater();
}

void IslandGenerator::constructMap(unsigned int x, unsigned int y, TypeOfGenerator type)
{
  this->typeOfGenerator = type;

  if (!this->init(x, y))
    return;
  this->graph.clear();

  (this->*fmap[type])();
}

void IslandGenerator::createEdge()
{
  if (this->typeOfGenerator == ISLAND)
  {
    this->_minX = (_sizeX / 12) + std::rand() % (_sizeX / 10);
    this->_maxX = _sizeX - ((_sizeX / 12) + std::rand() % (_sizeX / 10));
    this->_peak = PEAK;
    this->_spaceBetweenGraph = ((this->_maxX - this->_minX) / this->_peak);
    this->_spaceChange = MAX_SPACE_BETWEEN_PEAK;
    this->typeOfSand = SAND;
    this->typeOfGrass = GRASS;
  }
  else if (this->typeOfGenerator == PLANE)
  {
    this->_minX = (_sizeX / 100) + std::rand() % (_sizeX / 100);
    this->_maxX = _sizeX - ((_sizeX / 100) + std::rand() % (_sizeX / 100));
    this->_peak = PEAK;
    this->_spaceBetweenGraph = ((this->_maxX - this->_minX) / this->_peak);
    this->_spaceChange = MAX_SPACE_BETWEEN_PEAK / 4;
    this->typeOfSand = SAND;
    this->typeOfGrass = GRASS_PLANE;
  }
  this->_maxHeight = (_sizeY / 5) + std::rand() % (_sizeY / 5);
}

bool IslandGenerator::isFlow()
{
  unsigned int i = 0;
  unsigned int cnt = 0;
  while (i < this->graph.size())
  {
    //std::cout << this->graph[i][1] << std::endl;
    if (this->graph[i][1] > ((int)_sizeY / 20) * 19)
      ++cnt;
    ++i;
  }
  if (cnt == this->graph.size() || this->getVolume(SAND) < 10)
  {
    std::cout << "on water !" << std::endl;

    this->constructMap(this->_sizeX, this->_sizeY, this->typeOfGenerator);
    return (false);
  }
  return (true);
}

bool IslandGenerator::generate()
{
  unsigned int i = 0;
  unsigned int current = 1;
  int previous = _sizeY - this->_maxHeight;
  //int previous = this->_maxHeight;
  int yy;
  int tmpLineX = this->_minX;
  int tmpLineY = _sizeY;
  while (i < _sizeX)
  {
    if (i < this->_minX || i > this->_maxX)
    {
      ++i;
      continue;
    }
    if (i == this->_minX + (this->_spaceBetweenGraph * (current))
        && current < this->_peak)
    {
      std::vector<int> tmp;
      tmp.push_back(i);//x
      do
      {
        yy = this->_maxHeight + (std::rand() % (_sizeY/* - this->_maxHeight*/));
        //std::cout << previous << "|"  << yy << std::endl;
      } while(std::abs(yy - previous) > ((int)this->_spaceChange));
      previous = yy;
      yy = (yy < 0) ? 0 : yy;
      yy = (yy >= (int)_sizeY) ? _sizeY - 1 : yy;
      tmp.push_back(yy);//y
      this->graph.push_back(tmp);
      fillY(i, this->_maxHeight, _sizeY, WIND);
      fillY(i, yy, _sizeY, SAND);
      LineMaker lm(tmpLineX, tmpLineY, i, yy);
      lm.makeLine(SAND, SMOOTH, this->miniMap, FILL, 1);
      tmpLineX = i;
      tmpLineY = yy;
      ++current;
    }
    else
      fillY(i, this->_maxHeight, _sizeY, WIND);
    ++i;
  }
  LineMaker lm2(tmpLineX, tmpLineY, this->_maxX, _sizeY);
  lm2.makeLine(SAND, SMOOTH, this->miniMap, FILL, 1);
  //makeLine(tmpLineX, tmpLineY, this->_maxX, _sizeY, SAND, SMOOTH);
  if (!this->isFlow())
    return (false);
  return (true);
}

const TypeOfGenerator &IslandGenerator::getGeneratorType() const
{
  return (this->typeOfGenerator);
}
