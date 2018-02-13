#include "EventHandler.hh"
#include "Display.hh"
#include <iostream>

Event::~Event()
{

}

int	Event::changePosTab(Event event)
{
  static bool      isPressedTab = false;

  if (isPressedTab == true)
  {
    if (!event.IsKeyDown(irr::KEY_TAB))
      isPressedTab = false;
  }
  else if (isPressedTab == false && event.IsKeyDown(KEY_TAB))
  {
    isPressedTab = true;
    return (7);
  }
  return (0);
}

int	Event::changePosAttack(Event event)
{
  static bool      isPressedAttack = false;

  if (isPressedAttack == true)
  {
    if (!event.IsKeyDown(irr::KEY_KEY_E))
      isPressedAttack = false;
  }
  else if (isPressedAttack == false && event.IsKeyDown(KEY_KEY_E))
  {
    isPressedAttack = true;
    return (9);
  }
  return (0);
}

int Event::changePosRight(Event event)
{
  static bool      isPressedRight = false;

  if (isPressedRight == true)
  {
    //if (!(event.IsKeyDown(irr::KEY_KEY_D) || event.IsKeyDown(irr::KEY_RIGHT)))
    if (!((event.IsKeyDown(irr::KEY_KEY_D) || event.IsKeyDown(irr::KEY_RIGHT))
        && !(event.IsKeyDown(irr::KEY_KEY_Q) || event.IsKeyDown(irr::KEY_LEFT))))
      isPressedRight = false;
  }
  else if (isPressedRight == false
    && //(event.IsKeyDown(irr::KEY_KEY_D) || event.IsKeyDown(irr::KEY_RIGHT)))
    ((event.IsKeyDown(irr::KEY_KEY_D) || event.IsKeyDown(irr::KEY_RIGHT))
        && !(event.IsKeyDown(irr::KEY_KEY_Q) || event.IsKeyDown(irr::KEY_LEFT)))
      )
  {
    isPressedRight = true;
    return (1);
  }
  return (0);
}

int Event::changePosLeft(Event event)
{
  static bool      isPressedLeft = false;

  if (isPressedLeft == true)
  {
    if (!(((event.IsKeyDown(irr::KEY_KEY_Q) || event.IsKeyDown(irr::KEY_LEFT))
        && !(event.IsKeyDown(irr::KEY_KEY_D) || event.IsKeyDown(irr::KEY_RIGHT) ))))
      isPressedLeft = false;
  }
  else if (isPressedLeft == false
    &&
    (((event.IsKeyDown(irr::KEY_KEY_Q) || event.IsKeyDown(irr::KEY_LEFT))
        && !(event.IsKeyDown(irr::KEY_KEY_D) || event.IsKeyDown(irr::KEY_RIGHT) )))
  )
  {
    isPressedLeft = true;
    return (2);
  }
  return (0);
}

int Event::changePosUp(Event event)
{
  static bool      isPressedUp = false;

  if (isPressedUp == true)
  {
    //if (!(event.IsKeyDown(irr::KEY_KEY_D) || event.IsKeyDown(irr::KEY_RIGHT)))
    if (!((event.IsKeyDown(irr::KEY_KEY_Z) || event.IsKeyDown(irr::KEY_UP))
        && !(event.IsKeyDown(irr::KEY_KEY_S) || event.IsKeyDown(irr::KEY_DOWN))))
      isPressedUp = false;
  }
  else if (isPressedUp == false
    && //(event.IsKeyDown(irr::KEY_KEY_D) || event.IsKeyDown(irr::KEY_RIGHT)))
    ((event.IsKeyDown(irr::KEY_KEY_Z) || event.IsKeyDown(irr::KEY_UP))
        && !(event.IsKeyDown(irr::KEY_KEY_S) || event.IsKeyDown(irr::KEY_DOWN)))
      )
  {
    isPressedUp = true;
    return (11);
  }
  return (0);
}

int Event::changePosDown(Event event)
{
  static bool      isPressedDown = false;

  if (isPressedDown == true)
  {
    if (!(((event.IsKeyDown(irr::KEY_KEY_S) || event.IsKeyDown(irr::KEY_DOWN))
        && !(event.IsKeyDown(irr::KEY_KEY_Z) || event.IsKeyDown(irr::KEY_UP) ))))
      isPressedDown = false;
  }
  else if (isPressedDown == false
    &&
    (((event.IsKeyDown(irr::KEY_KEY_S) || event.IsKeyDown(irr::KEY_DOWN))
        && !(event.IsKeyDown(irr::KEY_KEY_Z) || event.IsKeyDown(irr::KEY_UP) )))
  )
  {
    isPressedDown = true;
    return (12);
  }
  return (0);
}

int Event::changePosMenuHome(Event event)
{
  static bool      isPressedMenu = false;
  static bool      isPressedMenu2 = false;
  static bool      isPressedMenu3 = false;
  static bool      isPressedMenu4 = false;
  static bool      isPressedMenu5 = false;
  static bool      isPressedMenu6 = false;
  static bool      isPressedMenu7 = false;
  static bool      isPressedMenu8 = false;

  if (isPressedMenu == true)
    {
      if (!event.IsKeyDown(irr::KEY_DOWN))
	isPressedMenu = false;
    }
  else if (isPressedMenu == false && event.IsKeyDown(KEY_DOWN))
    {
      isPressedMenu = true;
      return (DOWN_MENU);
    }

  if (isPressedMenu2 == true)
    {
      if (!event.IsKeyDown(irr::KEY_UP))
  	isPressedMenu2 = false;
    }
  else if (isPressedMenu2 == false && event.IsKeyDown(KEY_UP))
    {
      isPressedMenu2 = true;
      return (UP_MENU);
    }

    if (isPressedMenu3 == true)
    {
      if (!event.IsKeyDown(irr::KEY_RETURN))
  	isPressedMenu3 = false;
    }
    else if (isPressedMenu3 == false && event.IsKeyDown(KEY_RETURN))
      {
	isPressedMenu3 = true;
	return (ENTER);
      }

    if (isPressedMenu4 == true)
    {
      if (!event.IsKeyDown(irr::KEY_KEY_M))
  	isPressedMenu4 = false;
    }
    else if (isPressedMenu4 == false && event.IsKeyDown(KEY_KEY_M))
      {
	isPressedMenu4 = true;
	return (MUTE);
      }

    if (isPressedMenu5 == true)
    {
      if (!event.IsKeyDown(irr::KEY_TAB))
  	isPressedMenu5 = false;
    }
    else if (isPressedMenu5 == false && event.IsKeyDown(KEY_TAB))
      {
	isPressedMenu5 = true;
	return (INVENTORY);
      }

    if (isPressedMenu6 == true)
      {
	if (!event.IsKeyDown(irr::KEY_LEFT))
	  isPressedMenu6 = false;
      }
    else if (isPressedMenu6 == false && event.IsKeyDown(KEY_LEFT))
      {
	isPressedMenu6 = true;
	return (LEFT_WORMS);
      }

    if (isPressedMenu7 == true)
      {
	if (!event.IsKeyDown(irr::KEY_RIGHT))
	  isPressedMenu7 = false;
      }
    else if (isPressedMenu7 == false && event.IsKeyDown(KEY_RIGHT))
      {
	isPressedMenu7 = true;
	return (RIGHT_WORMS);
      }

    if (isPressedMenu8 == true)
      {
	if (!event.IsKeyDown(irr::KEY_ESCAPE))
	  isPressedMenu8 = false;
      }
    else if (isPressedMenu8 == false && event.IsKeyDown(KEY_ESCAPE))
      {
	isPressedMenu8 = true;
	return (ESCAPE);
      }
}

int Event::changePosMenu(Event event)
{
  static bool      isPressedMenu = false;

  if (isPressedMenu == true)
  {
    if (!event.IsKeyDown(irr::KEY_ESCAPE))
      isPressedMenu = false;
  }
  else if (isPressedMenu == false && event.IsKeyDown(KEY_ESCAPE))
  {
    isPressedMenu = true;
    return (10);
  }
  return (0);
}

int	Event::changePos(Event event)
{
  if ((event.IsKeyDown(irr::KEY_KEY_D) || event.IsKeyDown(irr::KEY_RIGHT))
      && !(event.IsKeyDown(irr::KEY_KEY_Q) || event.IsKeyDown(irr::KEY_LEFT)))
    return (1);
  if ((event.IsKeyDown(irr::KEY_KEY_Q) || event.IsKeyDown(irr::KEY_LEFT))
      && !(event.IsKeyDown(irr::KEY_KEY_D) || event.IsKeyDown(irr::KEY_RIGHT) ))
    return (2);
  if (event.IsKeyDown(irr::KEY_SPACE))
    return (3);
  if (event.IsKeyDown(irr::KEY_KEY_J))
    return (4);
  if (event.IsKeyDown(irr::KEY_PRIOR) && !event.IsKeyDown(irr::KEY_NEXT))
    return (5);
  if (event.IsKeyDown(irr::KEY_NEXT) && !event.IsKeyDown(irr::KEY_PRIOR))
    return (6);

  if (event.IsKeyDown(irr::KEY_RETURN))
    return (8);
  if (event.IsKeyDown(irr::KEY_ESCAPE))
    return (10);

  if ((event.IsKeyDown(irr::KEY_KEY_Z) || event.IsKeyDown(irr::KEY_UP))
      && !(event.IsKeyDown(irr::KEY_KEY_S) || event.IsKeyDown(irr::KEY_DOWN)))
    return (11);
  if ((event.IsKeyDown(irr::KEY_KEY_S) || event.IsKeyDown(irr::KEY_DOWN))
      && !(event.IsKeyDown(irr::KEY_KEY_Z) || event.IsKeyDown(irr::KEY_UP) ))
    return (12);

  if (event.IsKeyDown(KEY_KEY_E))
    return (9);
    /*
  if (event.IsKeyDown(irr::KEY_UP))
    return (11);
  if (event.IsKeyDown(irr::KEY_DOWN))
    return (12);*/

  return (0);
}

scene::IAnimatedMeshSceneNode* Event::ChangePos(Event event, scene::IAnimatedMeshSceneNode* cube)
{
  core::vector3df	nodePos;

  nodePos = cube->getPosition();
  if (event.IsKeyDown(irr::KEY_KEY_D))
    cube->setRotation(vector3df(0, 90, 0));
  if (event.IsKeyDown(irr::KEY_KEY_Q))
    cube->setRotation(vector3df(0, 270, 0));

  // static bool isPressed = true;
  // if (isPressed == true)
  //   {
  //     if (!event.IsKeyDown(irr::KEY_SPACE))
  // 	{
  // 	  isPressed = false;
  // 	  nodePos.Y -= 0.01;
  // 	}
  //   }
  // else if (isPressed == false && event.IsKeyDown(KEY_SPACE))
  //   {
  //     nodePos.Y += 1;
  //     isPressed = true;
  //   }
   cube->setPosition(nodePos);
  return (cube);
}

int		Event::SwitchPlayer(Event event, int nb_player, int nb_max)
{
  static bool	isPressed = false;

  if (isPressed == true)
    {
      if (!event.IsKeyDown(irr::KEY_KEY_Y))
	isPressed = false;
    }
  else if (isPressed == false && event.IsKeyDown(KEY_KEY_Y))
    {
      if (nb_player < nb_max)
  	     nb_player++;
      else
  	     nb_player = 0;
      isPressed = true;
    }
  return (nb_player);
}
