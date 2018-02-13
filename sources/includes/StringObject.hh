#ifndef _STRINGOBJECT_HH_
#define _STRINGOBJECT_HH_

#include "IslandGenerator.hh"

class StringObject
{
private:
  enum WitchLine
  {
    START,
    END,
  };

  struct Point2D
  {
    unsigned int x, y;
  } pt1, pt2;

  std::vector<std::vector<unsigned int> > listObject;

public:
  StringObject();
  ~StringObject();

  void makeStringObject(IslandGenerator const &is);
  void addPoint(unsigned int x, unsigned int y, const WitchLine &type, IslandGenerator const &island);
  void addObject(IslandGenerator const &island);
  std::vector<std::vector<unsigned int> > const &getListObject() const;
};

#endif /* !STRINGOBJECT_HH_ */
