#ifndef _VecToObj_HH_
#define _VecToObj_HH_

#include "Map.hh"

class VecToObj
{
protected:

public:
  VecToObj(std::vector<std::vector<Mapping> > &tmpVectorMap, const Mapping &mapping, std::string const &path);
  ~VecToObj();

  void constructObj(std::vector<std::vector<Mapping> > &tmpVectorMap,
                    const Mapping &mapping, std::string const &path);
};


#endif /* !VecToObj_HH_ */
