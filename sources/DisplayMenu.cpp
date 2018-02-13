#include                "Display.hh"
#include                "Worms.hh"

void Display::affMenuPause(bool isOpened)
{
  if (isOpened)
    {
      core::rect<s32> menuPause = (core::rect<s32>(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y));
      hide = _env->addWindow(menuPause, true, L"");
      hide->getCloseButton()->setVisible(false);
      hide->setDraggable(false);
      hide->setDrawTitlebar(false);
      for (s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
	{
	  video::SColor col = _env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
	  col.setAlpha(-300);
	  _env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
	}
      this->hud = _env->addImage(_driver->getTexture("media/hud/hudlite.png"), position2d<int>(0, 0));
      this->affTime(currentTime);
      menu = _env->addImage(_driver->getTexture("media/pause/pause.png"), position2d<int>(WINDOW_SIZE_X / 4, WINDOW_SIZE_Y / 4));
      selected = _env->addImage(_driver->getTexture("media/pause/selected.png"), position2d<int>(WINDOW_SIZE_X / 4 + 16, WINDOW_SIZE_Y / 5.8));
    }
  else
    {
      hud->remove();
      hide->remove();
      menu->remove();
      selected->remove();
    }
  return;
}

void Display::onSpriteSwitch(int nbButton)
{
  if (nbButton == 0)
    selected->setRelativePosition(position2d<int>((WINDOW_SIZE_X / 4 + 16), WINDOW_SIZE_Y / 5.8));
  if (nbButton == 1)
    selected->setRelativePosition(position2d<int>(WINDOW_SIZE_X / 4 + 16, WINDOW_SIZE_Y / 5.8 * 1.67));
  if (nbButton == 2)
    selected->setRelativePosition(position2d<int>(WINDOW_SIZE_X / 4 + 16, WINDOW_SIZE_Y / 5.8 * 2.33));
  return;
}

//SAVE CODE
//= _driver->getTexture("media/button.jpg");
// core::rect<s32> menuPause = (core::rect<s32>((WINDOW_SIZE_X / 8), WINDOW_SIZE_Y / 6, (WINDOW_SIZE_X / 8) * 7, (WINDOW_SIZE_Y / 6) * 5.5));
// menu = _env->addWindow(menuPause, true, L"Menu");
// saveQuit = _env->addImage(_driver->getTexture("media/save.png"), position2d<int>(WINDOW_SIZE_X / 3, (WINDOW_SIZE_Y / 4) * 2));
// quit = _env->addImage(_driver->getTexture("media/quit.png"), position2d<int>(WINDOW_SIZE_X / 3, (WINDOW_SIZE_Y / 4) * 3));
// onSpriteSwitch(0);
// menu->getCloseButton()->setVisible(false);
// menu->setDraggable(false);
// menu->setDrawTitlebar(true);
//    quit->setImage(_driver->getTexture("media/quit.png"));
