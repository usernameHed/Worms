#include "Worms.hh"

static std::string	wormsNames[] = {"Benjamin","Ugo","Illiasse","Dany","Arthur","Thomas",
				"Edouard","Karim","Sylvie","Marie","Flore","ThomasFraisse",
				"Nicolas","Emanuel","Samuel","Yamine"};

Worms::Worms(unsigned int id, unsigned int idTeam,
            wormsType type,
            std::string name, unsigned int life,
            Direction dir)
  : _health(life), _name(name), _id(id), _idTeam(idTeam),
    _type(type), _direction(dir)
{
  this->_name = wormsNames[((idTeam * 4) + (id + 1)) - 1];
  std::cout << "Creating new Worms with id [" << id << "] and called [" << this->_name << "]" << std::endl;
  this->_force.XPos = 0;
  this->_force.YPos = 0;
  this->_force.vel = 0;
  this->_force.angl = 90;
  this->_force.XVel = cos(this->_force.angl / 180.0 * M_PI) * this->_force.vel;
  this->_force.YVel = - sin(this->_force.angl / 180.0 * M_PI) * this->_force.vel;
}

Worms::~Worms()
{

}

void Worms::setVelocity(float velo, int angle)
{
  if (angle != -1)
    this->_force.angl = angle;
  this->_force.vel = velo;
  this->_force.XVel = cos(this->_force.angl / 180.0 * M_PI) * this->_force.vel;
  this->_force.YVel = - sin(this->_force.angl / 180.0 * M_PI) * this->_force.vel;
}


void Worms::addVelocity(float velo, int angle)
{
  if (angle != -1)
    this->_force.angl = angle;
  this->_force.vel += floor(velo);
  if (this->_force.vel < 0)
    this->_force.vel = 0;
  this->_force.XVel = cos(this->_force.angl / 180.0 * M_PI) * this->_force.vel;
  this->_force.YVel = - sin(this->_force.angl / 180.0 * M_PI) * this->_force.vel;
}

float Worms::getVelocity() const
{
  return (static_cast<float>(this->_force.vel));
}

bool Worms::getPlaying() const
{
  return (this->isPlaying);
}

void Worms::setPlaying(bool play)
{
  this->isPlaying = play;
}

unsigned int Worms::getWidth() const
{
  return (this->_widhWorms);
}

unsigned int Worms::getHeight() const
{
  return (this->_heightWorms);
}

void Worms::setWidth(unsigned int width)
{
  this->_widhWorms = width;
}

void Worms::setHeight(unsigned int height)
{
  this->_heightWorms = height;
}

std::string Worms::getName() const
{
  return (this->_name);
}

unsigned int Worms::getId() const
{
  return (this->_id);
}

unsigned int Worms::getIdTeam() const
{
  return (this->_idTeam);
}

void Worms::setDirection(Direction dir)
{
  this->_direction = dir;
}

Direction Worms::getDirection() const
{
  return (this->_direction);
}

wormsType Worms::getType() const
{
  return (this->_type);
}

Life Worms::getLife() const
{
  return (this->_health);
}

void Worms::setPos(int x, int y)
{
  this->_pos.x = x;
  this->_pos.y = y;
  this->_force.XPos = x;
  this->_force.YPos = y;
}

Position Worms::getPos() const
{
  return (this->_pos);
}

Force Worms::getForce() const
{
  return (this->_force);
}

bool Worms::getAlive() const
{
  return (this->_alive);
}

void Worms::setPv(int pv)
{
  this->_health._pv = pv;
  if (this->_health._pv <= 0)
    this->_health._pv = 0;
}

WeaponsType       Worms::getWeaponsType() const
{
  return (this->_weaponsType);
}

void Worms::setWeaponsType(const WeaponsType &weap)
{
  this->_weaponsType = weap;
}

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

bool Worms::takeDamage(int damage)
{
  this->setPv(this->_health.getPv() - damage);
  std::cout << "new pv:" << this->_health.getPv() << std::endl;
  if (this->testDeath())
  {
    this->lifePosition();
    return (true);
  }
  this->lifePosition();
  return (false);
}

bool Worms::testDeath()
{
  if (!this->_health.isAlive())
  {
    this->_alive = false;
    std::cout << "worms[" << this->_id << "] of team[" << this->_idTeam << "] is dead !!" << std::endl;
    return (false);
  }
  return (true);
}

void Worms::lifePosition()
{
  //here set life position and slidebare position !!!
  int tmpX = this->_pos.x;
  int tmpY = this->_pos.y - this->_heightWorms * 2;
  this->_health.setPosLife(tmpX, tmpY);

  int tmpX1 = this->_pos.x - this->_heightWorms;
  int tmpY1 = this->_pos.y - this->_heightWorms - (this->_heightWorms / 2);
  int tmpX2 = tmpX1;
  int tmpY2 = tmpY1 + 1;

  int maxLenght = (this->_pos.x + this->_heightWorms) - tmpX1;
  //100 = maxLent;
  //this->_health.getPv() * maxLent / 100
  maxLenght = (this->_health.getPv() * maxLenght / 100 > maxLenght) ? maxLenght : this->_health.getPv() * maxLenght / 100;

  std::cout << "maLenght:" << maxLenght << std::endl;
  tmpX2 += maxLenght;
  this->_health.setSlideLifePos(tmpX1, tmpY1, tmpX2, tmpY2);
}

bool Worms::move()
{
  //change worms position

  //after move, set position of life and slidebare  depending of worms position !
  this->lifePosition();

  //display here or after function move();
  return (true);
}
