#include		"Weapons.hh"
#include "template.hh"
//#include "Display.hh"

Weapons::Weapons(GameLoop &game)
  : gameloop(game)
{
  this->fmap.clear();
  this->fmap[POUNCH] = &Weapons::pounch;
  this->fmap[FINGER] = &Weapons::finger;
  this->fmap[BASEBALL] = &Weapons::baseball;
  this->fmap[JUMPTHOUGHTWALL] = &Weapons::jumpThoughtWall;
  this->fmap[UZI] = &Weapons::uzi;
  this->fmap[SHOOTGUN] = &Weapons::shootgun;
  this->fmap[BAZOOKA] = &Weapons::bazooka;
  this->fmap[DYNAMIT] = &Weapons::dynamit;
  this->fmap[GRENADE] = &Weapons::grenade;
  this->fmap[DRILL] = &Weapons::drill;
}

Weapons::~Weapons()
{

}

bool Weapons::getCanUsWeapon() const
{
  return (this->_canUseWeapon);
}

void Weapons::setCanUseWeapon(bool can)
{
  this->_canUseWeapon = can;
}

void Weapons::attack()
{
  if (this->gameloop.getWormsPlayer() < 0 || this->gameloop.getWormsPlayer() >= this->gameloop.listPlayers.size())
    return;

  int idTeam = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][1];
  WeaponsType tmpWeaponType = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType();
  int nb_player = this->gameloop.getWormsPlayer();

  std::cout << "attack ! (type: " << tmpWeaponType << ") for player: " << nb_player << std::endl;

  (this->*fmap[tmpWeaponType])();
}

std::vector<int> Weapons::getIaHit(int x, int y, int nb_player, int right)
{
  if (nb_player < 0 || nb_player >= this->gameloop.listPlayers.size())
  {
    std::vector<int> tmpNull;
    return (tmpNull);
  }

  int idTeam = this->gameloop.listPlayers[nb_player][0];
  int idWorms = this->gameloop.listPlayers[nb_player][1];

  int x1;
  int x2;
  int y1 = y - (this->gameloop.getHeightWorms() * 2);
  int y2 = y + (this->gameloop.getHeightWorms() * 2);
  if (right == 1)
  {
    x1 = x + (this->gameloop.getWidthWorm() / 2);
    x2 = x + (this->gameloop.getWidthWorm() * 2);
  }
  else
  {
    x1 = x - (this->gameloop.getWidthWorm() * 2);
    x2 = x + (this->gameloop.getWidthWorm() / 2);
  }
  std::vector<int> allWormsTouch = this->gameloop.allWormsInBox(x1, y1, x2, y2);
  return (allWormsTouch);
}

bool Weapons::pounchHit(int damage, float velocity, int angle)
{
  if (this->gameloop.getWormsPlayer() < 0 || this->gameloop.getWormsPlayer() >= this->gameloop.listPlayers.size())
    return (false);

  int idTeam = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][1];

  int x1;
  int x2;
  int y1 = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y - (this->gameloop.getHeightWorms() * 2);
  int y2 = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y + (this->gameloop.getHeightWorms() * 2);
  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
  {
    x1 = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x + (this->gameloop.getWidthWorm() / 2);
    x2 = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x + (this->gameloop.getWidthWorm() * 2);
  }
  else
  {
    x1 = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x - (this->gameloop.getWidthWorm() * 2);
    x2 = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x + (this->gameloop.getWidthWorm() / 2);
  }
  std::vector<int> allWormsTouch = this->gameloop.allWormsInBox(x1, y1, x2, y2);
  if (allWormsTouch.size() == 0)
    return (false);
  printList(allWormsTouch, " ");
  int i = 0;
  while (i < allWormsTouch.size())
  {
    std::cout << "to pounch: " << allWormsTouch[i] << std::endl;
    if (allWormsTouch[i] < 0 || allWormsTouch[i] >= this->gameloop.listPlayers.size())
    {
      ++i;
      continue;
    }
    int tmpIdTeam = this->gameloop.listPlayers[allWormsTouch[i]][0];
    int tmpIdWorms = this->gameloop.listPlayers[allWormsTouch[i]][1];
    if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
    {
      this->gameloop.getWormsFromGameLoop(tmpIdTeam, tmpIdWorms).setVelocity(velocity, 90 - angle);
      this->gameloop.getWormsFromGameLoop(tmpIdTeam, tmpIdWorms).takeDamage(damage);
    }
    else
    {
      this->gameloop.getWormsFromGameLoop(tmpIdTeam, tmpIdWorms).setVelocity(velocity, 90 + angle);
      this->gameloop.getWormsFromGameLoop(tmpIdTeam, tmpIdWorms).takeDamage(damage);
    }
    ++i;
  }
  return (true);
}

void Weapons::pounch()
{
  std::cout << "pounch !" << std::endl;
  if (!this->pounchHit(25, 15.0, 20))
    return;
  this->_canUseWeapon = false;
}

void Weapons::finger()
{
    std::cout << "finger !" << std::endl;
    if (!this->pounchHit(3, 10.0, 20))
      return;
    this->_canUseWeapon = false;
}

void Weapons::baseball()
{
    std::cout << "baseball !" << std::endl;
    if (!this->pounchHit(30, 27.0, 40))
      return;
    this->_canUseWeapon = false;
}


void Weapons::jumpThoughtWall()
{
  if (this->gameloop.getWormsPlayer() < 0 || this->gameloop.getWormsPlayer() >= this->gameloop.listPlayers.size())
    return;
  if (this->jumpi != JUMP_NONE)
  {
    std::cout << "FUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU" << std::endl;
    return;
  }

  int idTeam = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][1];

  std::cout << "mega jump !" << std::endl;
  float velocityJump = 30.0;
  int angleRightJump = 60.0;
  int angleLeftJump = 120.0;

  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
    this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setVelocity(velocityJump, angleRightJump);
  else
    this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setVelocity(velocityJump, angleLeftJump);

  this->jumpi = JUMP_START;
  this->_canUseWeapon = false;
}

void Weapons::activeParachute()
{
  int nb_player = this->gameloop.getWormsPlayer();
  if (nb_player < 0 || nb_player >= this->gameloop.listPlayers.size())
  {
    std::cout << "active para what ??" << std::endl;
    return ;
  }
  if (this->jumpi == JUMP_FIST_FALL)
  {
    std::cout << "set parachute !" << std::endl;
    //TODO: change obj player to PARACHUTE


    this->jumpi = JUMP_FALL;
  }
  else if (this->jumpi == JUMP_NONE)
  {
    std::cout << "set normal !" << std::endl;
    //TODO: change obj player to NORMAL


  }
}

void Weapons::uzi()
{
  std::cout << "uzi !" << std::endl;
  this->numberAction = 0;
  this->numberMaxAction = 30;
  this->speed = 15;
  this->ray = 2;
  //this->_canUseWeapon = false;
}

void Weapons::drill()
{
  std::cout << "drill !" << std::endl;
  this->numberAction = 0;
  this->numberMaxAction = 20;
  this->speed = 5;
  this->ray = 5;
}

void Weapons::shootgun()
{
  std::cout << "shootgun !" << std::endl;
  this->numberAction = 0;
  this->numberMaxAction = 2;
  this->speed = 12;
  this->ray = 15;
  //this->_canUseWeapon = false;
}

void Weapons::setPosOfCursor()
{
  if (this->gameloop.getWormsPlayer() < 0 || this->gameloop.getWormsPlayer() >= this->gameloop.listPlayers.size())
    return;

    int idTeam = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][0];
    int idWorms = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][1];

  int x = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int y = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y;

  float xx = x;
  float yy = y;

  float vel = 50.0;
  //int angle =  this->gameloop._currentAngle;
  int angle = 0;
  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
    angle = 90 - this->gameloop._tmpAngle;
  else
    angle = 90 + this->gameloop._tmpAngle;

  float xvel = cos(angle / 180.0 * M_PI) * vel;
  float yvel = - sin(angle / 180.0 * M_PI) * vel;
  xx += xvel;
  yy += yvel;

  std::cout << "pos of worms: " << x << ":" << y << std::endl;
  std::cout << "pos Cursor: " << xx << ":" << yy << std::endl;
  //x = (int)xx;
  //y = (int)yy;
  this->xPos = (int)xx;
  this->yPos = (int)yy;
  this->setPosCursor = true;
}

void Weapons::addAngleCursor(int add)
{
  if (this->gameloop.getWormsPlayer() < 0 || this->gameloop.getWormsPlayer() >= this->gameloop.listPlayers.size())
    return;
  int idTeam = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][1];
  add *= -1;
  this->gameloop._tmpAngle += add;
  if (this->gameloop._tmpAngle < 0)
    this->gameloop._tmpAngle = 0;
  else if (this->gameloop._tmpAngle > 180)
    this->gameloop._tmpAngle = 180;

  std::cout << "angle: " << this->gameloop._tmpAngle << std::endl;
  this->gameloop._aff_cursor = true;
  this->setPosOfCursor();
}

void Weapons::affWeaponCursor(bool aff)
{
  this->gameloop._aff_cursor = aff;
  if (this->gameloop.getWormsPlayer() < 0 || this->gameloop.getWormsPlayer() >= this->gameloop.listPlayers.size()
      || !aff || !this->getCanUsWeapon())
  {
    std::cout << "hide cursor" << std::endl;
    this->xPos = 2000;
    this->yPos = 2000;
    this->setPosCursor = true;
    return;
  }
  std::cout << "display cursor" << std::endl;
  int idTeam = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][1];
  this->setPosOfCursor();
}

void Weapons::bazooka()
{
  std::cout << "bazooka !" << std::endl;
  this->ray = 50;
}

void Weapons::dynamit()
{
  std::cout << "dynamit !" << std::endl;
  this->_canUseWeapon = false;
}

void Weapons::grenade()
{
  std::cout << "grenade !" << std::endl;
  this->_canUseWeapon = false;
}
