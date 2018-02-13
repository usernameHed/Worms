#include	   "GameLoop.hh"
#include		 "Menu.hh"
#include	   "Display.hh"
#ifndef		_WIN32
  #include <unistd.h>
#else
  #include <Windows.h>
#endif

int		Display::InitWindow()
{
  IrrlichtDevice *device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1920, 1080), 16,
					true, /* true for fullsreen */ false, false, &_e);


  if (!device)
    return 1;
  IVideoDriver*		driver = device->getVideoDriver();
  ISceneManager*	smgr = device->getSceneManager();
  IGUIEnvironment*      env = device->getGUIEnvironment();

  device->getCursorControl()->setVisible(false);
  this->_env = env;
  this->_device = device;
  this->_driver = driver;
  this->_smgr = smgr;
  return (0);
}

IAnimatedMeshSceneNode*		Display::ObjCreate(std::string obj, std::string texture, core::vector3df position)
{
  IAnimatedMesh*     mesh = _smgr->getMesh(obj.c_str());
  IAnimatedMeshSceneNode* node = _smgr->addAnimatedMeshSceneNode(mesh);

  node->setPosition(position);
  if (texture != "")
    node->setMaterialTexture(0, _driver->getTexture(texture.c_str()));
  node->setMaterialFlag(video::EMF_LIGHTING, false);
  return (node);
}

int		Display::DispWater(std::string waterTexture)
{
  this->gameloop.lg.log("[Display.cpp] - DispWater\n");
  scene::IAnimatedMesh* mesh = _smgr->getMesh("media/objs/cube.obj");
  mesh = _smgr->addHillPlaneMesh( "myHill",
				  core::dimension2d<f32>(5,5),
				  core::dimension2d<u32>(90,90), 0, 0
				  , core::dimension2d<f32>(0,0),
				  core::dimension2d<f32>(10,10));

  water = _smgr->addWaterSurfaceSceneNode(mesh->getMesh(0), WAVE_HEIGHT, WAVE_SPEED, WAVE_LENGTH);
  if (this->island.getGeneratorType() == ISLAND)
    water->setPosition(core::vector3df(-20, -14.4, 0));
  else if (this->island.getGeneratorType() == PLANE)
    water->setPosition(core::vector3df(-20, -14.39, 0));
  water->setMaterialTexture(0, _driver->getTexture(waterTexture.c_str()));
  water->setMaterialTexture(1, _driver->getTexture(waterTexture.c_str()));
  water->setMaterialType(video::EMT_REFLECTION_2_LAYER);
  water = _smgr->addLightSceneNode(0, core::vector3df(0, 20, 0),
				   video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 10000.0f);
  return (0);
}

int		Display::DispMap()
{
  int			sizeX = this->island.getSizeX();
  int			sizeY = this->island.getSizeY();

  unsigned int		i = 0;
  float			regulator = 1920.0 / static_cast<float>(sizeX);
  float			cubeSize = 0.0266 * regulator;
  float			scale = 1;
  float			y = 0;
  float			x = ((this->obj.getListObject()[i][0] * cubeSize) - 25.4);

  unsigned int  tmpk = 0;
  while (tmpk < this->irrMap.size())
    {
      this->irrMap[tmpk]->remove();
      ++tmpk;
    }
  this->irrMap.clear();
  while (i < this->obj.getListObject().size())
    {
      unsigned int	x1 = this->obj.getListObject()[i][0];
      unsigned int	y1 = this->obj.getListObject()[i][1];
      unsigned int	y2 = this->obj.getListObject()[i][3];
      Mapping const	mapping = (Mapping)this->obj.getListObject()[i][4];

      scale = (y1 - y2) + 1;
      y = -14;
      y += ((cubeSize * scale) / 2) + (y2 * cubeSize);
      x = (x1 * cubeSize) - 25.4;
      scene::ISceneNode* cube2 =
	_smgr->addCubeSceneNode(cubeSize, 0, -1, irr::core::vector3df(x, -y, 20.0f), irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, scale, 20));
      cube2->setMaterialFlag(video::EMF_LIGHTING, false);

      if (mapping == SAND)
	cube2->setMaterialTexture(0, _driver->getTexture("media/Textures/beigeFonce.jpg"));
      else if (mapping == GRASS && this->island.getGeneratorType() == ISLAND)
	cube2->setMaterialTexture(0, _driver->getTexture("media/Textures/beige.jpg"));
      else if (mapping == GRASS && this->island.getGeneratorType() == PLANE)
	cube2->setMaterialTexture(0, _driver->getTexture("media/Textures/redFonce.jpg"));
      else if (mapping == GRASS_PLANE)
	cube2->setMaterialTexture(0, _driver->getTexture("media/Textures/red.jpg"));
      if (mapping == WATER)
	cube2->setMaterialTexture(0, _driver->getTexture("media/Textures/blue.png"));
      this->irrMap.push_back(cube2);
      i++;
    }
  return (0);
}

int		Display::DispBackground(std::string background)
{
  video::ITexture* backGround =
    _driver->getTexture(background.c_str());
  _driver->makeColorKeyTexture(backGround, core::position2d<s32>(0, 0));
  _backGround = backGround;
  if (!backGround)
    return (-1);
  return (0);
}

bool Display::testIfWormsAlive(int nb_player)
{
  if (!this->checkNbPlayer(nb_player))
    return (false);
  if (!this->gameloop.getWormsFromGameLoop(this->gameloop.listPlayers[nb_player][0], this->gameloop.listPlayers[nb_player][1]).testDeath())
    {
      this->removing(nb_player);
      return (false);
    }
  return (true);
}

void Display::timeLeft()
{
  static int lastTime = -1;
  int current = 0;
  if (this->gameloop.getPhase() == 2)
    current = (int)((this->gameloop.getWormsMaxTime() + this->gameloop._debugTimerGame) - this->gameloop.getCurrentTimeWorms());
  else if (this->gameloop.getPhase() == 1)
    current = (int)((this->gameloop.getMaxTimeBetweenWorms() + this->gameloop._debugTimerGame) - this->gameloop.getCurrentWaitTime());
  else if (this->gameloop.getPhase() == 4)
    current = (int)((this->gameloop.getMaxTimeBetweenWorms() + this->gameloop._debugTimerGame) - this->gameloop.getCurrentTimeAfterAttackWorms());
  else
    return;
  if (current != lastTime)
    {
      currentTime = current;
      this->affTime(current);
      lastTime = current;
    }
}

void    Display::loop()
{
  static bool isDisplayed = false;
  static bool zoom = false;

  if (!this->gameloop.debugStaticHud) //// debug static display HUD
  {
    isDisplayed = false;
    this->gameloop.debugStaticHud = true;
  }
  this->gameloop.findWhoPlay();

  //this->testIfWormsAlive();
  ////// change player if it is the time

  //le joueur à attaqué, il lui reste ~~5 seconde
  if (this->gameloop.getPhase() == 4
      && this->gameloop.getCurrentTimeAfterAttackWorms() > this->gameloop.getMaxTimeBetweenWorms() + this->gameloop._debugTimerGame)
  {
    cam->setFOV((M_PI / 2.5f) / 4);
    this->gameloop.setPhase(3);
    this->gameloop._debugTimerGame = 0.0;
  }

  if (this->gameloop.getPhase() == 0)
  {
    cam->setFOV((M_PI / 2.5f) / 1.5);
    zoom = false;
    cam->setPosition(core::vector3df(0, -10, 0));
    cam->setTarget(core::vector3df(0, -15, 20));
    this->gameloop.lg.log("[Display.cpp] - set the next player, start the waiting time for the player\n");
    this->gameloop.nextWhoIsPlaying();
    this->gameloop.setWaitTime();
    this->gameloop.setPhase(1);
    this->weapons->jumpi = JUMP_NONE;
    if (this->iaIsPlaying())
      this->iaExportInfo();
    return;
  }

  //test if the wait time is over
  if (this->gameloop.getPhase() == 1
      && this->gameloop.getCurrentWaitTime() > this->gameloop.getMaxTimeBetweenWorms() + this->gameloop._debugTimerGame)
    {
      cam->setPosition(core::vector3df(0, -10, 0));
      cam->setTarget(core::vector3df(0, -15, 20));
      this->gameloop.lg.log("[GameLoopInit.cpp] - wait time is over\n");
      this->gameloop._debugTimerGame = 0.0;
      this->gameloop.setWhoIsPlaying();  //change the player settings
      this->gameloop.setWormsTime();          //set the time of the worms
      this->gameloop.setPhase(2);
      this->weapons->setCanUseWeapon(true);
      this->displayWeaponType();
      return;
    }

  if (this->gameloop.getPhase() == 2 || this->gameloop.getPhase() == 4) //if player can play !
    {
      if (!isDisplayed && !this->gameloop.menuSet)
	{
	  this->gameloop.lg.log("[GameLoopInit.cpp] - playing...\n");
	  this->hud = _env->addImage(_driver->getTexture("media/hud/hud.png"), position2d<int>(0, 0));
	  this->affNameHUD();
	  this->affLifeHUD();
	  this->affWeaponsHUD();
    //this->setWeaponToPlayer(this->, true);
	  isDisplayed = true;
	}

      if (cam->getFOV() > 0.4 && !zoom)
	cam->setFOV(cam->getFOV() - 0.03);
      else
	zoom = true;
      this->setZoomPlayer();
      this->setCameraPosition();
      if (!this->iaIsPlaying() && !this->gameloop.menuSet)
	{
	  //player
	  this->gameloop.lg.log("[GameLoopInit.cpp] - player time\n");
	  this->eventCatcher();
	}
      else
	{
	  //this->eventCatcher();//TODO: enleve
	  this->iaPlaying();
	}
    }

  ///////////////////// ????
  if (this->menuHome->isMenuHome && !this->menuHome->isIntro)
    {
      if (this->menuHome->getHomePage() == TEAM_PAGE
	  || this->menuHome->getHomePage() == HOME)
	this->menuHome->eventHandler(_e.changePosMenuHome(_e), 4);
      if (menuHome->getHomePage() == SETTINGS)
	this->menuHome->eventHandler(_e.changePosMenuHome(_e), 3);
      if (this->menuHome->getHomePage() == MAP_PAGE)
	this->menuHome->eventHandler(_e.changePosMenuHome(_e), 2);
    }
  ////////////////////???

  //test if worms time is over
  if ((this->gameloop.getPhase() == 2 && this->gameloop.getCurrentTimeWorms() > this->gameloop.getWormsMaxTime() + this->gameloop._debugTimerGame)
      || this->gameloop.getPhase() == 3)
    {
      this->explodeDynamo();
      isDisplayed = false;
      //      if (this->hud)
      //      this->hud->remove();
      this->gameloop._debugTimerGame = 0.0;
      this->weapons->_powerWeapon = 0;
      if (this->gameloop.getInventory())
	this->inventory();
      // setNewCameraPos(0, 0, 1);
      // setCameraPosition();
      std::cout << "time over" << std::endl;
      this->weapons->setCanUseWeapon(false);
      if (this->weapons->jumpi == JUMP_FALL)
    	{
    	  this->weapons->jumpi = JUMP_NONE;
    	  this->weapons->activeParachute();
	}
      this->displayWeaponType();
      this->gameloop.findWhoPlay();
      this->gameloop.setPhase(0);
    }
}

void Display::initObject()
{
  std::cout << "FUCK IT" << std::endl;
  int x = 2500;
  int y = 2500;
  float X = (x * 0.0266) - 25.4;
  float Y = -14 + (y * 0.0266);
  this->uzi_aff =  ObjCreate("media/weapons/Uzi/Uzi.obj", "", core::vector3df(X, -Y, 17.5f));
  this->uzi_aff->setScale(core::vector3df(0.07f, 0.07f, 0.07f));
  this->uzi_aff->setRotation(core::vector3df(this->uzi_aff->getRotation().X, this->uzi_aff->getRotation().Y + 45.0f, this->uzi_aff->getRotation().Z));
  this->bazooka_aff =  ObjCreate("media/weapons/Bazooka/Bazooka.obj", "", core::vector3df(X, -Y, 17.5f));
  this->bazooka_aff->setScale(core::vector3df(0.07f, 0.07f, 0.07f));
  this->bazooka_aff->setRotation(core::vector3df(this->bazooka_aff->getRotation().X, this->bazooka_aff->getRotation().Y + 45.0f, this->bazooka_aff->getRotation().Z));
  this->shotgun_aff =  ObjCreate("media/weapons/Shotgun/Shotgun.obj", "", core::vector3df(X, -Y, 17.5f));
  this->shotgun_aff->setScale(core::vector3df(0.07f, 0.07f, 0.07f));
  this->shotgun_aff->setRotation(core::vector3df(this->shotgun_aff->getRotation().X, this->shotgun_aff->getRotation().Y + 45.0f, this->shotgun_aff->getRotation().Z));
  this->grenade_aff =  ObjCreate("media/weapons/Grenade/Grenade.obj", "", core::vector3df(X, -Y, 17.5f));
  this->grenade_aff->setScale(core::vector3df(0.07f, 0.07f, 0.07f));
  this->grenade_aff->setRotation(core::vector3df(this->grenade_aff->getRotation().X, this->grenade_aff->getRotation().Y + 45.0f, this->grenade_aff->getRotation().Z));
  this->dynamite_aff =  ObjCreate("media/weapons/Dynamite/Dynamite.obj", "", core::vector3df(X, -Y, 17.5f));
  this->dynamite_aff->setScale(core::vector3df(0.05f, 0.05f, 0.05f));
  this->dynamite_aff->setRotation(core::vector3df(this->dynamite_aff->getRotation().X, this->dynamite_aff->getRotation().Y + 45.0f, this->dynamite_aff->getRotation().Z));

  this->cursor = this->ObjCreate("media/objs/sight.obj", "media/Textures/intensitycolor.png", core::vector3df(X, -Y, 17.5f));
  this->cursor->setScale(core::vector3df(0.1, 0.1, 0.1));
  this->powerCursor = this->ObjCreate("media/objs/intensity.obj", "media/Textures/intensitycolor.png", core::vector3df(X, -Y, 17.5f));
  this->powerCursor->setScale(core::vector3df(0.05f, 0.05f, 0.05f));


}

void Display::victory(int id)
{
  static bool victory = false;

    if (id == -1)
    std::cout << "equality !" << std::endl;
  else
    std::cout << "victory for the team : " << id << std::endl;
  this->yeahVictory = true;
  this->cam->setFOV(M_PI / 2.5f);
  this->gameloop.setPaused(true);
  int i = -1;
  int tmpEnemyScore = 0;
  int tmpAllyScore = 0;
  while (++i < this->gameloop.getListLifeScore().size())
  {
    if (i != id)
      tmpEnemyScore += this->gameloop.getListLifeScore()[i][1];
    else
      tmpAllyScore += this->gameloop.getListLifeScore()[i][1];
  }
  std::cout << "tmpEnemyScore : " << tmpEnemyScore << std::endl;
  std::cout << "tmpAllyScore : " << tmpAllyScore << std::endl;
  i = -1;
  int actualLifeAlly = 0;
  while (++i < this->gameloop.listPlayers.size())
  {
    int idTeam = this->gameloop.listPlayers[i][0];
    int idWorms = this->gameloop.listPlayers[i][1];
    actualLifeAlly += this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getLife().getPv();
  }
  std::cout << "actualLifeAlly: " << actualLifeAlly << std::endl;
  int scoreFinal = tmpEnemyScore + actualLifeAlly - ((tmpAllyScore - actualLifeAlly) * 3);


  std::cout << "score final: " << scoreFinal << std::endl;
  std::cout << "victory for the team : " << id << std::endl;

   std::string team = "media/menuteam/" + std::to_string(id) + "vic.png";
  _env->addImage(_driver->getTexture(team.c_str()), position2d<int>(0, 0));

  std::string str = std::to_string(scoreFinal);
  int disp = WINDOW_SIZE_X / 1.9;
  int x = 0;
  while (str[x])
    {
      affNumb(str[x] - 48, disp, WINDOW_SIZE_Y / 2.1);
      disp += 50;
      x++;
    }
  
  
  if (!victory)
  victory = true;
}

void Display::testVictory()
{
  std::vector<int> tmpTeam;
  int team1 = 0;
  int team2 = 0;
  int team3 = 0;
  int team4 = 0;
  for (int i = 0; i < this->gameloop.listPlayers.size(); i++)
  {
    int idTeam = this->gameloop.listPlayers[i][0];
    if (idTeam == 0)
      ++team1;
    else if (idTeam == 1)
      ++team2;
    else if (idTeam == 2)
      ++team3;
    else
      ++team4;
    //int idWorms = this->gameloop.listPlayers[i][1];
  }
  if (team1 > 0 && team2 == 0 && team3 == 0 && team4 == 0)
    this->victory(0);
  else if (team1 == 0 && team2 > 0 && team3 == 0 && team4 == 0)
    this->victory(1);
  else if (team1 == 0 && team2 == 0 && team3 > 0 && team4 == 0)
    this->victory(2);
  else if (team1 == 0 && team2 == 0 && team3 == 0 && team4 > 0)
    this->victory(3);
  else if (team1 == 0 && team2 == 0 && team3 == 0 && team4 == 0)
    this->victory(-1);
}

void Display::DrawMenu()
{
  //ici menu
  int i = 0;
  while (i < listPlayers.size())
    {
      this->GravityWorms(i);
      this->setLifeScale(i);
      this->setForceWorms(i);
      ++i;
    }
  this->timeLeft();
  this->loop();
  this->objectPhysics();
  this->affCursorAfter();
}

void Display::DrawGame()
{
  this->testVictory();
  if (!this->yeahVictory)
    this->catchPause();
  else
    this->catchLeave();
  if (!this->gameloop.getPaused())
    {
      int i = 0;
      this->gameloop._debugRand = !this->gameloop._debugRand;
      while (i < listPlayers.size())
    	{
    	  this->GravityWorms(i);
    	  this->setLifeScale(i);
    	  this->setForceWorms(i);
    	  ++i;
    	}
      this->timeLeft();
      this->loop();
      this->objectPhysics();
      this->affCursorAfter();
    }
}

void		Display::DrawAll()
{
  if (this->gameloop.menuSet)
    {
      this->menuHome = new Menu(*this);
      this->menuHome->createMenu();
    }

  this->gameloop.setGlobaleTime();
  this->gameloop.setPhase(0);
  this->initObject();

  this->gameloop.lg.log("[Display.cpp] - DrawAll init\n");
  if (!this->gameloop.menuSet)
    _env->addImage(_driver->getTexture("media/hud/hudlite2.png"), core::position2d<int>(0, 0));
  this->DispWater("media/Textures/water2.jpg");

  s32 ref = this->_device->getTimer()->getTime();
  static bool isChecked = false;
  while (_device->run())
    {
      if (this->gameloop.exitGame)
        break;
      _driver->beginScene(true, true, SColor(255, 255, 255, 255));

      ///////////////////////////////////////////////
      if (this->gameloop.menuSet)
	{
	  if ((this->_device->getTimer()->getTime() - ref) >= 3000 && !isChecked)
  	    {
  	      this->menuHome->remove_menu();
  	      isChecked = true;
	    }
	  else
	    this->DrawMenu();
	}
      else
	{
	  ////////////////// pas demenu !
	  if (!this->gameloop.firstTimeNoMenu)
	    {
	      std::cout << "first pas de menu" << std::endl;
	      this->gameloop.initTeams();
	      this->gameloop.initListPlayer();
	      this->gameloop.initDisplay(this->gameloop.firstTimeNoMenu);

	      //if type == island or plane,
	      if (this->island.getGeneratorType() == ISLAND)
    		{
    		  this->DispWater("media/Textures/water2.jpg");
    		  this->DispBackground("media/background/background.jpg");
    		}
	      else if (this->island.getGeneratorType() == PLANE)
    		{
    		  water->setVisible(false);
    		  this->DispWater("media/Textures/lava.jpg");
    		  this->DispBackground("media/background/background2.jpg");
    		}
	      this->DispMap();
	      this->Spawn();

	      this->gameloop.setGlobaleTime();
	      this->gameloop.setPhase(0);
	      this->gameloop.firstTimeNoMenu = true;
	    }
	  else
	    {
	      this->DrawGame();
	    }
	}
      ////////////////////////////////////////////////


      if (_backGround)
      	_driver->draw2DImage(_backGround, core::position2d<s32>(0, 0),
			     core::rect<s32>(0, 0, 1920, 1080), 0);
      _smgr->drawAll();
      _env->drawAll();
      _driver->endScene();
    }
  _device->drop();
  return;
}
