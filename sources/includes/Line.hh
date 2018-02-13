#ifndef _LINE_HH_
#define _LINE_HH_

#include "Rasterization.hh"
#include "MapOptimizor.hh"

class Line : public Rasterization
{
private:
  int sign(int x) const;
  MapOptimizor *opti;

public:
  Line(std::vector<std::vector<Mapping> > &tmpMap);
  ~Line();

  void drawLine(int x1, int y1, int x2, int y2, unsigned int size, const Mapping &mapping, const TypeConstruct &type);
  void drawLine(int x1, int y1, int x2, int y2, const Mapping &mapping, const TypeConstruct &type);
};

#endif /* !LINE_HPP_ */
