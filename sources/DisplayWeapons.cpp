#include		"driverChoice.h"

#include		"Display.hh"
#include "Rocket.hh"
#include "Bullet.hh"
#include "Drill.hh"
#include "Dynamit.hh"
#include "template.hh"

void Display::displayWeaponType()
{
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
		return;

  int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];
  int weaponType = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType();
  int nb_player = this->gameloop.getWormsPlayer();

  if (this->weapons->getCanUsWeapon())
  {
    this->setWeaponToPlayer(this->gameloop.getWormsPlayer(), true);
    //TODO:display GUI text of type weapon (set to X, Y)
    std::cout << "display type " << weaponType << " of player: " << nb_player << std::endl;
    if (weaponType == BAZOOKA || weaponType == UZI
        || weaponType == SHOOTGUN || weaponType == DRILL)
    {
      this->weapons->affWeaponCursor(true);
    }

  }
  else
  {
    //hide GUI text
    this->setWeaponToPlayer(this->gameloop.getWormsPlayer(), false);
    std::cout << "hide type " << weaponType << " of player: " << nb_player << std::endl;
    this->weapons->affWeaponCursor(false);
  }
}

void Display::dynamity(int x, int y)
{
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
		return;
  int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];

  Dynamit dyn(x, y);
  this->gameloop.dynamit.push_back(dyn);

  float X = (static_cast<float>(x) * (float)0.0266) - (float)25.4;
  float Y = (float)-14.0 + (static_cast<float>(y) * (float)0.0266);

  scene::IAnimatedMeshSceneNode* cat = this->ObjCreate("media/objs/Dynamite.obj", "", core::vector3df(X, -Y, 19.5f));
 // scene::IAnimatedMeshSceneNode* cat = this->ObjCreate("media/worm/worm.obj", "media/green.jpg", core::vector3df(10, 1, 19.5f));
  cat->setScale(core::vector3df(SIZE_PLAYER, SIZE_PLAYER, SIZE_PLAYER));

  std::cout << "x:" << x << ":" << y << std::endl;
  std::cout << "created" << std::endl;
  this->dynamitObj.push_back(cat);
}

void Display::createObjectWeapon(int x, int y, int angle, int power)
{
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
		return;
  int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];
  y -= this->gameloop.getHeightWorms() / 2;

  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == BAZOOKA)
  {
    Rocket rock(x, y, angle, power);
    this->gameloop.rocket.push_back(rock);

    float X = (static_cast<float>(x) * (float)0.0266) - (float)25.4;
    float Y = (float)-14.0 + (static_cast<float>(y) * (float)0.0266);

    scene::IAnimatedMeshSceneNode* cat = this->ObjCreate("media/objs/missile.obj", "", core::vector3df(X, -Y, 19.5f));
   // scene::IAnimatedMeshSceneNode* cat = this->ObjCreate("media/worm/worm.obj", "media/green.jpg", core::vector3df(10, 1, 19.5f));
    cat->setScale(core::vector3df(SIZE_PLAYER, SIZE_PLAYER, SIZE_PLAYER));

    std::cout << "x:" << x << ":" << y << std::endl;
    std::cout << "created" << std::endl;
    this->rocketObj.push_back(cat);
  }
  else if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == GRENADE)
  {
    Grenade gren(x, y, angle, power);
    this->gameloop.grenade.push_back(gren);
    float X = (static_cast<float>(x) * (float)0.0266) - (float)25.4;
    float Y = (float)-14.0 + (static_cast<float>(y) * (float)0.0266);
    scene::IAnimatedMeshSceneNode* cat = this->ObjCreate("media/objs/Grenade.obj", "", core::vector3df(X, -Y, 19.5f));
    cat->setScale(core::vector3df(SIZE_PLAYER, SIZE_PLAYER, SIZE_PLAYER));
    std::cout << "x:" << x << ":" << y << std::endl;
    std::cout << "created" << std::endl;
    this->grenadeObj.push_back(cat);
  }
  else if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == SHOOTGUN
            || this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == UZI)
  {
    Bullet bullet(x, y, angle, power);
    bullet.setSpeed(3 + rand() % 6);
    this->gameloop.bullet.push_back(bullet);

    float X = (static_cast<float>(x) * (float)0.0266) - (float)25.4;
    float Y = (float)-14.0 + (static_cast<float>(y) * (float)0.0266);

    scene::IAnimatedMeshSceneNode* cat = this->ObjCreate("media/objs/bullet.obj", "", core::vector3df(X, -Y, 19.5f));
   // scene::IAnimatedMeshSceneNode* cat = this->ObjCreate("media/worm/worm.obj", "media/green.jpg", core::vector3df(10, 1, 19.5f));
    cat->setScale(core::vector3df(0.0005f, 0.0005f, 0.0005f));
    cat->setRotation(core::vector3df(cat->getRotation().X, cat->getRotation().Y, 90.0f));

    std::cout << "x:" << x << ":" << y << std::endl;
    std::cout << "created" << std::endl;
    this->bulletObj.push_back(cat);
  }
  else if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == DRILL)
  {
    Drill drill(x, y, angle, power);
    this->gameloop.drill.push_back(drill);
  }
}

void Display::changeScalePower(int change)
{
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
		return;
  if (!this->weapons->getCanUsWeapon())
    change = 2;
  if (change == 0)
  {
    int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
    int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];
    int tmpX = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x;
    int tmpY = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y;
    float X = (static_cast<float>(tmpX) * (float)0.0266) - (float)25.4;
    float Y = (float)-14.0 + (static_cast<float>(tmpY) * (float)0.0266);
    this->powerCursor->setPosition(core::vector3df(X, -Y, this->powerCursor->getPosition().Z));
    if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
      this->powerCursor->setRotation(core::vector3df(this->powerCursor->getRotation().X, this->powerCursor->getRotation().Y, 180 - this->gameloop._tmpAngle));
    else
      this->powerCursor->setRotation(core::vector3df(this->powerCursor->getRotation().X, this->powerCursor->getRotation().Y, 180 + this->gameloop._tmpAngle));
  }
  else if (change == 1)
  {
    this->powerCursor->setScale(core::vector3df(0.1f, this->weapons->_powerWeapon * 0.04f, 0.04f));
  }
  else
  {
    this->powerCursor->setScale(core::vector3df(0.1f, 0.04f, 0.04f));
    this->powerCursor->setPosition(core::vector3df(100, 100, this->powerCursor->getPosition().Z));
  }
}

void Display::affCursorAfter()
{
  if (this->weapons->setPosCursor)
  {
    std::cout << "setCursor FUUUUUUUUUUUU" << this->weapons->xPos << ":" << this->weapons->yPos << std::endl;
    float X = (static_cast<float>(this->weapons->xPos) * (float)0.0266) - (float)25.4;
    float Y = (float)-14.0 + (static_cast<float>(this->weapons->yPos) * (float)0.0266);
    std::cout << X << ":" << Y << std::endl;
    this->cursor->setPosition(core::vector3df(X, -Y, this->cursor->getPosition().Z));

    if (this->checkNbPlayer(this->gameloop.getWormsPlayer()))
    {
      //int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
      //int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];
      this->setWeaponToPlayer(this->gameloop.getWormsPlayer(), true);
    }
    this->weapons->setPosCursor = false;
  }
}

void Display::reactualiseMap()
{
  std::cout << "actualise !" << std::endl;
  this->gameloop.obj.makeStringObject(this->island);
  this->DispMap();
}


int Display::testHitWorms(int x, int y)
{
  int wo = 0;
  while (static_cast<unsigned int>(wo) < this->listPlayers.size())
  {
    if (!this->checkNbPlayer(wo))
    {
      ++wo;
      continue;
    }

    int idTeam = this->listPlayers[wo][0];
    int idWorms = this->listPlayers[wo][1];

    if (x == this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x
        && y == this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y - (this->gameloop.getHeightWorms() / 2))
      return (wo);

    /*int i = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x - (this->gameloop.getWidthWorm());
    int j;
    while (i < this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x + (this->gameloop.getWidthWorm()))
    {
      j = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y - (this->gameloop.getHeightWorms());
      while (j < this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y + (this->gameloop.getHeightWorms()))
      {
        if (i == x && j == y)
          return (wo);
        ++j;
      }
      ++i;
    }*/
    ++wo;
  }
  return (-1);
}

bool Display::applyForceHole(int x1, int y1, int r, bool autoTo)
{
  if (static_cast<unsigned int>(x1) < 0 || static_cast<unsigned int>(x1) >= this->island.getSizeX() - 1)
    return (true);
  if (static_cast<unsigned int>(y1) < 0 || static_cast<unsigned int>(y1) >= this->island.getSizeY() - 1)
    return (true);

  bool hitGround = false;
  std::vector<int> wormsHit;
  int rr = r;
  for(int y = -rr ; y <= rr ; y++)
  {
    for(int x = -rr ; x <= rr ; x++)
    {
      if (x * x + y * y <= rr * rr)
      {
        int tmp = testHitWorms(x1 + x, y1 + y);
        if (std::find(wormsHit.begin(), wormsHit.end(), tmp) != wormsHit.end())
        {
          // found value in vec

        }
        else if (tmp != -1)
        {
          if (!this->checkNbPlayer(tmp))
        	   continue;
          int idTeam = this->listPlayers[tmp][0];
          int idWorms = this->listPlayers[tmp][1];


          if (!autoTo)
          {
            if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
          	   continue;
            int idTeamPlayer = this->listPlayers[this->gameloop.getWormsPlayer()][0];
            if (idTeamPlayer == idTeam)
            {
              wormsHit.push_back(tmp);
              continue;
            }
          }
          float dist = sqrt( pow((static_cast<float>(x1) + (float)x) - static_cast<float>(x1), (float)2.0) + pow((static_cast<float>(y1) + (float)y) - static_cast<float>(y1), (float)2.0));
          std::cout << "fuck the worms: " << tmp << " and hit: " << (r - (int)dist) * 2 << std::endl;

          float angleProject = atan2 ((static_cast<float>(y1) + (float)y) - static_cast<float>(y1), (static_cast<float>(x1) + (float)x) - static_cast<float>(x1)) * (float)180.0 / (float)M_PI;
          std::cout << "angleToHit: " << angleProject << std::endl;
          this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setVelocity((static_cast<float>(r) - dist) / (float)2.0, (int)angleProject + 90);
          this->gameloop.getWormsFromGameLoop(idTeam, idWorms).takeDamage((r - (int)dist) * 2);
          wormsHit.push_back(tmp);
        }
      }
    }
  }
  return (hitGround);
}
