#ifndef _addWater_HH_
#define _addWater_HH_

#include "Rasterization.hh"
#include "IslandGenerator.hh"

class AddWater : public Rasterization
{
public:
  AddWater(std::vector<std::vector<Mapping> > &tmpMap);
  ~AddWater();

  void addWater();
};


#endif /* !addWater_HH_ */
