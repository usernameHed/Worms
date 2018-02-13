//
// Cursor.hh for  in /home/rifki_i/rendu/cpp_indie_studio/sources
//
// Made by 
// Login   <@epitech.net>
// 
// Started on  Mon May  2 03:29:33 2016 
// Last update Tue May  3 04:29:40 2016 
//

#ifndef __CURSOR__
#define __CURSOR__

#include <iostream>
#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class MyEventReceiver : public IEventReceiver
{
public:
  struct SMouseState
  {
    core::position2di Position;
    bool LeftButtonDown;
    SMouseState() : LeftButtonDown(false) { }
  } MouseState;

  
  virtual bool OnEvent(const SEvent& event)
  {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return false;
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
      {
	switch(event.MouseInput.Event)
	  {
	  case EMIE_LMOUSE_PRESSED_DOWN:
	    MouseState.LeftButtonDown = true;
	    break;
	  case EMIE_LMOUSE_LEFT_UP:
	    MouseState.LeftButtonDown = false;
	    break;
	  case EMIE_MOUSE_MOVED:
	    MouseState.Position.X = event.MouseInput.X;
	    MouseState.Position.Y = event.MouseInput.Y;
	    break;
	  default:
	    break;
	  }
      }
    return false;
  }
  const SMouseState & GetMouseState(void) const
  {
    return MouseState;
  }
  virtual bool IsKeyDown(EKEY_CODE keyCode) const
  {
    //std::cout << KeyIsDown[keyCode] << std::endl;
    return KeyIsDown[keyCode];
  }
  MyEventReceiver()
  {
    for (u32 i=0; i < KEY_KEY_CODES_COUNT; ++i)
      KeyIsDown[i] = false;
  }
private:
  bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

#endif
