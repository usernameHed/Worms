#include "Map.hh"
#include "template.hh"
#include <fstream>
#include <string>
#include <string>
#include "Cryptor.hh"

Map::Map()
{
  this->_minSizeX = 50;//200
  this->_minSizeY = 50;
  this->_maxSizeX = 2000;//200
  this->_maxSizeY = 2000;
}

Map::~Map()
{

}

bool Map::init(unsigned int x, unsigned int y)
{
  if (x < this->_minSizeX || y < this->_minSizeY
    || x > this->_maxSizeX || y > this->_maxSizeY)
  {
    std::cerr << "size of map incorrect" << std::endl;
    x = 1920;
    y = 1080;
  }
  this->_sizeX = (x % 2 == 0) ? x : x + 1;
  this->_sizeY = (y % 2 == 0) ? y : y + 1;

  unsigned int i = 0;
  unsigned int j = 0;

  this->miniMap.clear();
  std::vector<Mapping> tmpX;
  while(j < this->_sizeY)
  {
    tmpX.clear();
    i = 0;
    while (i < this->_sizeX)
    {
      tmpX.push_back(WIND);
      ++i;
    }
    this->miniMap.push_back(tmpX);
    ++j;
  }
  return (true);
}

void Map::aff() const
{
  unsigned int i = 0;
  unsigned int j = 0;
  while(j < this->_sizeY)
  {
    i = 0;
    while (i < this->_sizeX)
    {
      if (
          (j == 0 && i == 0) || (j == this->_sizeY - 1 && i == this->_sizeX - 1)
          || (j == 0 && i == this->_sizeX - 1) || (i == 0 && j == this->_sizeY - 1) )
        std::cout << "+";
      else if (j == 0)// || j == this->_sizeY - 1)
        std::cout << "—";
      else if (i == 0 || i == this->_sizeX - 1)
        std::cout << "|";
      else if (this->miniMap[j][i] == WIND)
        std::cout << " ";
      else if (this->miniMap[j][i] == GRASS)
        std::cout << "œ";
      else if (this->miniMap[j][i] == GRASS_PLANE)
        std::cout << "%";
      else if (this->miniMap[j][i] == WATER)
        std::cout << "~";
      else if (this->miniMap[j][i] == POS_WORMS)
        std::cout << "-";
      else if (this->miniMap[j][i] == TMP_TEAM_1)
        std::cout << "a";
      else if (this->miniMap[j][i] == TMP_TEAM_2)
        std::cout << "b";
      else if (this->miniMap[j][i] == TMP_TEAM_3)
        std::cout << "c";
      else if (this->miniMap[j][i] == TMP_TEAM_4)
        std::cout << "d";
      else if (this->miniMap[j][i] == SIZE_LIFE)
        std::cout << "#";
      else
        std::cout << this->miniMap[j][i];
      ++i;
    }
    std::cout << std::endl;
    ++j;
  }
}

void Map::swapMapValue(const Mapping &mapping1, const Mapping &mapping2)
{
  unsigned int i = 0;
  unsigned int j = 0;
  while(j < this->_sizeY)
  {
    i = 0;
    while (++i < this->_sizeX)
    {
      if (this->miniMap[j][i] == mapping1)
        this->miniMap[j][i] = mapping2;
      ++i;
    }
    ++j;
  }
}

Mapping Map::getMapping(int x, int y)
{
  if (x < 0 || x >= (int)this->getSizeX() || y < 0 || y >= (int)this->getSizeY())
  {
    std::cout << "ERROR GET MAP OPTI" << std::endl;
    return (ERROR_MAP);
    //exit(0);
  }
  return (this->miniMap[y][x]);
}

bool Map::isDestructible(const Mapping &mapping) const
{
  if (mapping == SAND || mapping == GRASS || mapping == GRASS_PLANE)
    return (true);
  return (false);
}

void Map::change(int x, int y, const Mapping &mapping)
{
  unsigned int xx = (x < 0) ? 0 : x;
  unsigned int yy = (y < 0) ? 0 : y;
  if (xx >= this->_sizeX)
    xx = this->_sizeX - 1;
  if (yy >= this->_sizeY)
    yy = this->_sizeY - 1;
  this->miniMap[yy][xx] = mapping;
}

void Map::fillY(int x, int startY, int endY, const Mapping &mapping)
{
  while(startY <= endY)
  {
    this->change(x, startY, mapping);
    ++startY;
  }
}

unsigned int Map::getSizeX() const
{
  return (this->_sizeX);
}

unsigned int Map::getSizeY() const
{
  return (this->_sizeY);
}

int Map::getVolume(const Mapping &mapping) const
{
  unsigned int i = 0;
  unsigned int j = 0;
  int other = 0;
  int current = 0;
  while(j < this->_sizeY)
  {
    i = 0;
    while (i < this->_sizeX)
    {
      if (this->miniMap[j][i] == mapping)
        ++current;
      else
        ++other;
      ++i;
    }
    ++j;
  }
  return ((current * 100) / (current + other));
}

std::vector<std::vector<Mapping> > &Map::getMap()
{
  return (this->miniMap);
}

std::vector<std::vector<Mapping> > const &Map::getMapConst() const
{
  return (this->miniMap);
}

std::string Map::convertMapToString() const
{
  std::string tmp = "";
  unsigned int i = 0;
  while (i < this->miniMap.size())
  {
    std::ostringstream oss;
    if (!this->miniMap[i].empty())
    {
      std::copy(this->miniMap[i].begin(), this->miniMap[i].end()-1, std::ostream_iterator<int>(oss, " "));
      oss << this->miniMap[i].back();
    }
    std::string line = oss.str() + "\n";
    tmp += line;
    i++;
  }
  return (tmp);
}

void Map::loadMap(const std::string &fileName)
{
  this->miniMap.clear();
  std::string fileString = this->openFiles(fileName);
  Cryptor cry(fileString, UNCRYPT);
  //Zipper zip(fileString, UNZIP);
  this->_sizeX = 0;
  this->_sizeY = 0;
  bool ok = true;
  std::string tmpNumber = "";
  std::vector<Mapping> lineMap;
  unsigned int kk = 0;

  while (kk < fileString.size())
  {
    if (fileString[kk] == '\n')
    {
      if (tmpNumber.size() > 0)
      {
        if (ok)
          this->_sizeX += 1;
        lineMap.push_back((Mapping)std::atoi(tmpNumber.c_str()));
      }
      ++this->_sizeY;
      this->miniMap.push_back(lineMap);
      lineMap.clear();
      ok = false;
    }
    else if ((fileString[kk] >= '0' && fileString[kk] <= '9') || fileString[kk] == '-')
      tmpNumber += fileString[kk];
    else
    {
      if (tmpNumber.size() > 0)
      {
        if (ok)
          this->_sizeX += 1;
        lineMap.push_back((Mapping)std::atoi(tmpNumber.c_str()));
      }
      tmpNumber = "";
    }
    ++kk;
  }
}

void Map::saveMap(const std::string &fileName)
{
  std::string fileString = this->convertMapToString();
  //Zipper zip(fileString, ZIP);
  Cryptor cry(fileString, CRYPT);

  std::ofstream myfile;
  myfile.open (fileName);
  myfile << fileString;
  myfile.close();
}

std::string Map::openFiles(std::string const &fileName) const
{
  std::ifstream input(fileName.c_str());
  std::stringstream sstr;
  while(input >> sstr.rdbuf());
  return (sstr.str());
}
