#ifndef _FORME2D_HH_
#define _FORME2D_HH_

#include <vector>
#include "Map.hh"

#define SMOOTHFORME (20)

class Forme2D
{
public:
  Forme2D(const std::vector<std::vector<int> > &pts,
      std::vector<std::vector<Mapping> > &tmpVectorMap, const Mapping &mapping,
      const TypeConstruct &type, const LineType &lineType, int sizeLine);
  ~Forme2D();
};

#endif /* !FORME2D_HH_ */
