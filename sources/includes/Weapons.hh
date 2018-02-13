#ifndef		_WEAPONS__
#define		_WEAPONS__

#include <iostream>
#include <vector>
#include "GameLoop.hh"

enum		JumpParachute
{
  JUMP_START,
  JUMP_FIST_FALL,
  JUMP_FALL,
  JUMP_NONE,
};

class		Weapons
{
public:
  GameLoop          &gameloop;
  int               power = 1;
  JumpParachute     jumpi = JUMP_NONE;
  int               _powerWeapon = 0;
  int               _maxPowerWeapon = 100;
  int               xPos = 0;
  int               yPos = 0;
  bool              setPosCursor = false;
  int               numberAction = 0;
  int               numberMaxAction = 2;
  float             speed = 10.0;
  int               ray = 10;

private:
  bool _canUseWeapon = false;
  typedef void (Weapons::*MFPP)();
  std::map <WeaponsType, MFPP> fmap;

public:
  Weapons(GameLoop &game);
  virtual ~Weapons();

  bool getCanUsWeapon() const;
  void setCanUseWeapon(bool);

  void attack();

  bool pounchHit(int damage, float velocity, int angle);
  std::vector<int> getIaHit(int x, int y, int nb_player, int right);

  void pounch();
  void finger();
  void baseball();

  void jumpThoughtWall();
  void activeParachute();
  void uzi();
  void shootgun();
  void bazooka();
  void dynamit();
  void grenade();
  void drill();

  void affWeaponCursor(bool aff);
  void setPosOfCursor();
  void addAngleCursor(int add);
};

#endif
