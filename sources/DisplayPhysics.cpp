#include		"driverChoice.h"

#include		"GameLoop.hh"
#include "Hole.hh"
#include		"Display.hh"

bool Display::changeHoriz(int X, int Y, int idTeam, int idWorms, int decale)
{
  /////////////////// don't turn if is falling !
  int z = Y;
  while (z + 1 < this->island.getSizeY() - 1 && (!(this->island.isDestructible(this->island.getMapping(X, z))))
   && z < Y + GRAVITY_WORMS && this->gameloop.testPosOfAllWorms(X, z, idTeam, idWorms))
    {
      ++z;
      if (z >= this->island.getSizeY() - 2)
       break;
    }
  if (z - Y >= GRAVITY_WORMS && this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() != JUMPTHOUGHTWALL)
    return (false);
  if (z - Y >= GRAVITY_WORMS && this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == JUMPTHOUGHTWALL)
  {
    int more = 2;
    if (decale < 0)
      decale -= more;
    else if (decale > 0)
      decale += more;
  }

  /*if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == JUMPTHOUGHTWALL)
    decale += 2;*/
  ///////////////////// catch right/left
  int cpt = 0;
  z = Y;
  while ((this->island.isDestructible(this->island.getMapping(X + decale, z))))
  {
    ++cpt;
    --z;
  }
  if (!this->gameloop.testPosOfAllWorms(X + decale, Y - (this->gameloop.getHeightWorms() / 2), idTeam, idWorms))
    cpt = MAX_UP_WORMS + 1;

  bool tmpOk = false;
  if (cpt <= MAX_UP_WORMS)
  {
    replacePlayer(X + decale, z, this->gameloop.getWormsPlayer());
    this->setZoomPlayer();
    tmpOk = true;
  }
  if (decale > 0)
  {
    this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setDirection(RIGHT);
    listObjPlayers[this->gameloop.getWormsPlayer()]->setRotation(vector3df(0, 90, 0));
  }
  else
  {
    this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setDirection(LEFT);
    listObjPlayers[this->gameloop.getWormsPlayer()]->setRotation(vector3df(0, 270, 0));
  }
  this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._falling = 0;
  return (tmpOk);
}

bool Display::testIfIsFalling(int X, int Y, int nb_player)
{
  if (!this->checkNbPlayer(nb_player))
	  return (false);

  int idTeam = this->listPlayers[nb_player][0];
  int idWorms = this->listPlayers[nb_player][1];

  int z = 0;

  z = Y;
  while (z + 1 < this->island.getSizeY() - 1 && (!(this->island.isDestructible(this->island.getMapping(X, z))))
  && z < Y + GRAVITY_WORMS && this->gameloop.testPosOfAllWorms(X, z, idTeam, idWorms))
  {
    ++z;
    if (z >= this->island.getSizeY() - 2)
    break;
  }
  if (z - Y >= GRAVITY_WORMS)
    return (false);
  return (true);
}

bool Display::jump(int X, int Y, int idTeam, int idWorms, int type)
{
  if (!this->testIfIsFalling(X, Y, this->gameloop.getWormsPlayer()))
    return (false);
  if (!this->testFallingHit(this->gameloop.getWormsPlayer()))
    return (false);
  if (!this->testIfWormsInWater(this->gameloop.getWormsPlayer(), X, Y + 1))
    return (false);

  this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._falling = 0;

  float velocityJump = 12.0;
  float velocityJumpUp = 15.0;
  int angleRightJump = 60;
  int angleRightJumpUp = 95;
  int angleLeftJump = 120;
  int angleLeftJumpUp = 80;

  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
  {
    if (type == JUMP_WORMS)
      this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setVelocity(velocityJump, angleRightJump);
    else if (type == JUMP_UP_WORMS)
      this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setVelocity(velocityJumpUp, angleRightJumpUp);
  }
  else
  {
    if (type == JUMP_WORMS)
      this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setVelocity(velocityJump, angleLeftJump);
    else if (type == JUMP_UP_WORMS)
      this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setVelocity(velocityJumpUp, angleLeftJumpUp);
  }
  return (true);
}

bool    Display::testFallingHit(int nb_player)
{
	if (!this->checkNbPlayer(nb_player))
		return (false);
  int idTeam = this->listPlayers[nb_player][0];
  int idWorms = this->listPlayers[nb_player][1];

  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._falling > MAX_FALL_HIT && this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() != JUMPTHOUGHTWALL)
  {
    int tmpAddFalling = (this->gameloop.difficulty != HARD_GAME) ?
      1 : (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getType() == HUMAN) ? 2 : 1;

    if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).takeDamage(this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._falling * tmpAddFalling))
    {
      if (this->gameloop.getWormsPlayer() == nb_player)
        this->gameloop.setPhase(3);
    }
    else
      removing(nb_player);
    return (false);
  }

  /////////////////////////////////// for jump
  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == JUMPTHOUGHTWALL
      && this->weapons->jumpi == JUMP_FALL && nb_player == this->gameloop.getWormsPlayer())
    {
      std::cout << "WHAT ??? testFallHit" << std::endl;
      this->weapons->jumpi = JUMP_NONE;
      this->weapons->activeParachute();
      this->displayWeaponType();
      this->gameloop.setPhase(4);
      this->gameloop.setWaitTimeAfterAttack();
      this->gameloop._debugTimerGame = 0.0;
    }
  return (true);
}

bool Display::testIfWormsInWater(int nb_player, int X, int Y)
{
  if (this->island.getMapping(X, Y) == WATER || Y >= this->island.getSizeY() - 3)
  {
    removing(nb_player);
    return (false);
  }
  return (true);
}

void		Display::GravityWorms(int nb_player)
{
  if (!this->checkNbPlayer(nb_player))
	  return;

  int idTeam = this->listPlayers[nb_player][0];
  int idWorms = this->listPlayers[nb_player][1];


  int X = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int Y = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y;
  int tmpGravity = GRAVITY_WORMS;

  if (nb_player == this->gameloop.getWormsPlayer()
      && this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == JUMPTHOUGHTWALL
      && this->weapons->jumpi == JUMP_FALL)
  {
    if (this->gameloop._debugRand)
      return;
    else
      tmpGravity /= 2;
  }

  if (!this->testIfWormsInWater(nb_player, X, Y))
    return;

  int z = Y;
  while (z + 1 < this->island.getSizeY() - 1 && (!(this->island.isDestructible(this->island.getMapping(X, z))))
	 && z < Y + tmpGravity && this->gameloop.testPosOfAllWorms(X, z, idTeam, idWorms))
    {
      ++z;
      if (z >= this->island.getSizeY() - 2)
	     break;
    }

  if (z != Y)
  {
    this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._falling++;
    replacePlayer(X, z, nb_player);
    this->setZoomPlayer();

    if (this->gameloop.getWormsPlayer() == nb_player
        && (  this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == UZI
          ||  this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == SHOOTGUN
          ||  this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == BAZOOKA
          ||  this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == GRENADE
          ||  this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == DRILL
        ))
    {
      this->weapons->affWeaponCursor(false);
    }
    //std::cout << "fuul" << std::endl;
  }
  else
  {
    if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.vel <= 1)
    {
      if (!this->testIfWormsAlive(nb_player))
        return;
    }
    if (this->gameloop.getWormsPlayer() == nb_player
        && this->gameloop._aff_cursor == false
        && (  this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == UZI
          ||  this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == SHOOTGUN
          ||  this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == BAZOOKA
          ||  this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == GRENADE
          ||  this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == DRILL
        ))
    {
      this->weapons->affWeaponCursor(true);
    }
    this->testFallingHit(nb_player);
    this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._falling = 0;
  }

  ////////////////////////////////////////// for jump ////////////////////
  if (this->weapons->jumpi == JUMP_START && nb_player == this->gameloop.getWormsPlayer())
  {
    if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.vel <= 1)
    {
      this->weapons->jumpi = JUMP_FIST_FALL;
      std::cout << "velocité <1 gravity !" << std::endl;
      this->weapons->activeParachute();
    }
    else
      std::cout << "fuu" << std::endl;
  }
  //this->gameloop.getWormsFromGameLoop(idTeam, idWorms).addVelocity(0.1, 90);

}

void Display::setForceWorms(int nb_player)
{
  if (!this->checkNbPlayer(nb_player))
		return;
  int idTeam = this->listPlayers[nb_player][0];
  int idWorms = this->listPlayers[nb_player][1];

  float tmpY = this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.YPos;
  this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.XPos += this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.XVel;
  this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.YPos += this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.YVel;
  if ((int)this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.XPos != this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x
      || (int)this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.YPos != this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y)
  {
    this->setWeaponToPlayer(this->gameloop.getWormsPlayer(), true);
    if (  (!this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._passThroughtWall
        && this->island.isDestructible(this->island.getMapping((int)this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.XPos, (int)this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.YPos))
            )
        /*||
        (   (int)this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.XPos >= this->island.getSizeX() - 2
         || (int)this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.XPos < 2
         || (int)this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.YPos >= this->island.getSizeY() - 2
         || (int)this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.YPos < 2
       )*/
        )
    {
      this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.XPos -= this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.XVel * 1;
      this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.YPos -= this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.YVel * 1;
      this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._falling = 0;
      this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setVelocity(0, -1);
      return;
    }
    this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setPos((int)this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.XPos, (int)this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.YPos);
    if (tmpY > this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._force.YPos)
      this->gameloop.getWormsFromGameLoop(idTeam, idWorms)._falling = 0;
    this->gameloop.getWormsFromGameLoop(idTeam, idWorms).addVelocity(-0.1, -1);
  }
}

bool Display::testHitObject(int x1, int y1, int r = 4)
{
  if (x1 < 0 || x1 >= this->island.getSizeX() - 1)
    return (true);
  if (y1 < 0 || y1 >= this->island.getSizeY() - 1)
    return (true);
  bool hitGround = false;
  int rr = r;
  for(int y = -rr ; y <= rr ; y++)
  {
    for(int x = -rr ; x <= rr ; x++)
    {
      if (x * x + y * y <= rr * rr)
      {
        if (this->island.isDestructible(this->island.getMapping(x1 + x, y1 + y)))
          hitGround = true;
      }
    }
  }
  int i = -1;

  int idTeamPlayer = -1;
  int idWormsPlayer = -1;
  if (this->checkNbPlayer(this->gameloop.getWormsPlayer()))
	{
    idTeamPlayer = this->listPlayers[this->gameloop.getWormsPlayer()][0];
    idWormsPlayer = this->listPlayers[this->gameloop.getWormsPlayer()][1];
  }

  /*while (++i < this->gameloop.listPlayers.size())
  {
    int idTeam = this->listPlayers[i][0];
    int idWorms = this->listPlayers[i][1];
    if (idTeam == idTeamPlayer && idWorms == idWormsPlayer)
      continue;
    int x = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x;
    int y = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y;
    if (this->gameloop.posOfTwoWorms(x1, y1, x, y))
      return (true);
  }*/


  return (hitGround);
}

void Display::objectPhysics()
{
  unsigned int i = 0;
  bool reactualiseOk = false;
  while (i < this->gameloop.rocket.size())
  {
    std::cout << "before: " << this->gameloop.rocket[i].XPos << std::endl;
    this->gameloop.rocket[i].advance();
    //cat->setRotation(core::vector3df(1, 1, 90));
    std::cout << "after: " << this->gameloop.rocket[i].XPos << std::endl;
    float X = (this->gameloop.rocket[i].XPos * 0.0266) - 25.4;
    float Y = -14 + (this->gameloop.rocket[i].YPos * 0.0266);
    this->rocketObj[i]->setPosition(core::vector3df(X, -Y, this->rocketObj[i]->getPosition().Z));
    this->rocketObj[i]->setRotation(core::vector3df(this->rocketObj[i]->getRotation().X, this->rocketObj[i]->getRotation().Y, this->gameloop.rocket[i].angle - 90));
    if (this->gameloop.rocket[i].XPos <= 0 || this->gameloop.rocket[i].XPos >= this->island.getSizeX() || this->gameloop.rocket[i].YPos <= 0 || this->gameloop.rocket[i].YPos >= this->island.getSizeY() || this->testHitObject(this->gameloop.rocket[i].XPos, this->gameloop.rocket[i].YPos, 5))
    {
      //make hole
      std::cout << "HOLE Rocket !" << std::endl;
      std::cout << "pos: " << this->gameloop.rocket[i].XPos << ":" << this->gameloop.rocket[i].YPos << std::endl;
      Hole hole(this->island.getMap());
      hole.drawHole((int)this->gameloop.rocket[i].XPos, (int)this->gameloop.rocket[i].YPos, this->gameloop.rocket[i].holy, WIND, PERFECT);
      reactualiseOk = true;

      this->applyForceHole(this->gameloop.rocket[i].XPos, this->gameloop.rocket[i].YPos, this->gameloop.rocket[i].holy, true);

      this->gameloop.rocket.erase(this->gameloop.rocket.begin() + i);
      this->rocketObj[i]->setPosition(core::vector3df(2000, 2000, this->rocketObj[i]->getPosition().Z));
      this->rocketObj.erase(this->rocketObj.begin() + i);
    }
    ++i;
  }
  i = 0;
  while (i < this->gameloop.bullet.size())
  {
    int kk = -1;
    while (++kk < 2)
    {
      std::cout << "before: " << this->gameloop.bullet[i].XPos << std::endl;
      this->gameloop.bullet[i].advance();
      //cat->setRotation(core::vector3df(1, 1, 90));
      std::cout << "after: " << this->gameloop.bullet[i].XPos << std::endl;
      float X = (this->gameloop.bullet[i].XPos * 0.0266) - 25.4;
      float Y = -14 + (this->gameloop.bullet[i].YPos * 0.0266);
      this->bulletObj[i]->setPosition(core::vector3df(X, -Y, this->bulletObj[i]->getPosition().Z));
      this->bulletObj[i]->setRotation(core::vector3df(this->bulletObj[i]->getRotation().X, this->bulletObj[i]->getRotation().Y, this->gameloop.bullet[i].angle));
      if (this->gameloop.bullet[i].XPos <= 0 || this->gameloop.bullet[i].XPos >= this->island.getSizeX() || this->gameloop.bullet[i].YPos <= 0 || this->gameloop.bullet[i].YPos >= this->island.getSizeY() || this->testHitObject(this->gameloop.bullet[i].XPos, this->gameloop.bullet[i].YPos, this->gameloop.bullet[i].holy / 2))
      {
        //make hole
        std::cout << "HOLE BULLET !" << std::endl;
        std::cout << "pos bullet: " << this->gameloop.bullet[i].XPos << " " << this->gameloop.bullet[i].YPos << std::endl;
        Hole hole(this->island.getMap());
        hole.drawHole(this->gameloop.bullet[i].XPos, this->gameloop.bullet[i].YPos, this->gameloop.bullet[i].holy, WIND, PERFECT);
        reactualiseOk = true;
        this->applyForceHole(this->gameloop.bullet[i].XPos, this->gameloop.bullet[i].YPos, this->gameloop.bullet[i].holy, false);

        this->gameloop.bullet.erase(this->gameloop.bullet.begin() + i);
        this->bulletObj[i]->setPosition(core::vector3df(2000, 2000, this->bulletObj[i]->getPosition().Z));
        this->bulletObj.erase(this->bulletObj.begin() + i);
        break;
      }
    }
    ++i;
  }
  i = 0;
  while (i < this->gameloop.drill.size())
  {
    this->gameloop.drill[i].advance();
    if (this->gameloop.drill[i].XPos <= 0 || this->gameloop.drill[i].XPos >= this->island.getSizeX()
        || this->gameloop.drill[i].YPos <= 0 || this->gameloop.drill[i].YPos >= this->island.getSizeY()
        || this->testHitObject(this->gameloop.drill[i].XPos, this->gameloop.drill[i].YPos, 3)
        || this->gameloop.drill[i].cran >= this->gameloop.drill[i].maxCran
      )
    {
      std::cout << "HOLE DRILL !" << std::endl;
      Hole hole(this->island.getMap());
      hole.drawHole(this->gameloop.drill[i].XPos, this->gameloop.drill[i].YPos, this->gameloop.drill[i].holy, WIND, PERFECT);
      reactualiseOk = true;
      this->applyForceHole(this->gameloop.drill[i].XPos, this->gameloop.drill[i].YPos, this->gameloop.drill[i].holy, false);

      this->gameloop.drill.erase(this->gameloop.drill.begin() + i);
    }
    ++i;
  }
  i = 0;
  while (i < this->gameloop.grenade.size())
  {
    this->gameloop.grenade[i].advance();
    float X = (this->gameloop.grenade[i].XPos * 0.0266) - 25.4;
    float Y = -14 + (this->gameloop.grenade[i].YPos * 0.0266);
    this->grenadeObj[i]->setPosition(core::vector3df(X, -Y, this->grenadeObj[i]->getPosition().Z));
    this->grenadeObj[i]->setRotation(core::vector3df(this->grenadeObj[i]->getRotation().X, this->grenadeObj[i]->getRotation().Y, this->gameloop.grenade[i].angle - 90));
    if (this->gameloop.grenade[i].XPos <= 0 || this->gameloop.grenade[i].XPos >= this->island.getSizeX()
        || this->gameloop.grenade[i].YPos <= 0 || this->gameloop.grenade[i].YPos >= this->island.getSizeY()
        || this->testHitObject(this->gameloop.grenade[i].XPos, this->gameloop.grenade[i].YPos, 4))
    {
      this->gameloop.grenade[i].subBounce(1);
      if (this->gameloop.grenade[i].bounce > 0)
      {
        //if (this->gameloop.grenade[i].angle > -90 && this->gameloop.grenade[i].angle < 0)
          this->gameloop.grenade[i].setNewAngle(/*this->gameloop.grenade[i].angle * -1*/);
      }
      else
      {
        std::cout << "HOLE grenade !" << std::endl;
        Hole hole(this->island.getMap());
        hole.drawHole((int)this->gameloop.grenade[i].XPos, (int)this->gameloop.grenade[i].YPos, this->gameloop.grenade[i].holy, WIND, PERFECT);
        reactualiseOk = true;
        this->applyForceHole(this->gameloop.grenade[i].XPos, this->gameloop.grenade[i].YPos, this->gameloop.grenade[i].holy, true);

        this->gameloop.grenade.erase(this->gameloop.grenade.begin() + i);
        this->grenadeObj[i]->setPosition(core::vector3df(2000, 2000, this->grenadeObj[i]->getPosition().Z));
        this->grenadeObj.erase(this->grenadeObj.begin() + i);
      }
    }
    ++i;
  }
  i = 0;
  while (i < this->gameloop.dynamit.size())
  {
    if (this->gameloop.dynamit[i].XPos <= 0 || this->gameloop.dynamit[i].XPos >= this->island.getSizeX() || this->gameloop.dynamit[i].YPos <= 0 || this->gameloop.dynamit[i].YPos >= this->island.getSizeY())
    {
      this->gameloop.dynamit.erase(this->gameloop.dynamit.begin() + i);
      this->dynamitObj[i]->setPosition(core::vector3df(2000, 2000, this->dynamitObj[i]->getPosition().Z));
      this->dynamitObj.erase(this->dynamitObj.begin() + i);
      ++i;
      continue;
    }

    if (!this->testHitObject(this->gameloop.dynamit[i].XPos, this->gameloop.dynamit[i].YPos, 1))
    {
      this->gameloop.dynamit[i].fall(2);
      float X = (this->gameloop.dynamit[i].XPos * 0.0266) - 25.4;
      float Y = -14 + (this->gameloop.dynamit[i].YPos * 0.0266);
      this->dynamitObj[i]->setPosition(core::vector3df(X, -Y, this->dynamitObj[i]->getPosition().Z));
    }
    ++i;
  }
  if (reactualiseOk)
    this->reactualiseMap();
}

void Display::explodeDynamo()
{
  int i = 0;
  bool reactualiseOk = false;
  while (i < this->gameloop.dynamit.size())
  {
    this->testHitObject(this->gameloop.dynamit[i].XPos, this->gameloop.dynamit[i].YPos, 1);
    Hole hole(this->island.getMap());
    hole.drawHole(this->gameloop.dynamit[i].XPos, this->gameloop.dynamit[i].YPos, this->gameloop.dynamit[i].holy, WIND, PERFECT);
    reactualiseOk = true;
    this->applyForceHole(this->gameloop.dynamit[i].XPos, this->gameloop.dynamit[i].YPos, this->gameloop.dynamit[i].holy, true);

    this->gameloop.dynamit.erase(this->gameloop.dynamit.begin() + i);
    this->dynamitObj[i]->setPosition(core::vector3df(2000, 2000, this->dynamitObj[i]->getPosition().Z));
    this->dynamitObj.erase(this->dynamitObj.begin() + i);
    ++i;
  }
  if (reactualiseOk)
    this->reactualiseMap();
}
