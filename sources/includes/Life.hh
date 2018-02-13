#ifndef _LIFE_HH_
# define _LIFE_HH_

#include "Position.hh"
#include "vector"

class Life
{
public:
  int                         _pv;
private:
  Position                    _posLife;
  std::vector<int>   _slideLifePos;

public:
  Life(int pv = 100);
  virtual ~Life();

  int                       getPv() const;
  Position                  getPosLife() const;
  std::vector<int>          &getSlifeLifePos();

  void                      setPv(int pv);
  void                      setPosLife(int x, int y);
  void                      setSlideLifePos(int x1, int y1, int x2, int y2);

  bool                      isAlive() const;
};

#endif /* !LIFE_HH_ */
