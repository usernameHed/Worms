#include		"driverChoice.h"

#include		"GameLoop.hh"
#include		"Display.hh"
#include		"Worms.hh"
#ifndef _WIN32
	#include <unistd.h>
#else
	#include <Windows.h>
#endif

void Display::Spawn()
{
	unsigned int i = 0;

	while (i < this->listPlayers.size())
	{
		int tmpX = this->gameloop.getWormsFromGameLoop(this->listPlayers[i][0], this->listPlayers[i][1]).getPos().x;
		int tmpY = this->gameloop.getWormsFromGameLoop(this->listPlayers[i][0], this->listPlayers[i][1]).getPos().y;
		this->SpawnPlayer(tmpX, tmpY, this->listPlayers[i][0], this->listPlayers[i][1]);
		++i;
	}
	//this->team[0].getWorms(0).getLife().
}

void Display::displayNbPlayer(int nb_player)
{
	if (!this->checkNbPlayer(nb_player))
		return;
	int                   idTeam = this->listPlayers[nb_player][0];
	int                   idWorms = this->listPlayers[nb_player][1];

	int x1 = gameloop.getWormsFromGameLoop(idTeam, idWorms).getLife().getSlifeLifePos()[0];
	int x2 = gameloop.getWormsFromGameLoop(idTeam, idWorms).getLife().getSlifeLifePos()[2];
	int y1 = gameloop.getWormsFromGameLoop(idTeam, idWorms).getLife().getSlifeLifePos()[1];
	int y2 = gameloop.getWormsFromGameLoop(idTeam, idWorms).getLife().getSlifeLifePos()[3];

	// _env->addStaticText(L"SALUUUUUUUT" + nb_player,
	// 		      rect<s32>(x1,-y1,x2,-y2),
	// 		      true,
	// 		      true);
}

bool Display::checkNbPlayer(int nb_player)
{
	if (nb_player < 0 || nb_player >= this->gameloop.listPlayers.size())
		return (false);
	return (true);
}

void Display::setLifeScale(int nb_player)
{
	if (!this->checkNbPlayer(nb_player))
		return;
	int			idTeam = this->listPlayers[nb_player][0];
	int			idWorms = this->listPlayers[nb_player][1];

	static int x1 = -1;
	static int x2 = -1;
	static int y1 = -1;
	static int y2 = -1;

	int tmpx1 = gameloop.getWormsFromGameLoop(idTeam, idWorms).getLife().getSlifeLifePos()[0];
	int tmpx2 = gameloop.getWormsFromGameLoop(idTeam, idWorms).getLife().getSlifeLifePos()[2];
	int tmpy1 = gameloop.getWormsFromGameLoop(idTeam, idWorms).getLife().getSlifeLifePos()[1];
	int tmpy2 = gameloop.getWormsFromGameLoop(idTeam, idWorms).getLife().getSlifeLifePos()[3];

	if (tmpx1 == x1 && tmpx2 == x2 && tmpy1 == y1 && tmpy2 == y2)
		return;
	x1 = tmpx1;
	x2 = tmpx2;
	y1 = tmpy1;
	y2 = tmpy2;

	float scale = (static_cast<float>(x2) - static_cast<float>(x1));
	core::vector3df Scale = listLife[nb_player]->getScale();
	Scale.X = scale;
	Scale.Y = 5;
	Scale.Z = 10;
	this->listLife[nb_player]->setScale(Scale);
}

int             Display::SpawnPlayer(int X, int Y, int idTeam, int idWorms)
{
	float                 regulator = 1;
	float                 cubeSize = 0.0266 * regulator;
	float                 y = 0;
	float                 x = 0;

	y = -14 + (Y * cubeSize);
	x = (X * cubeSize) - 25.4;
	cube = ObjCreate("media/objs/worm/worm.obj", "", core::vector3df(x, -y, 19.95f));

	scene::ISceneNode* life = _smgr->addCubeSceneNode(cubeSize);

	y -= cubeSize * 15;
	life->setMaterialFlag(video::EMF_LIGHTING, false);
	if (idTeam == 0)
	  life->setMaterialTexture(0, _driver->getTexture("media/Textures/red.jpg"));
	else if (idTeam == 1)
	  life->setMaterialTexture(0, _driver->getTexture("media/Textures/green.jpg"));
	else if (idTeam == 2)
	  life->setMaterialTexture(0, _driver->getTexture("media/Textures/blue.png"));
	else if (idTeam == 3)
	  life->setMaterialTexture(0, _driver->getTexture("media/Textures/orange.jpg"));

	life->setPosition(core::vector3df(x, -y, 19.8f));
	this->listLife.push_back(life);

	displayNbPlayer(idWorms);

	if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == LEFT)
	    cube->setRotation(vector3df(0, 270, 0));
	else
	    cube->setRotation(vector3df(0, 90, 0));
	cube->setScale(vector3df(SIZE_PLAYER, SIZE_PLAYER, SIZE_PLAYER));
	this->listObjPlayers.push_back(cube);
	return (0);
}

int		Display::replacePlayer(int X, int Y, int nb_player)
{
	float			regulator = 1;
	this->cubeSize = 0.0266 * regulator;
	float			y = 0;
	float			x = 0;

	if (!this->checkNbPlayer(nb_player))
		return (0);
	int			idTeam = this->listPlayers[nb_player][0];
	int			idWorms = this->listPlayers[nb_player][1];

	y = -14 + (Y * cubeSize);
	x = (X * cubeSize) - 25.4;

	this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setPos(X, Y);

	core::vector3df nodePosition = listObjPlayers[nb_player]->getPosition();
	nodePosition.Y = -y;
	nodePosition.X = x;
	nodePosition.Z = 19.8f;
	this->listObjPlayers[nb_player]->setPosition(nodePosition);
	nodePosition.Y += 15 * cubeSize;

	this->setWeaponToPlayer(this->gameloop.getWormsPlayer(), true);
	this->listLife[nb_player]->setPosition(nodePosition);
	return (0);
}

void Display::setWeaponToPlayer(int nb_player, bool setWeap)
{
  if (!this->checkNbPlayer(nb_player))
    return;

	if (!this->weapons->getCanUsWeapon())
		setWeap = false;

  int idTeam = this->listPlayers[nb_player][0];
  int idWorms = this->listPlayers[nb_player][1];
	int x = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x;
	int y = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y;
	//int angleRot = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).
	float Y = -14 + (y * 0.0266);
	float X = (x * 0.0266) - 25.4;
	Y *= -1;
	if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == SHOOTGUN)
	{
		//set shootgun to x, y
		this->shotgun_aff->setPosition(core::vector3df(X, Y, 19.5f));
		if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
		{
			if (shotgun_aff->getScale().Z > 0)
				this->shotgun_aff->setScale(core::vector3df(shotgun_aff->getScale().X, shotgun_aff->getScale().Y, shotgun_aff->getScale().Z));
			else
				this->shotgun_aff->setScale(core::vector3df(shotgun_aff->getScale().X, shotgun_aff->getScale().Y, -shotgun_aff->getScale().Z));
			this->shotgun_aff->setRotation(core::vector3df(shotgun_aff->getRotation().X, /*-*/shotgun_aff->getRotation().Y, -this->gameloop._tmpAngle + 75));
		}
		else
		{
			if (shotgun_aff->getScale().Z > 0)
				this->shotgun_aff->setScale(core::vector3df(shotgun_aff->getScale().X, shotgun_aff->getScale().Y, -shotgun_aff->getScale().Z));
			else
				this->shotgun_aff->setScale(core::vector3df(shotgun_aff->getScale().X, shotgun_aff->getScale().Y, shotgun_aff->getScale().Z));
			this->shotgun_aff->setRotation(core::vector3df(shotgun_aff->getRotation().X, shotgun_aff->getRotation().Y, this->gameloop._tmpAngle - 75));
		}
		if (!setWeap)
			this->shotgun_aff->setPosition(core::vector3df(1000, 1000, 19.5f));
	}
	if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == UZI)
	{
		//set shootgun to x, y
		this->uzi_aff->setPosition(core::vector3df(X, Y, 19.5f));
		if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
		{
			if (uzi_aff->getScale().Z > 0)
				this->uzi_aff->setScale(core::vector3df(uzi_aff->getScale().X, uzi_aff->getScale().Y, uzi_aff->getScale().Z));
			else
				this->uzi_aff->setScale(core::vector3df(uzi_aff->getScale().X, uzi_aff->getScale().Y, -uzi_aff->getScale().Z));

			this->uzi_aff->setRotation(core::vector3df(uzi_aff->getRotation().X, uzi_aff->getRotation().Y, -this->gameloop._tmpAngle + 75));
		}
		else
		{
			if (uzi_aff->getScale().Z > 0)
				this->uzi_aff->setScale(core::vector3df(uzi_aff->getScale().X, uzi_aff->getScale().Y, -uzi_aff->getScale().Z));
			else
				this->uzi_aff->setScale(core::vector3df(uzi_aff->getScale().X, uzi_aff->getScale().Y, uzi_aff->getScale().Z));

			this->uzi_aff->setRotation(core::vector3df(uzi_aff->getRotation().X, uzi_aff->getRotation().Y, this->gameloop._tmpAngle - 75));
		}
		if (!setWeap)
			this->uzi_aff->setPosition(core::vector3df(1000, 1000, 19.5f));
	}
	if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == BAZOOKA)
	{
		//set shootgun to x, y
		this->bazooka_aff->setPosition(core::vector3df(X, Y, 19.5f));
		if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
		{
			if (bazooka_aff->getScale().Z > 0)
				this->bazooka_aff->setScale(core::vector3df(bazooka_aff->getScale().X, bazooka_aff->getScale().Y, bazooka_aff->getScale().Z));
			else
				this->bazooka_aff->setScale(core::vector3df(bazooka_aff->getScale().X, bazooka_aff->getScale().Y, -bazooka_aff->getScale().Z));

			this->bazooka_aff->setRotation(core::vector3df(bazooka_aff->getRotation().X, /*-*/bazooka_aff->getRotation().Y, -this->gameloop._tmpAngle + 75));
		}
		else
		{
			if (bazooka_aff->getScale().Z > 0)
				this->bazooka_aff->setScale(core::vector3df(bazooka_aff->getScale().X, bazooka_aff->getScale().Y, -bazooka_aff->getScale().Z));
			else
				this->bazooka_aff->setScale(core::vector3df(bazooka_aff->getScale().X, bazooka_aff->getScale().Y, bazooka_aff->getScale().Z));


			this->bazooka_aff->setRotation(core::vector3df(bazooka_aff->getRotation().X, bazooka_aff->getRotation().Y, this->gameloop._tmpAngle - 75));
		}
		if (!setWeap)
			this->bazooka_aff->setPosition(core::vector3df(1000, 1000, 19.5f));
	}
	if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == DYNAMIT)
	{
		//set shootgun to x, y
		this->dynamite_aff->setPosition(core::vector3df(X, Y, 19.5f));
		this->dynamite_aff->setRotation(core::vector3df(dynamite_aff->getRotation().X, dynamite_aff->getRotation().Y, 0.0f));
		if (!setWeap)
			this->dynamite_aff->setPosition(core::vector3df(1000, 1000, 19.5f));
	}
	if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == GRENADE)
	{
		//set shootgun to x, y
		this->grenade_aff->setPosition(core::vector3df(X, Y, 19.5f));
		this->grenade_aff->setRotation(core::vector3df(grenade_aff->getRotation().X, grenade_aff->getRotation().Y, 45.0f));
		if (!setWeap)
			this->grenade_aff->setPosition(core::vector3df(1000, 1000, 19.5f));
	}
}

void Display::removeAllWorms()
{
  this->gameloop.setWormsPlayer(-1);
  std::cout << "remove all worms ?" << std::endl;
  std::cout << "size: " << this->gameloop.listPlayers.size() << std::endl;
  while(this->gameloop.listPlayers.size() > 0)
  {
    this->removing(0);
  }
}

void Display::removing(int nb_player)
{
	if (!this->checkNbPlayer(nb_player))
		return;
	int idTeam = this->listPlayers[nb_player][0];
	int idWorms = this->listPlayers[nb_player][1];
	std::cout << "removing worms ! (" << idTeam << ":" << idWorms << ")" << std::endl;

	this->replacePlayer(-1000, -1000, nb_player);
	if (nb_player == this->gameloop.getWormsPlayer())
	{
		this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setPlaying(false);
		this->gameloop.setTmpDead(true);
	}
	this->gameloop.getWormsFromGameLoop(idTeam, idWorms).takeDamage(this->team[idTeam].getWorms(idWorms).getLife().getPv());

	//if (this->listObjPlayers.size() < nb_player)
		this->listObjPlayers.erase(this->listObjPlayers.begin() + nb_player);
	//if (this->listPlayers.size() < nb_player)
		this->listPlayers.erase(this->listPlayers.begin() + nb_player);
	//if (this->listLife.size() < nb_player)
		this->listLife.erase(this->listLife.begin() + nb_player);
	if (nb_player == this->gameloop.getWormsPlayer())
		this->gameloop.setPhase(3);
}

void Display::inventory()
{
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
    {
      this->weapons->setCanUseWeapon(false);
      return;
    }
  if (this->gameloop.getInventory())
    {
      this->affWeaponsHUD();
	  //close inventory
	  std::cout << "close" << std::endl;
	  this->gameloop.setInventory(false);
	  this->weapons->setCanUseWeapon(true);
	  this->displayWeaponType();
	  inventoryDisp->remove();
	  inventorySelect->remove();
	  //this->gameloop.setPreselectedInventory((int)this->gameloop.getWormsFromGameLoop(this->listPlayers[this->gameloop.getWormsPlayer()][0], this->listPlayers[this->gameloop.getWormsPlayer()][1]).getWeaponsType());
	}
	else
	  {
this->affWeaponsHUD();
	    //open inventory
	    std::cout << "open" << std::endl;
	    this->gameloop.setInventory(true);
	    this->weapons->setCanUseWeapon(false);
	    this->displayWeaponType();
	    this->gameloop.setPreselectedInventory((int)this->gameloop.getWormsFromGameLoop(this->listPlayers[this->gameloop.getWormsPlayer()][0], this->listPlayers[this->gameloop.getWormsPlayer()][1]).getWeaponsType());
	    std::cout << "type weapon first: " << this->gameloop.getWormsFromGameLoop(this->listPlayers[this->gameloop.getWormsPlayer()][0], this->listPlayers[this->gameloop.getWormsPlayer()][1]).getWeaponsType() << std::endl;
	    inventoryDisp = _env->addImage(_driver->getTexture("media/inventory/inventory.png"), position2d<int>(WINDOW_SIZE_X / 4, WINDOW_SIZE_Y / 4));
	    inventorySelect = _env->addImage(_driver->getTexture("media/inventory/inventorySelect.png"), position2d<int>(WINDOW_SIZE_X / 8.65, WINDOW_SIZE_Y / 5.08));
	    dispSelectedWeapon();
	  }
}

void Display::dispSelectedWeapon()
{
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
    return;
  WeaponsType balek = this->gameloop.getWormsFromGameLoop(this->listPlayers[this->gameloop.getWormsPlayer()][0], this->listPlayers[this->gameloop.getWormsPlayer()][1]).getWeaponsType();

	float		X;
	float		X2;
	float		Y;
	float		Y2;

	X = (WINDOW_SIZE_X / 5.466);
	X2 = (WINDOW_SIZE_X / 8.65);
	Y2 = (WINDOW_SIZE_Y / 3.25);
	Y = (WINDOW_SIZE_Y / 5.08);

	//En haut
	if (balek == 0)
	  inventorySelect->setRelativePosition(position2d<int>(X2, Y));
	if (balek == 1)
	  inventorySelect->setRelativePosition(position2d<int>(X2 + (X - X2), Y));
	if (balek == 2)
	  inventorySelect->setRelativePosition(position2d<int>(X2 + ((X - X2) * 2), Y));
	if (balek == 3)
	  inventorySelect->setRelativePosition(position2d<int>(X2 + ((X - X2) * 3), Y));
	if (balek == 4)
	  inventorySelect->setRelativePosition(position2d<int>(X2 + ((X - X2) * 4), Y));

	//En bas
	if (balek == 5)
	  inventorySelect->setRelativePosition(position2d<int>(X2, Y + (Y2 - Y)));
	if (balek == 6)
	  inventorySelect->setRelativePosition(position2d<int>(X2 + (X - X2), Y + (Y2 - Y)));
	if (balek == 7)
	  inventorySelect->setRelativePosition(position2d<int>(X2 + ((X - X2) * 2), Y + (Y2 - Y)));
	if (balek == 8)
	  inventorySelect->setRelativePosition(position2d<int>(X2 + ((X - X2) * 3), Y + (Y2 - Y)));
	if (balek == 9)
	  inventorySelect->setRelativePosition(position2d<int>(X2 + ((X - X2) * 4), Y + (Y2 - Y)));

}

void Display::moveInInventory(int move)
{
	if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
		return;
	int sizeInventory = NONE;
	this->gameloop.setPreselectedInventory(this->gameloop.getPreselectedInventory() + move);
	if (this->gameloop.getPreselectedInventory() < 0)
		this->gameloop.setPreselectedInventory(sizeInventory - 1);
	else if (this->gameloop.getPreselectedInventory() >= sizeInventory)
		this->gameloop.setPreselectedInventory(0);
	this->gameloop.getWormsFromGameLoop(this->listPlayers[this->gameloop.getWormsPlayer()][0], this->listPlayers[this->gameloop.getWormsPlayer()][1]).setWeaponsType((WeaponsType)this->gameloop.getPreselectedInventory());

	std::cout << "type weapon move: " << this->gameloop.getWormsFromGameLoop(this->listPlayers[this->gameloop.getWormsPlayer()][0], this->listPlayers[this->gameloop.getWormsPlayer()][1]).getWeaponsType() << std::endl;
	dispSelectedWeapon();
}

void Display::debugTimerGame()
{
	std::cout << "end time escape:" << this->gameloop.getCurrentMenuTime() << std::endl;
	this->gameloop._debugTimerGame += this->gameloop.getCurrentMenuTime();
}

/*void Display::reinitTeamBackToMenu()
{
	//std::vector<Team> teams;
  for (size_t i = 0; i < MAX_TEAMS; i++)
  {
    this->getGame().teams.push_back(Team(i));
    for (size_t j = 0; j < MAX_WORMS_PER_TEAM; j++)
      this->getGame().teams[i].addWorms(Worms(j, i, IA, "adolf", 100, LEFT));
  }
}*/

void Display::selectInMenu()
{
	if (this->gameloop.getMenuSelection() == 0)
	{
		this->gameloop.setPaused(false);
		this->gameloop.setMenuSelection(0);
		std::cout << "resume selected" << std::endl;
		this->affMenuPause(false);
		this->debugTimerGame();
	}
	else if (this->gameloop.getMenuSelection() == 1)
	{
		std::cout << "save and quit" << std::endl;
		this->island.saveMap("test.worms");
		this->gameloop.exitGame = true;
		/*this->affMenuPause(false);

		this->removeAllWorms();
	  this->getGame().teams.clear();
		this->getGame().difficulty = MEDIUM_GAME;

		this->reinitTeamBackToMenu();
		this->gameloop.initGame(true);*/

	}
	else
	{
		std::cout << "quit" << std::endl;
		this->gameloop.exitGame = true;
		/*this->affMenuPause(false);

		this->removeAllWorms();
	  this->getGame().teams.clear();
		this->getGame().difficulty = MEDIUM_GAME;

		this->reinitTeamBackToMenu();
		this->gameloop.initGame(true);*/

	}
}

void Display::moveInMenu(int move)
{
	int sizeInventory = QUIT_GAME + 1;
	this->gameloop.setMenuSelection(this->gameloop.getMenuSelection() + move);
	if (this->gameloop.getMenuSelection() < 0)
		this->gameloop.setMenuSelection(sizeInventory - 1);
	else if (this->gameloop.getMenuSelection() >= sizeInventory)
		this->gameloop.setMenuSelection(0);
	onSpriteSwitch(this->gameloop.getMenuSelection());
	std::cout << "menu move: " << this->gameloop.getMenuSelection() << std::endl;
}
