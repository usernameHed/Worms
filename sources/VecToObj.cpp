#include "VecToObj.hh"
#include <vector>
#include <fstream>

VecToObj::VecToObj(std::vector<std::vector<Mapping> > &tmpVectorMap, const Mapping &mapping, std::string const &path)
{
  this->constructObj(tmpVectorMap, mapping, path);
}

VecToObj::~VecToObj()
{

}

void VecToObj::constructObj(std::vector<std::vector<Mapping>> &tmpVectorMap,
                  const Mapping &mapping, std::string const &path)
{
  (void)mapping;
  unsigned int i = 0, j = 0, count = 0;
  std::cout << tmpVectorMap.size() << ":" << tmpVectorMap[0].size() << std::endl;
  std::fstream file;
  file.open(path, std::fstream::out);

  file << "# Wavefront generate by WorldWideWorms's Team" << std::endl << std::endl;

  i = 0;
  while (i < tmpVectorMap[0].size())
  {
    j = tmpVectorMap.size();
    Mapping tmp = tmpVectorMap[j - 1][i];
    while (--j > 0)
    {
      if (tmpVectorMap[j][i] != tmp)
      {
        std::cout << "[" << i << ":" << j << "] changement d'état à:" << j << "de type:" << tmp << std::endl;
        file << "v " << j << " " << i << " " << 0 << std::endl;
        tmp = tmpVectorMap[j][i];
        count++;
      }
    }
    i++;
  }
  std::cout << "-----" << count << "-----" << std::endl;
  i = 0;
  while (i < tmpVectorMap[0].size())
  {
    j = tmpVectorMap.size();
    Mapping tmp2 = tmpVectorMap[j - 1][i];
    while (--j > 0)
    {
      if (tmpVectorMap[j][i] != tmp2)
      {
        std::cout << "[" << i << ":" << j << "] changement d'état à:" << j << " de type:" << tmp2 << std::endl;
        file << "v " << j << " " << i << " " << 40 << std::endl;
        tmp2 = tmpVectorMap[j][i];
      }
    }
    i++;
  }

  unsigned int bla = 1;
  std::cout << "??" << std::endl;
  while (bla < count)
  {
    file << "f " << bla + count << " " << bla + 1 + count << " " << bla + 1 << " " << bla << std::endl;
    bla++;
  }
  //file << "f " << 1 + count << " " << count * 2 << " " << count << " " << 1 << std::endl;
  file << "f " << 1 << " " << count << " " << count * 2 << " " << 1 + count << std::endl;

  unsigned int blo = 2;
  file << "f ";
  while (blo < count + 1)
  {
    file << blo << " ";
    blo++;
  }
  file << "1" << std::endl;

  blo = count * 2;
  file << "f ";
  while (blo > count)
  {
    file << blo << " ";
    blo--;
  }

  file.close();
}
