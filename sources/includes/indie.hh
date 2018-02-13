#ifndef __INDIE__
#define __INDIE__

#include <iostream>
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

const int DELAY_TIME = 3000;

enum ETimerAction
  {
    ETA_MOUSE_VISIBLE,
    ETA_MOUSE_INVISIBLE,
  };

struct TimerAction
{
  u32 TargetTime;
  ETimerAction Action;
};

struct SAppContext
{
  SAppContext()
    : Device(0), InfoStatic(0), EventBox(0)
  {}
  IrrlichtDevice * Device;
  gui::IGUIStaticText * InfoStatic;
  gui::IGUIListBox * EventBox;
};

class MyEventReceiver : public IEventReceiver
{
public:
  MyEventReceiver(SAppContext & context);
  virtual bool OnEvent(const SEvent& event);
private:
  SAppContext & Context;
};

#endif /* !INDIE_HH_ */
