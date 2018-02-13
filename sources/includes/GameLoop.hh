#ifndef _GAMELOOP_HH_
# define _GAMELOOP_HH_

#include <iostream>
#include <vector>
#include <ctime>
#include "Team.hh"
#include "EventHandler.hh"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sound.hh"

#include <fstream>
#ifndef _WIN32
	#include <unistd.h>
#else
	#include <Windows.h>
#endif
#include "IslandGenerator.hh"
#include "StringObject.hh"
#include "Rocket.hh"
#include "Bullet.hh"
#include "Drill.hh"
#include "Grenade.hh"
#include "Dynamit.hh"
#include "Log.hh"

//#define SIZE_MAX_X (600)
//#define SIZE_MAX_Y (200)
#define SIZE_MAX_X (1920)
#define SIZE_MAX_Y (1080)
#define SIZE_PLAYER (cubeSize * 2)

enum difficultyLevel
{
  EASY_GAME,
  MEDIUM_GAME,
  HARD_GAME,
};

class GameLoop
{
public:
	bool menuSet = true;
	bool exitGame = false;
	bool firstTimeNoMenu = false;
	bool mapMenuType = true;

  std::vector<std::vector<int> >  listPlayers;
  bool                            _debugRand = false;
  double                          _debugTimerGame = 0.0;
  //int                             _currentAngle = 180;
  //int                             _currentAngle = 90;
  int                             _tmpAngle = 90;
  bool                            _aff_cursor = false;
  std::vector<Rocket>             rocket;
  std::vector<Bullet>             bullet;
  std::vector<Drill>              drill;
  std::vector<Grenade>            grenade;
  std::vector<Dynamit>            dynamit;
  StringObject                    obj;
  difficultyLevel									difficulty = MEDIUM_GAME;
  Log                             lg;
  std::vector<Team>               &teams;

  bool debugStaticHud = false;
  bool loadMapMenu = false;


private:
  IslandGenerator                 island;
	Sound				  									sound;
	std::vector<std::vector<int> > 	listLifeScore;

  std::clock_t startGlobaleTime;
  std::clock_t startWormsTime;
  std::clock_t startWaitTime;
  std::clock_t startWaitTimeAfterAttack;
  std::clock_t startMenuTime;

  int                             _widhWorms;
  int                             _heightWorms;
  double                          wormsMaxTime = 32.0;
  double                          betweenWormsMaxTime = 4.0;
  int                             phase = 0;
  bool                            tmpDead = false;
  int                             nbPlayer = 0;
  bool                            _inventoryIsOpen = false;
  int                             _preselected = 0;
  int                             _menuSelection = 0;
  bool                            _paused = false;

public:
  GameLoop(std::vector<Team> &tea);
  virtual ~GameLoop();

  void initGame(bool);
  void initMap(TypeOfGenerator typeGen);
  void initTeams();
  void initDisplay(bool);
  void initListPlayer();

  //tmp
  void affListWorms();
  void affWormsOnMap();
  void writeLifePosition(unsigned int idTeam, unsigned int idWorms);
  void changeWindByTmp(unsigned int idTeam, unsigned int idWorms);
  void changeTmpByWind();
  //tmp

	int addToIa();
	int addToHuman();

	void changeLifeWorms();

  ///////////////////// GET / SET ////////////////////////
  void setGlobaleTime();
  void setWormsTime();
  void setWaitTime();
  void setWaitTimeAfterAttack();
  void setMenuTime();

  void setPhase(int phase);
  void setTmpDead(bool set);
  void setWormsPlayer(int worms);
  void setInventory(bool);
  void setPreselectedInventory(int);

  void setCurrentTimeWorms(int);
  void setPaused(bool);
  void setMenuSelection(int);

  std::clock_t getStartGlobaleTime() const;
  std::clock_t getStartWormsTime() const;
  std::clock_t getStartWaitTime() const;
  std::clock_t getStartWaitTimeAfterAttack() const;
  std::clock_t getStartMenuTime() const;

  double  getCurrentGlobalTime() const;
  double  getCurrentWaitTime() const;
  double  getCurrentTimeWorms() const;
  double  getCurrentTimeAfterAttackWorms() const;
  double  getCurrentMenuTime() const;

  double  getWormsMaxTime() const;
  double  getMaxTimeBetweenWorms() const;
  int     getPhase() const;
  bool    getTmpDead() const;
  int     getWormsPlayer() const;
  int     getWidthWorm() const;
  int     getHeightWorms() const;
  bool    getInventory() const;
  int     getPreselectedInventory() const;
  bool    getPaused() const;
  int     getMenuSelection() const;
  std::vector<std::vector<int> > &getListLifeScore();

  ////////////////////// Function //////////////////////
  bool deleteWormsFromListPlayer(unsigned int idTeam, unsigned int idWorms);
  Worms &getWormsFromGameLoop(int idTeam, int idWorms);
  void findWhoPlay();
  void setWhoIsPlaying();
  void nextWhoIsPlaying();
  bool posOfTwoWorms(int x1, int y1, int x2, int y2);
  bool testPosOfAllWorms(int x, int y, int idTeam, int idWorms);
  std::vector<int> allWormsInBox(int x1, int y1, int x2, int y2);
  bool testIfCurrentWormsAlive();
};

#endif /* !GAMELOOP_HH_ */
