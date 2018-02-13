#include		"driverChoice.h"

#include		"GameLoop.hh"
#include		"Display.hh"
#ifndef _WIN32
	#include <unistd.h>
#else
	#include <Windows.h>
#endif

int		Display::eventCatcher()
{
	if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
		return (0);
  int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];

  int X = this->team[idTeam].getWorms(idWorms).getPos().x;
  int Y = this->team[idTeam].getWorms(idWorms).getPos().y;

  if (this->weapons->_powerWeapon == 0)
  {
    if (_e.changePosTab(_e) == INVENTORY)
      {
	this->inventory();
	this->affWeaponsHUD();
      }
    if (this->gameloop.getInventory())
    {
      if (_e.changePosRight(_e) == RIGHT_WORMS)
      	this->moveInInventory(1);
      if (_e.changePosLeft(_e) == LEFT_WORMS)
      	this->moveInInventory(-1);
      if (_e.changePos(_e) == ENTER)
      	this->inventory();
      return (0);
    }

    if (_e.changePos(_e) == JUMP_WORMS)
    	this->jump(X, Y, idTeam, idWorms, JUMP_WORMS);
    else if (_e.changePos(_e) == JUMP_UP_WORMS)
    	this->jump(X, Y, idTeam, idWorms, JUMP_UP_WORMS);

    if (_e.changePos(_e) == RIGHT_WORMS && (X + 1) < this->island.getSizeX() - 1)
    	this->changeHoriz(X, Y, idTeam, idWorms, 1);
    else if (_e.changePos(_e) == LEFT_WORMS && (X - 1) > 0)
    	this->changeHoriz(X, Y, idTeam, idWorms, -1);

    if (_e.changePos(_e) == ZOOM_IN)
      {
	float zoom = cam->getFOV();
	if (zoom > 0.4)
	  zoom -= 0.01;
	cam->setFOV(zoom);
      }
    else if (_e.changePos(_e) == ZOOM_OUT)
      {
	float zoom = cam->getFOV();
	if (zoom < (M_PI / 2.5f) / 1.5)
	  zoom += 0.01;
	cam->setFOV(zoom);
      }
    if (!(this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == POUNCH
        || this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == FINGER
        || this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == BASEBALL
        || this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == JUMPTHOUGHTWALL || this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == DYNAMIT))
    {
      if (this->weapons->getCanUsWeapon())
      {
        if (_e.changePos(_e) == UP_MENU && this->weapons->_powerWeapon == 0)
        this->weapons->addAngleCursor(2);
        else if (_e.changePos(_e) == DOWN_MENU && this->weapons->_powerWeapon == 0)
        this->weapons->addAngleCursor(-2);
      }
    }
  }

  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == BAZOOKA || this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == GRENADE)
  {
    this->actionCursor(idTeam, idWorms);
  }
  else if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == UZI
          || this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == DRILL)
  {
    this->actionRepeat(idTeam, idWorms);
  }
  else
    this->actionUnique(idTeam, idWorms);
  return (0);
}

void Display::actionRepeat(int idTeam, int idWorms, bool isIa)
{
  int tmpOfAngle = 0;
  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
    tmpOfAngle = 90 - this->gameloop._tmpAngle;
  else
    tmpOfAngle = 90 + this->gameloop._tmpAngle;

  if (_e.changePos(_e) == ACTION || isIa)
  {
    if (!this->weapons->getCanUsWeapon())
      return;
    if (this->weapons->numberAction == 0)
      this->weapons->attack();
    this->createObjectWeapon( this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x, this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y,
                              tmpOfAngle, this->weapons->speed);
    this->weapons->numberAction++;
    if (this->weapons->numberAction >= this->weapons->numberMaxAction)
    {
      this->weapons->numberAction = 0;
      this->weapons->setCanUseWeapon(false);
      this->displayWeaponType();
      this->gameloop.setPhase(4);
      this->gameloop.setWaitTimeAfterAttack();
      this->gameloop._debugTimerGame = 0.0;
      return;
    }
  }
}

void Display::actionUnique(int idTeam, int idWorms)
{
  int tmpOfAngle = 0;
  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
    tmpOfAngle = 90 - this->gameloop._tmpAngle;
  else
    tmpOfAngle = 90 + this->gameloop._tmpAngle;

  if (_e.changePosAttack(_e) == ACTION)
  {
    if (!this->weapons->getCanUsWeapon())
      return;
    if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == SHOOTGUN)
    {
      if (this->weapons->numberAction == 0)
        this->weapons->attack();
      this->createObjectWeapon( this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x, this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y,
                                tmpOfAngle, this->weapons->speed);
      if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == SHOOTGUN)
      {
        this->createObjectWeapon( this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x, this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y,
                                  tmpOfAngle - 1, this->weapons->speed);
        this->createObjectWeapon( this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x, this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y,
                                  tmpOfAngle - 2, this->weapons->speed);
        this->createObjectWeapon( this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x, this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y,
                                  tmpOfAngle + 1, this->weapons->speed);
        this->createObjectWeapon( this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x, this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y,
                                  tmpOfAngle + 2, this->weapons->speed);
      }
      this->weapons->numberAction++;
      if (this->weapons->numberAction >= this->weapons->numberMaxAction)
      {
        this->weapons->numberAction = 0;
        this->weapons->setCanUseWeapon(false);
        this->displayWeaponType();
        this->gameloop.setPhase(4);
        this->gameloop.setWaitTimeAfterAttack();
        this->gameloop._debugTimerGame = 0.0;
        return;
      }
      return;
    }
    else if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == DYNAMIT)
    {
      if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
        this->dynamity(this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x + this->gameloop.getWidthWorm(), this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y);
      else
        this->dynamity(this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x - this->gameloop.getWidthWorm(), this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y);
    }


    this->weapons->attack();
    if (!this->weapons->getCanUsWeapon())
    {
      if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() != JUMPTHOUGHTWALL)
      {
        this->displayWeaponType();
        this->gameloop.setPhase(4);
        this->gameloop.setWaitTimeAfterAttack();
        this->gameloop._debugTimerGame = 0.0;
      }
    }
  }
}

void Display::actionCursor(int idTeam, int idWorms)
{
  int tmpOfAngle = 0;
  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
    tmpOfAngle = 90 - this->gameloop._tmpAngle;
  else
    tmpOfAngle = 90 + this->gameloop._tmpAngle;

  if (!this->weapons->getCanUsWeapon())
    return;
  if (_e.changePos(_e) == UP_MENU && this->weapons->_powerWeapon == 0)
    this->weapons->addAngleCursor(1);
  else if (_e.changePos(_e) == DOWN_MENU && this->weapons->_powerWeapon == 0)
    this->weapons->addAngleCursor(-1);
  else if (_e.changePos(_e) == ACTION)
  {
    if (this->weapons->_powerWeapon == 0)
      this->changeScalePower(0);
    this->weapons->_powerWeapon += 2;
    if (this->weapons->_powerWeapon > this->weapons->_maxPowerWeapon)
      this->weapons->_powerWeapon = this->weapons->_maxPowerWeapon;
    std::cout << "action cursor: " << this->weapons->_powerWeapon << std::endl;
    this->changeScalePower(1);
  }
  else
  {
    if (this->weapons->_powerWeapon != 0)
    {
      std::cout << "current power: " << this->weapons->_powerWeapon << std::endl;
      this->createObjectWeapon(this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x,
                                this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y,
                                tmpOfAngle,
                                this->weapons->_powerWeapon / 10);
      std::cout << "reset action !" << std::endl;
      this->weapons->_powerWeapon = 0;
      this->weapons->setCanUseWeapon(false);
      this->changeScalePower(2);
      this->displayWeaponType();
      this->gameloop.setPhase(4);
      this->gameloop.setWaitTimeAfterAttack();
      this->gameloop._debugTimerGame = 0.0;
    }
  }
}

void Display::catchLeave()
{
	if (_e.changePos(_e) != 0)
	{
		std::cout << "leave !" << std::endl;
		//this->removeAllWorms();
		//this->gameloop.initGame(false);
		exit(0);
	}
}

void Display::catchPause()
{
  if (_e.changePosMenu(_e) == ESCAPE)
  {
    this->gameloop.setPaused(!this->gameloop.getPaused());
    this->gameloop.setMenuSelection(0);
    if (!this->gameloop.getPaused())
    {
      std::cout << "end pause" << std::endl;
      affMenuPause(false);
      this->debugTimerGame();
    }
    else
    {
			affMenuPause(true);
			std::cout << "start pause" << std::endl;
			//this->gameloop._debugTimerGame = 0.0;
			this->gameloop.setMenuTime();
    }
  }
  if (!this->gameloop.getPaused())
    return;
  if (_e.changePosUp(_e) == UP_MENU)
    this->moveInMenu(-1);
  if (_e.changePosDown(_e) == DOWN_MENU)
    this->moveInMenu(1);
  if (_e.changePos(_e) == ENTER)
    this->selectInMenu();
}
