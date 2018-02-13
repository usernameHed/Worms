#ifndef __EVENT__
#define __EVENT__

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class           Event : public IEventReceiver
{
public:
  virtual bool  OnEvent(const SEvent& event)
  {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return (false);
  }

  virtual bool  IsKeyDown(EKEY_CODE keyCode) const
  {
    return KeyIsDown[keyCode];
  }
  Event()
  {
    for (u32 i=0; i < KEY_KEY_CODES_COUNT; ++i)
      KeyIsDown[i] = false;
  }
  virtual			~Event();
  int				SwitchPlayer(Event, int, int);
  int				changePos(Event);
  int				changePosTab(Event);
  int				changePosAttack(Event);
  int				changePosLeft(Event);
  int				changePosRight(Event);
  int				changePosUp(Event);
  int				changePosDown(Event);
  int				changePosMenu(Event);
  int				changePosMenuHome(Event);
  scene::IAnimatedMeshSceneNode	*ChangePos(Event, scene::IAnimatedMeshSceneNode*);
private:
  bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


#endif
