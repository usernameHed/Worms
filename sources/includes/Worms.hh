#ifndef _WORMS_HH_
# define _WORMS_HH_

#include "Life.hh"
#include "Position.hh"

#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

enum wormsType
{
  IA = 0,
  HUMAN = 1
};

enum Direction
{
  LEFT = 0,
  RIGHT = 1
};

enum		WeaponsType
{
  POUNCH,
  FINGER,
  BASEBALL,
  JUMPTHOUGHTWALL,
  UZI,
  SHOOTGUN,
  BAZOOKA,
  DYNAMIT,
  GRENADE,
  DRILL,
  NONE,
};

class Worms
{
public:
  Force             _force;
  int               _falling = 0;
  bool              _passThroughtWall = false;

protected:
  Life              _health;
  std::string       _name;
  unsigned int      _id;
  unsigned int      _idTeam;
  wormsType         _type;
  Direction         _direction;
  Position          _pos;
  unsigned int      _widhWorms;
  unsigned int      _heightWorms;

  bool              _alive = true;
  bool              isPlaying = false;
  WeaponsType       _weaponsType = POUNCH;

public:
  Worms(unsigned int id = 0, unsigned int idTeam = 0,
        wormsType type = HUMAN,
        std::string name = "Bobby", unsigned int life = 100,
        Direction rot = LEFT);
  virtual ~Worms();

  std::string       getName() const;
  unsigned int      getId() const;
  unsigned int      getIdTeam() const;
  Life              getLife() const;
  //Stuff             getStuff() const;
  wormsType         getType() const;
  Position          getPos() const;
  Force             getForce() const;
  Direction         getDirection() const;
  unsigned int      getWidth() const;
  unsigned int      getHeight() const;
  bool              getAlive() const;
  bool getPlaying() const;
  WeaponsType       getWeaponsType() const;


  void setPlaying(bool play);
  void setPos(int x, int y);
  void setDirection(Direction dir);
  void setWidth(unsigned int width);
  void setHeight(unsigned int height);
  void setPv(int pv);
  void setWeaponsType(const WeaponsType &weap);

  void lifePosition();
  bool takeDamage(int damage);
  bool testDeath();
  bool move();

  void addVelocity(float velo, int angle);
  void setVelocity(float velo, int angle);
  float getVelocity() const;
};

#endif/* !WORMS_HH_ */
