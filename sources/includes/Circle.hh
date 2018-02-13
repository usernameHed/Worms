#ifndef _HOLE_HH_
#define _HOLE_HH_

#include "Rasterization.hh"

class Circle : public Rasterization
{
private:
  struct points
  {
    int		x_mid;
    int		y_mid;
    int		x;
    int		y;
    int		r;
    int		di;
  } pts;

public:
  Circle(std::vector<std::vector<Mapping> > &tmpMap);
  ~Circle();

  void drawCircle(unsigned int x1, unsigned int y1, unsigned int r, const Mapping &mapping);
  void drawCircle(unsigned int x1, unsigned int y1, unsigned int r, const Mapping &mapping, bool fill);
};

#endif /* !LINE_HPP_ */
