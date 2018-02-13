#ifndef _MENU_HH_
# define _MENU_HH_

#include <sys/types.h>
#include <signal.h>
#include <irrlicht.h>
#include "driverChoice.h"
#include "EventHandler.hh"
#include "Team.hh"
#include "Display.hh"
#include <vector>
#ifndef _WIN32
  #include <unistd.h>
#else
  #include <Windows.h>
#endif
#include <SFML/Audio.hpp>

#define SOUND_SPLASH "media/SFX/gameSound.wav"

#define HOME 0
#define MAP_PAGE 1
#define TEAM_PAGE 2
#define MAP_LOAD 3
#define SETTINGS 4

struct steam
{
  int id;
  int nbWorms;
  std::vector<IGUIImage*> worms;
};

class Menu
{
public:
  bool		backToMenu = false;
  bool		isChangedMenu = false;
  bool		isIntro;
  bool		mute;
  IGUIImage*    intro;
  bool		isMenuHome;

private:
  std::vector <bool>            isOff;
  std::vector<IGUIImage*> playerSprite;
  std::vector<IGUIImage*> volumeSprite;
  int                     tmpSizeVolume;
  int                     spaceBetweenSound;

  IGUIWindow*   hideAnimator;
  IGUIImage*    menuHome;
  IGUIImage*    menuTeam;
  IGUIImage*    menuMap;
  IGUIImage*    menuSettings;
  IGUIImage*    homeSelected;
  IGUIImage*    homeSelectedSpace;
  IGUIImage*    cutSound;
  IGUIImage*	worms;
  IGUIImage*   difficultySprite;
  std::vector<steam> gameTeam;

  // std::vector<IGUIImage*> wormsSprites;
  // std::vector<IGUIImage*> wormsSprites1;
  // std::vector<IGUIImage*> wormsSprites2;
  // std::vector<IGUIImage*> wormsSprites3;

  //  std::vector<std::vector<IGUIImage*> >	listTeamWorms;
  sf::Music	                music;
  Display	                  &display;
  IrrlichtDevice            *device;
  IGUISkin                  *skin;

  std::vector<int>          playerType;
  int		                    menuHomePage;

public:
  Menu(Display &disp);
  ~Menu();
  IGUIImage* dispImg(std::string, bool, rect<s32>);
  void affMenuHome(bool);
  void affMenuTeam(bool);

  void affMenuMap(bool);
  void MenuMapActions(int,int);

  void affMenuSettings(bool);
  void affFilter();
  void HomeActions(int, int);
  void TeamActions(int, int);
  void SettingsActions(int, int);
  void fillSpritesPlayer(int, int);
  void removeSpritesPlayer(int, int);
  void onSpriteSwitch(int, int);
  void Player(int, int);
  void affPlayerPerTeam(int, int);
  void playerPerTeam(int, int);
  int createWindow();
  void createMenu();
  int intro_menu();
  void remove_menu();
  void eventHandler(int, int);
  int  soundManager(std::string, bool);
  void hideElement();
  void jumpToTeamSelection();
  void aff();
  int getHomePage();

  void addWorm(int, int);
  void deleteHUD();
  void clearGame();
  void createDefaultTeam();
};


#endif /* !MENU_HH */
