#ifndef _LINEMAKER_HH_
#define _LINEMAKER_HH_

#include "Map.hh"

#define XORSWAP(a, b)   ((&(a) == &(b)) ? (a) : ((a)^=(b),(b)^=(a),(a)^=(b)))

class LineMaker
{
private:
  struct points
  {
    int _new_x1;
    int _new_y1;
    int _new_x2;
    int _new_y2;
    unsigned int _sizeXline;
    unsigned int _sizeYline;
    int _squareXline;
    int _squareYline;
    int _x1;
    int _y1;
    int _x2;
    int _y2;
  } pts;

  std::vector<int> _px;

public:
  LineMaker();
  LineMaker(int x1, int y1, int x2, int y2);
  ~LineMaker();

  void changePx(int x1, int y1, int x2, int y2);
  //template <class T>
  bool makeLine(const Mapping &mapping, unsigned int repetition,
      std::vector<std::vector<Mapping> > &tmpVectorMap,
      const TypeConstruct &type, int sizeLine);

  void xorswap();
  void getFirstUp();
  void getFirstDown();
  void getSecondUp();
  void getSecondDown();
};


#endif /* !linemaker_HH_ */
