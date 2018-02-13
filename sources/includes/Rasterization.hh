#ifndef _RASTERIZATION_HH_
#define _RASTERIZATION_HH_

#include <vector>
#include "Map.hh"

class Rasterization
{
protected:
  std::vector<std::vector<Mapping> > &tmpVectorMap;

public:
  Rasterization(std::vector<std::vector<Mapping> > &tmpMap);
  ~Rasterization();

  virtual int getSizeX() const;
  virtual int getSizeY() const;
  virtual bool isDestructible(const Mapping &mapping) const;
  virtual Mapping getMapping(int x, int y);
  virtual void change(int x, int y, const Mapping &mapping);
  virtual void fillY(int x, int startY, int endY, const Mapping &mapping);
};


#endif /* !RASTERIZATION_HH_ */
