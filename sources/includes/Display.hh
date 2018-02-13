#ifndef _DISPLAY_HH_
# define _DISPLAY_HH_

#include					<iostream>
#include					<vector>
#include					<irrlicht.h>
#include          <cmath>

#include					"EventHandler.hh"
#include          "IslandGenerator.hh"
#include          "StringObject.hh"
#include          "Sound.hh"

//TODO: Team.hh enleve ?
//#include          "Team.hh"

#include          "GameLoop.hh"
#include	        "Weapons.hh"
#include          "IaThinking.hh"


using namespace		irr;
using namespace		core;
using namespace		scene;
using namespace		video;
using namespace		io;
using namespace		gui;

#define WINDOW_SIZE_X 1920
#define WINDOW_SIZE_Y 1080

#define GRAVITY_WORMS (5)
#define MAX_UP_WORMS  (4)
#define RIGHT_WORMS   (1)
#define LEFT_WORMS    (2)
#define JUMP_WORMS    (3)
#define JUMP_UP_WORMS (4)
#define ZOOM_IN       (5)
#define ZOOM_OUT      (6)
#define INVENTORY     (7)
#define ENTER         (8)
#define ACTION        (9)
#define ESCAPE        (10)
#define UP_MENU       (11)
#define DOWN_MENU     (12)
#define MUTE          (13)

#define WAVE_HEIGHT   (0.1)
#define WAVE_SPEED    (300)
#define WAVE_LENGTH   (0.1)
#define WATER_TEXTURE "media/Textures/water2.jpg"
#define GROUND_WATER_TEXTURE "media/Textures/water2.jpg"

#define ZOOM_MAX (0.4)

#define MAX_FALL_HIT (20)
#define VELOCITY_JUMP (16)

enum MenuChoice
{
  RESUME_GAME,
  SAVE_AND_QUIT_GAME,
  QUIT_GAME,
};

class Menu;

class Display
{
public:

private:
  ///////////////////// Component Class ///////////////////////
  IslandGenerator                       &island;
  StringObject                          const &obj;
  std::vector<Team>                     &team;
  std::vector<std::vector<int> >        &listPlayers;
  GameLoop                              &gameloop;
  Menu                                  *menuHome;
  IaThinking                            iaPlay;
  Weapons                               *weapons;
  scene::ISceneNode*			              water;
  Sound				                           sound;

  ///////////////////// Variable ///////////////////////////////
  std::vector<int>                      finalPosCamera;
  float                                 cubeSize;
  int                                   currentTime;
  bool                                  yeahVictory = false;
  bool                                  hudHere = false;

  ///////////////////// IRLICHT //////////////////
  IrrlichtDevice*                        _device;
  IVideoDriver*				                   _driver;
  ISceneManager*	                       _smgr;
  IGUIEnvironment*                       _env;
  Event			                             _e;

  video::ITexture*                      _backGround;
  std::vector<IAnimatedMeshSceneNode*>  listObjPlayers;
  std::vector<ISceneNode*>              listLife;
  std::vector<unsigned int>             xVal;
  ICameraSceneNode *                    cam;
  scene::IAnimatedMeshSceneNode*        cube;
  std::vector<ISceneNode*>              irrMap;

  IGUIWindow*                           hide;
  IGUIImage*                            hud;
  IGUIImage*				                    menu;
  IGUIImage*				                    selected;
  IGUIImage*				                    inventoryDisp;
  IGUIImage*				                    nameSprite;
  IGUIImage*				                    inventorySelect;
  IGUIImage*				                    weaponSprite;
  IGUIImage*                            timerDisp;
  IGUIImage*                            timerDisp2;
  IGUIImage*                            lifeDisp;

  std::vector<IAnimatedMeshSceneNode*>   rocketObj;
  std::vector<IAnimatedMeshSceneNode*>   bulletObj;
  std::vector<IAnimatedMeshSceneNode*>   grenadeObj;
  std::vector<IAnimatedMeshSceneNode*>   dynamitObj;
  IAnimatedMeshSceneNode*                cursor;
  IAnimatedMeshSceneNode*                powerCursor;

  IAnimatedMeshSceneNode*                uzi_aff;
  IAnimatedMeshSceneNode*                bazooka_aff;
  IAnimatedMeshSceneNode*                shotgun_aff;
  IAnimatedMeshSceneNode*                grenade_aff;
  IAnimatedMeshSceneNode*                dynamite_aff;



public:
  ///////////////// display //////////////////////////
  Display(IslandGenerator &is, StringObject const &object, std::vector<Team> &tea, std::vector<std::vector<int> > &list, GameLoop &game);
  ~Display();
  int					                    InitWindow();
  IAnimatedMeshSceneNode*		      ObjCreate(std::string, std::string, core::vector3df);
  int		                          DispMap();
  int		                          DispWater(std::string);
  int		                          DispBackground(std::string);
  void                            loop();
  void		     	                  DrawAll();
  bool                            testIfWormsAlive(int nb_player);
  void                            timeLeft();
  IGUIImage*                      affNumb(int, float, float);
  void                            affTime(int timing);
  void                            affLifeHUD();
  void                            affWeaponsHUD();
  void                            affNameHUD();
  void                            initObject();
  void                            testVictory();
  void                            victory(int id);
  void                            DrawMenu();
  void                            DrawGame();

  /////////////////// set/get /////////////////////////
  GameLoop                        &getGame();
  IslandGenerator                 &getIsland();
  Weapons                         *getWeapons();
  IVideoDriver				            *getDriver();
  IGUIEnvironment                 *getEnv();


  /////////////////// Event /////////////////////////
  void                            catchPause();
  void                            catchLeave();
  int			                        eventCatcher();
  void                            actionUnique(int idTeam, int idWorms);
  void                            actionRepeat(int idTeam, int idWorms, bool isIa = false);
  void                            actionCursor(int idTeam, int idWorms);
  void                            changeScalePower(int change);

  /////////////////// other /////////////////////
  void					                  Spawn();
  void                            setLifeScale(int);
  int                             SpawnPlayer(int, int, int, int);
  int			                        replacePlayer(int, int, int);
  void                            removing(int nb_player);
  void                            removeAllWorms();
  void                            inventory();
  void                            moveInInventory(int move);
  void                            moveInMenu(int move);
  void                            selectInMenu();
  void                            debugTimerGame();
  void                            displayNbPlayer(int);
  bool							              checkNbPlayer(int nb_player);

  //////////////////// IA ///////////////////////////
  bool                            iaIsPlaying();
  void                            iaExportInfo();
  bool                            testLine(int x1, int y1, int x2, int y2);
  int                             sign(int x) const;
  void                            iaPlaying();
  void                            iaCac();
  void                            iaDirect();
  void                            iaIndirect();
  void                            iaNoLoSe();
  void                            hideWorms();
  bool                            testIfToMuchFalling(int x, int y);
  void                            iaJump();
  void                            iaMoveAfterJump();
  bool                            testIsGroundDown(int x, int y);

  ////////////////// physics  /////////////////
  bool                            testFallingHit(int);
  void					                  GravityWorms(int);
  void                            setForceWorms(int worms);
  bool                            changeHoriz(int, int, int, int, int);
  bool                            jump(int, int, int, int, int);
  bool                            testIfWormsInWater(int nb_player, int X, int Y);
  bool                            testIfIsFalling(int X, int Y, int nb_player);
  void                            objectPhysics();
  bool                            testHitObject(int x, int y, int r);
  bool                            applyForceHole(int x, int y, int r, bool autoTo);
  int                             testHitWorms(int x, int y);

  ///////////////// camera //////////////////
  void                            CameraManager();
  void                            setCameraPosition();
  void                            setNewCameraPos(float x, float y, float z);
  void                            zoomIn(float);
  void                            setZoomPlayer();

  ///////////////// Weapons //////////////////
  void                            displayWeaponType();
  void                            createObjectWeapon(int x, int y, int angle, int power);
  void                            affCursorAfter();
  void                            reactualiseMap();
  void                            dynamity(int x, int y);
  void                            explodeDynamo();
  void                            setWeaponToPlayer(int, bool);

  ///////////////// inventory && menu //////////////////
  void                            displayInventory();
  void                            affMenuPause(bool);
  void                            onSpriteSwitch(int);
  void				                    dispSelectedWeapon();

};

#endif /* !DISPLAY_HH_ */
