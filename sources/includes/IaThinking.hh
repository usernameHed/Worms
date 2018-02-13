#ifndef _IATHINKING_HH_
#define _IATHINKING_HH_

#include <iostream>
#include        "AIExecute.hh"

class IaThinking
{
public:
  int numberOut = 0;
  int jumpFocus = 0;
  int jumpFocusMax = 4;
  int jumpHide = 0;
  int jumpHideMax = 2;
  int hideHoriz = 0;
  int maxHideDynamit = 50;
  int maxHide = 10;

  int jumpDebugFocus = 0;
  int jumpDebugFocusMax = 30;

  int angleTmpDrill = -420042;
  int paraTime = 0;
  int paraTimeMax = 100;

  void reset()
  {
    this->numberOut = 0;
    this->jumpFocus = 0;
    this->jumpHide = 0;
    this->hideHoriz = 0;
    this->jumpDebugFocus = 0;
    this->angleTmpDrill = -420042;
    this->paraTime = 0;
  }

private:
  LUARes                   iaMove;
  bool                     attack = false;

public:
    IaThinking();
    ~IaThinking();

    LUARes  getIaMove() const;
    void    setIaMove(LUARes move);

    bool getAttack() const;
    void setAttack(bool att);

};


#endif /* !_HH */
