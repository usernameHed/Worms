#include "Menu.hh"

Menu::Menu(Display &disp)
  : display(disp)
{
  isIntro = false;
}

Menu::~Menu()
{

}

int Menu::soundManager(std::string soundSource, bool loop)
{
  music.openFromFile(soundSource);
  music.play();
  music.setLoop(loop);
  this->tmpSizeVolume = 10;
  music.setVolume(this->tmpSizeVolume * 10);
  this->volumeSprite.clear();
  return (0);
}

IGUIImage* Menu::dispImg(std::string pathImg, bool isVisible, rect<s32> rectSize)
{
  IGUIImage* tmp;

  tmp = this->display.getEnv()->addImage(rectSize);
  tmp->setImage(display.getDriver()->getTexture(pathImg.c_str()));
  tmp->setVisible(isVisible);
  return (tmp);
}

void Menu::remove_menu()
{
  intro->remove();
  this->isIntro = false;
}

int Menu::intro_menu()
{
  //aff splash
  intro = dispImg("media/background/WWWormsV2.jpg", true, rect<s32>(0, 0, 1920, 1080));
  this->isIntro = true;
  //sound splash
  soundManager(SOUND_SPLASH, false);
  return (0);
}

void Menu::affFilter()
{
  core::rect<s32> menuPause = (core::rect<s32>(0, 0, 1920, 1080));
  hideAnimator = this->display.getEnv()->addWindow(menuPause, true, L"");
  hideAnimator->getCloseButton()->setVisible(false);
  hideAnimator->setDraggable(false);
  hideAnimator->setDrawTitlebar(false);
  for (s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
    {
      video::SColor col = this->display.getEnv()->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
      col.setAlpha(-300);
      this->display.getEnv()->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
    }
}

void Menu::affMenuTeam(bool isOpened)
{
  if (isOpened)
    {
      menuTeam = this->display.getEnv()->addImage(this->display.getDriver()->getTexture("media/menuteam/MenuTeam.png"), position2d<int>(0, 0));
      int test = 0;
      while (test != 4)
	{
	  Player(test, 0);
	  test++;
	}

      //init sprites
      int z = 0;
      int X = 0;
      int Y = 0;

      while (z != 4)
	{
	  int i = -1;
	  int x;
	  int y;
	  while (++i < 4)
	    {
	      steam st;
	      st.id = i;
	      st.nbWorms = (i < 2) ? 4 : 1;

	      int j = -1;
	      while (++j < st.nbWorms)
		{
		  y = WINDOW_SIZE_Y / 4.75 + ((WINDOW_SIZE_Y / 6.75) * i);
		  x = WINDOW_SIZE_X / 2.7 + ((WINDOW_SIZE_X / 30) * j);
		  st.worms.push_back(this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menut\
eam/worm.png"), position2d<int>(x, y)));
		}
	      this->gameTeam.push_back(st);
	      Y = WINDOW_SIZE_Y / 4.5 + ((WINDOW_SIZE_Y / 6.75) * z);
	      if (z == 0)
		playerSprite.push_back(this->display.getEnv()->addImage(display.getDriver()->getTexture("media/men\
uteam/player2.png"), position2d<int>(WINDOW_SIZE_X / 1.78, Y)));
	      else if (z == 1)
		playerSprite.push_back(this->display.getEnv()->addImage(display.getDriver()->getTexture("media/men\
uteam/player1.png"), position2d<int>(WINDOW_SIZE_X / 1.78, Y)));
	      else
		{
		  Y = WINDOW_SIZE_Y / 5.5 + ((WINDOW_SIZE_Y / 6.75) * z);
		  playerSprite.push_back(this->display.getEnv()->addImage(display.getDriver()->getTexture("media/m\
enuteam/player3.png"), position2d<int>(WINDOW_SIZE_X / 2.86, Y)));
		}
	      z++;
	    }
	}
      onSpriteSwitch(0, 4);
    }
  else
    {
      menuHome->remove();
      homeSelected->remove();
    }
  return;
}

void Menu::createDefaultTeam()
{
  this->display.removeAllWorms();
  this->display.getGame().teams.clear();

  int i = -1;
  while (++i < 4)
  {
    this->display.getGame().teams.push_back(Team(i));
    int j = -1;
    while (++j < 4)
      this->display.getGame().teams[i].addWorms(Worms(j, i, IA, "adolf", 100, LEFT));
  }
  this->display.getGame().difficulty = MEDIUM_GAME;
}

void Menu::addWorm(int toAdd, int nbButton)
{
  if (!isOff[nbButton])
    {
      if (nbButton < 0 || nbButton >= this->gameTeam.size())
	{
	  std::cout << "nbButton error !" << std::endl;
	  return;
	}
      if (this->gameTeam[nbButton].nbWorms + toAdd < 1 || this->gameTeam[nbButton].nbWorms + toAdd > 4)
	{
	  std::cout << "toAdd limit !" << std::endl;
	  return;
	}
      if (toAdd < 0)
	{
	  this->gameTeam[nbButton].worms[this->gameTeam[nbButton].nbWorms - 1]->remove();
	  this->gameTeam[nbButton].worms.erase(this->gameTeam[nbButton].worms.begin() + this->gameTeam[nbButton].nbWorms - 1);
	  this->gameTeam[nbButton].nbWorms--;
	}
      else
	{
	  int y = WINDOW_SIZE_Y / 4.75 + ((WINDOW_SIZE_Y / 6.75) * nbButton);
	  int x = WINDOW_SIZE_X / 2.7 + ((WINDOW_SIZE_X / 30) * this->gameTeam[nbButton].nbWorms);
	  this->gameTeam[nbButton].nbWorms++;
	  this->gameTeam[nbButton].worms.push_back(this->display.getEnv()->addImage(display.getDriver()->getTexture
										    ("media/menuteam/worm.png"), position2d<int>(x, y)));
	}
    }
}

void Menu::clearGame()
{
  this->display.removeAllWorms();
  this->display.getGame().teams.clear();

  int i = -1;
  while (++i < this->gameTeam.size())
    {
      int j = -1;
      if (this->playerType.size() < 1)
	{
	  std::cout << "what 0 ?" << std::endl;
	  exit(0);
	}
      if (this->playerType[i] != 3)//!OFF
	{
	  this->display.getGame().teams.push_back(Team(i));
	  while (++j < this->gameTeam[i].nbWorms)
	    {
	      if (playerType[i] == 1)
		this->display.getGame().teams[i].addWorms(Worms(j, i, IA, "adolf", 100, LEFT));
	      else if (playerType[i] == 2)
		this->display.getGame().teams[i].addWorms(Worms(j, i, HUMAN, "adolf", 100, LEFT));
	    }
	}
      else
	return;
    }
}

void Menu::deleteHUD()
{
  int i = -1;
  while (++i < this->gameTeam.size())
    {
      this->playerSprite[i]->remove();
      int j = -1;
      while (++j < this->gameTeam[i].nbWorms)
	{
	  this->gameTeam[i].worms[j]->remove();
	}
    }
}

void Menu::TeamActions(int nbButton, int event)
{
  int nbWorms = 0;

  if (event == ENTER)
    {
      this->menuHomePage = MAP_PAGE;
      this->deleteHUD();
      menuTeam->remove();
      homeSelected->remove();
      affMenuMap(true);
    }
  else if (event == LEFT_WORMS)
    this->addWorm(-1, nbButton);
  else if (event == RIGHT_WORMS)
    this->addWorm(1, nbButton);
  else if (event == INVENTORY)
    Player(nbButton, event);
}

void Menu::affMenuHome(bool isOpened)
{
  if (isOpened)
    {
       menuHome = this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menuhome/MenuHome.png"), position2d<int>(0, 0));
       onSpriteSwitch(0, 4);
    }
  else
    {
      menuHome->remove();
      homeSelected->remove();
    }
  return;
}

void Menu::eventHandler(int event, int buttonMax)
{
  static int nbButtonMenu = 0;
  static int isChangedM = menuHomePage;

  if (menuHomePage != isChangedM)
    {
      nbButtonMenu = 0;
      isChangedM = menuHomePage;
    }
  if (this->backToMenu)
    nbButtonMenu = 0;
  if (event == DOWN_MENU && nbButtonMenu == buttonMax - 1)
    nbButtonMenu = 0;
  else if (event == UP_MENU && nbButtonMenu == 0)
    nbButtonMenu = buttonMax - 1;
  else if (event == DOWN_MENU && nbButtonMenu <= buttonMax - 1)
    nbButtonMenu++;
  else if (event == UP_MENU && nbButtonMenu > 0)
    nbButtonMenu--;

  if (menuHomePage == HOME)
    HomeActions(nbButtonMenu, event);
  else if (menuHomePage == TEAM_PAGE)
    TeamActions(nbButtonMenu, event);
  else if (menuHomePage == SETTINGS)
    SettingsActions(nbButtonMenu, event);
  else if (menuHomePage == MAP_PAGE)
    MenuMapActions(nbButtonMenu, event);

  if (event != 0 && event != ENTER)
    {
      if (menuHomePage != MAP_PAGE)
	      homeSelected->remove();
      else
	      homeSelectedSpace->remove();
      this->onSpriteSwitch(nbButtonMenu, buttonMax);
    }
}

void Menu::affMenuSettings(bool isOpened)
{
  if (isOpened)
  {
    menuSettings = this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menusettings/MenuSettings.png"), position2d<int>(0, 0));
    if (this->display.getGame().difficulty == EASY_GAME)
	    difficultySprite = this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menusettings/difficulty1.png"), position2d<int>(WINDOW_SIZE_X / 1.86, WINDOW_SIZE_Y / 1.73));
    else if (this->display.getGame().difficulty == MEDIUM_GAME)
	    difficultySprite = this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menusettings/difficulty2.png"), position2d<int>(WINDOW_SIZE_X / 1.86, WINDOW_SIZE_Y / 1.73));
    else if (this->display.getGame().difficulty == HARD_GAME)
	    difficultySprite = this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menusettings/difficulty3.png"), position2d<int>(WINDOW_SIZE_X / 1.86, WINDOW_SIZE_Y / 1.73));
    else
	    difficultySprite = this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menusettings/difficulty1.png"), position2d<int>(WINDOW_SIZE_X / 1.86, WINDOW_SIZE_Y / 1.73));
    onSpriteSwitch(0, 3);

    int x = -1;
    this->spaceBetweenSound = 60;
    while (++x < this->tmpSizeVolume)
	    this->volumeSprite.push_back(this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menusettings/soundlevel.png"), position2d<int>(WINDOW_SIZE_X / 2.3 + (WINDOW_SIZE_X / this->spaceBetweenSound * x), WINDOW_SIZE_Y / 3.62)));
  }
  else
  {
    menuHome->remove();
    homeSelected->remove();
  }
  return;
}

void Menu::SettingsActions(int nbButton, int event)
{
  int nbWorms = 0;

  if (event == ENTER || event == ESCAPE)
    {
      this->menuHomePage = HOME;
      difficultySprite->remove();
      menuSettings->remove();
      homeSelected->remove();

	  int i = -1;
	  while (++i < this->volumeSprite.size())
	  {
		  this->volumeSprite[i]->remove();
	  }
	  this->volumeSprite.clear();
	  //volumeSprite
	

      affMenuHome(true);
    }
  if (event == RIGHT_WORMS && nbButton + 1 == 1)
    {
      if (this->volumeSprite.size() < 10)
      {
        this->volumeSprite.push_back(this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menusettings/soundlevel.png"), position2d<int>(WINDOW_SIZE_X / 2.3 + (WINDOW_SIZE_X / this->spaceBetweenSound * this->volumeSprite.size()), WINDOW_SIZE_Y / 3.62)));
        this->tmpSizeVolume = this->volumeSprite.size();
        music.setVolume(this->tmpSizeVolume * 10);
      }
    }
  else if (event == LEFT_WORMS && nbButton + 1 == 1)
    {
      if (this->volumeSprite.size() > 0)
      {
        this->volumeSprite[this->volumeSprite.size() - 1]->remove();
        this->volumeSprite.erase(this->volumeSprite.begin() + (this->volumeSprite.size() - 1));
        this->tmpSizeVolume = this->volumeSprite.size();
        music.setVolume(this->tmpSizeVolume * 10);
      }
    }
  if (nbButton + 1 == 3 && event != 0 && event != ENTER)
    {
      static int difficulty = 2;

      if (event == RIGHT_WORMS && difficulty < 3)
	  difficulty++;
      if (event == LEFT_WORMS && difficulty > 1)
      	difficulty--;

      if (difficulty == 1)
	this->display.getGame().difficulty = EASY_GAME;
      if (difficulty == 2)
	this->display.getGame().difficulty = MEDIUM_GAME;
      if (difficulty == 3)
	this->display.getGame().difficulty = HARD_GAME;

      std::string playerPath = "media/menusettings/difficulty" + std::to_string(difficulty) + ".png";
	  difficultySprite->remove();
	  difficultySprite = this->display.getEnv()->addImage(display.getDriver()->getTexture(playerPath.c_str()), position2d<int>(WINDOW_SIZE_X / 1.86, WINDOW_SIZE_Y / 1.73));
    }
}

void Menu::Player(int nbButton, int event)
{
  static std::vector<int> team;
  int           Y = 0;

  if (team.empty() && isOff.empty())
    {
      team.push_back(2);
      team.push_back(1);
      team.push_back(3);
      team.push_back(3);
      isOff.push_back(false);
      isOff.push_back(false);
      isOff.push_back(true);
      isOff.push_back(true);
    }
  if (team[nbButton] == 3 && event == INVENTORY && nbButton == 3 && isOff[2])
    team[nbButton] = 3;
  else if (team[nbButton] == 2 && event == INVENTORY && nbButton == 2 && !isOff[3])
    team[nbButton] = 1;
  else if (team[nbButton] == 1 && event == INVENTORY)
    team[nbButton] = 2;
  else if (team[nbButton] == 2 && event == INVENTORY && nbButton != 0 && nbButton != 1)
    team[nbButton] = 3;
  else if (team[nbButton] == 3 && event == INVENTORY && nbButton != 0 && nbButton != 1)
    team[nbButton] = 1;
  else if (team[nbButton] == 2 && event == INVENTORY && nbButton == 0 || nbButton == 1)
    team[nbButton] = 1;
  if (team[nbButton] == 3)
    isOff[nbButton] = true;
  else
    isOff[nbButton] = false;
  this->playerType.clear();
  this->playerType = team;
  if (event == INVENTORY && menuHomePage == TEAM_PAGE)
    {
      std::string playerS = std::to_string(team[nbButton]);
      std::string playerPath = "media/menuteam/player" + playerS + ".png";
      Y = WINDOW_SIZE_Y / 4.5 + ((WINDOW_SIZE_Y / 6.75) * nbButton);
      if (event == INVENTORY)
	{
	  playerSprite[nbButton]->remove();
	  if (team[nbButton] == 3)
	    {
	      Y = WINDOW_SIZE_Y / 5.5 + ((WINDOW_SIZE_Y / 6.75) * nbButton);
	      playerSprite[nbButton] = (this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menuteam/player3.png"), position2d<int>(WINDOW_SIZE_X / 2.86, Y)));
	    }
	  else
	    playerSprite[nbButton] = this->display.getEnv()->addImage(display.getDriver()->getTexture(playerPath.c_str()), position2d<int>(WINDOW_SIZE_X / 1.78, Y));
	}
    }
  return;
}

void Menu::HomeActions(int nbButton, int event)
{
  //actions des boutons home
  if (nbButton + 1 == 1 && event == ENTER)
    {
      this->menuHomePage = TEAM_PAGE;
      menuHome->remove();
      homeSelected->remove();
      if (mute == true)
	cutSound->remove();
      affMenuTeam(true);
      isChangedMenu = true;
    }
  if (nbButton + 1 == 2 && event == ENTER)
    {
      this->menuHomePage = MAP_LOAD;
      menuHome->remove();
      homeSelected->remove();
      if (mute == true)
	cutSound->remove();
      affMenuMap(false);
    }
  if (nbButton + 1 == 3 && event == ENTER)
    {
      this->menuHomePage = SETTINGS;
      menuHome->remove();
      homeSelected->remove();
      if (mute == true)
	cutSound->remove();
      affMenuSettings(true);
      isChangedMenu = true;
    }
  if (nbButton + 1 == 4 && event == ENTER)
    {
      music.stop();
      exit(-1);
    }
  if (event == MUTE && this->mute == false)
    {
      this->mute = true;
      cutSound = this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menuhome/cutSound.png"), position2d<int>(WINDOW_SIZE_X - (WINDOW_SIZE_X / 9), WINDOW_SIZE_Y / 18));
      music.setVolume(0);
    }
  else if (event == MUTE && this->mute == true)
    {
      this->mute = false;
      cutSound->remove();
      music.setVolume(this->tmpSizeVolume * 10);
    }
}

void Menu::onSpriteSwitch(int nbButton, int buttonMax)
{
  if (nbButton < buttonMax && nbButton >= 0)
    {
      int Y = 0;
      if (menuHomePage == HOME)
	Y = WINDOW_SIZE_Y / 3.35 + ((WINDOW_SIZE_Y / 6.38) * nbButton);
      else if (menuHomePage == TEAM_PAGE)
      	Y = WINDOW_SIZE_Y / 5.50 + ((WINDOW_SIZE_Y / 6.75) * nbButton);
      else if (menuHomePage == SETTINGS)
	Y = WINDOW_SIZE_Y / 4.20 + ((WINDOW_SIZE_Y / 6.75) * nbButton);
      else if (menuHomePage == MAP_PAGE)
	Y = WINDOW_SIZE_Y / 3.378 + ((WINDOW_SIZE_Y / 3.55) * nbButton);

      if (menuHomePage == MAP_PAGE)
	homeSelectedSpace = this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menumap/selected.png"), position2d<int>(WINDOW_SIZE_X / 2.37, Y));
      else
	homeSelected = this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menuhome/menuSelected.png"), position2d<int>(WINDOW_SIZE_X / 2.86, Y));
    }
  return;
}

void Menu::createMenu()
{
  static bool already = false;

  //volumeMusic = 60;
  this->playerSprite.clear();
  this->volumeSprite.clear();
  this->gameTeam.clear();
  this->playerType.clear();

  mute = false;
  menuHomePage = HOME;
  isMenuHome = true;
  this->affMenuHome(true);
  if (!already)
    this->intro_menu();
  already = true;
}

int Menu::getHomePage()
{
  return (menuHomePage);
}
void Menu::affMenuMap(bool isOpened)
{
 if (isOpened)
    {
      this->menuMap = this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menumap/MenuMap.png"), position2d<int>(0, 0));
      int Y = WINDOW_SIZE_Y / 3.378;
      homeSelectedSpace = this->display.getEnv()->addImage(display.getDriver()->getTexture("media/menumap/selected.png"), position2d<int>(WINDOW_SIZE_X / 2.378, Y));
    }
  else
    {
      this->display.getGame().loadMapMenu = true;
      //this->clearGame();
      ////////////////////////////////////////////////////
      /// defualt setup for laod map, may be laod previous player + life ?
      ///
      this->createDefaultTeam();

      this->display.getGame().menuSet = false;
    }
 return;
}

void Menu::MenuMapActions(int nbButton, int event)
{
  int nbWorms = 0;

  if (event == ENTER)
    {
      //music.stop();
      this->display.getGame().mapMenuType = nbButton;
      this->menuHomePage = 10;
      menuMap->remove();
      homeSelectedSpace->remove();
      this->clearGame();
      this->display.getGame().menuSet = false;
      this->display.getGame().initGame(false);
    }
}
