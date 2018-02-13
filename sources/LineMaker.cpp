#include "LineMaker.hh"
#include "Line.hh"
#define _USE_MATH_DEFINES
#include <math.h>

LineMaker::LineMaker()
{
  this->changePx(0, 0, 0, 0);
}

LineMaker::LineMaker(int x1, int y1, int x2, int y2)
{
  this->changePx(x1, y1, x2, y2);
}

LineMaker::~LineMaker()
{

}

void LineMaker::changePx(int x1, int y1, int x2, int y2)
{
  this->_px = {x1, y1, x2, y2};
}

void LineMaker::xorswap()
{
  if (this->pts._x1 > this->pts._x2)
  {
    XORSWAP(this->pts._x1, this->pts._x2);
    XORSWAP(this->pts._y1, this->pts._y2);
  }
}

bool LineMaker::makeLine(const Mapping &mapping, unsigned int repetition,
  std::vector<std::vector<Mapping> > &tmpVectorMap,
  const TypeConstruct &typeFill, int sizeLine)
{
  if (repetition <= 0)
    return (false);
  Line line(tmpVectorMap);

  this->pts._x1 = this->_px[0];  this->pts._y1 = this->_px[1];  this->pts._x2 = this->_px[2];  this->pts._y2 = this->_px[3];
  this->xorswap();
  this->pts._sizeXline = std::abs(this->pts._x1 - this->pts._x2);
  this->pts._sizeYline = std::abs(this->pts._y1 - this->pts._y2);

  if (this->pts._sizeXline < SIZEX_1_P
      || this->pts._sizeYline < SIZEY_1_P)
  {
    line.drawLine(this->pts._x1, this->pts._y1, this->pts._x2, this->pts._y2, sizeLine, mapping, typeFill);
    return (false);
  }
  this->pts._squareXline = ((this->pts._sizeXline / 4) != 0) ? (this->pts._sizeXline / 4) : 1;
  this->pts._squareYline = ((this->pts._sizeYline / 4) != 0) ? (this->pts._sizeYline / 4) : 1;
  bool parabole = (std::rand() % 2 == 1) ? true : false;
  if (parabole)
  {
    this->getFirstDown();
    this->getSecondUp();
  }
  else
  {
    this->getFirstUp();
    this->getSecondDown();
  }
  line.drawLine(this->pts._x1, this->pts._y1, this->pts._new_x1, this->pts._new_y1, sizeLine, mapping, typeFill);
  line.drawLine(this->pts._new_x1, this->pts._new_y1, this->pts._new_x2, this->pts._new_y2, sizeLine, mapping, typeFill);
  line.drawLine(this->pts._new_x2, this->pts._new_y2, this->pts._x2,     this->pts._y2, sizeLine, mapping, typeFill);

  if (repetition > 0)
  --repetition;

  this->changePx(this->pts._x1,     this->pts._y1,     this->pts._new_x1, this->pts._new_y1);
  if (!makeLine(mapping, repetition, tmpVectorMap, typeFill, sizeLine))
    return (false);
  this->changePx(this->pts._new_x1, this->pts._new_y1, this->pts._new_x2, this->pts._new_y2);
  if (!makeLine(mapping, repetition, tmpVectorMap, typeFill, sizeLine))
    return (false);
  this->changePx(this->pts._new_x2, this->pts._new_y2, this->pts._x2,     this->pts._y2);
  if (!makeLine(mapping, repetition, tmpVectorMap, typeFill, sizeLine))
    return (false);
  return (true);
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

void LineMaker::getFirstDown()
{
  if (this->pts._y2 < this->pts._y1)
  {
    this->pts._new_x1 = this->pts._x1 + this->pts._squareXline + (std::rand() % this->pts._squareXline) + 1;
    this->pts._new_y1 = this->pts._y2 + this->pts._squareYline * 3;
  }
  else
  {
    this->pts._new_x1 = this->pts._x1 + this->pts._squareXline;
    this->pts._new_y1 = this->pts._y1 + this->pts._squareYline + (std::rand() % this->pts._squareYline) + 1;
  }
}

void LineMaker::getFirstUp()
{
  if (this->pts._y2 < this->pts._y1)
  {
    this->pts._new_x1 = this->pts._x1 + this->pts._squareXline;
    this->pts._new_y1 = this->pts._y2 + (this->pts._squareYline * 2) + (std::rand() % this->pts._squareYline) + 1;
  }
  else
  {
    this->pts._new_x1 = this->pts._x1 + this->pts._squareXline + (std::rand() % this->pts._squareXline) + 1;
    this->pts._new_y1 = this->pts._y1 + this->pts._squareYline;
  }
}

void LineMaker::getSecondUp()
{
  if (this->pts._y2 < this->pts._y1)
  {
    this->pts._new_x2 = this->pts._x1 + (this->pts._squareXline * 2) + (std::rand() % this->pts._squareXline) + 1;
    this->pts._new_y2 = this->pts._y2 + this->pts._squareYline;
  }
  else
  {
    this->pts._new_x2 = this->pts._x1 + (this->pts._squareXline * 3);
    this->pts._new_y2 = this->pts._y1 + (this->pts._squareYline * 2) + (std::rand() % this->pts._squareYline) + 1;
  }
}

void LineMaker::getSecondDown()
{

  if (this->pts._y2 < this->pts._y1)
  {
    this->pts._new_x2 = this->pts._x1 + (this->pts._squareXline * 3);
    this->pts._new_y2 = this->pts._y2 + this->pts._squareYline + (std::rand() % this->pts._squareYline) + 1;
  }
  else
  {
    this->pts._new_x2 = this->pts._x1 + (this->pts._squareXline * 2) + (std::rand() % this->pts._squareXline) + 1;
    this->pts._new_y2 = this->pts._y1 + (this->pts._squareYline * 3);
  }
}
