#include "Display.hh"
#include "AICore.hh"

bool Display::iaIsPlaying()
{
	if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
		return (false);

  int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];

  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getType() == IA)
  {
    //std::cout << "IA PLAY !" << std::endl;
    return (true);
  }
  //std::cout << "player PLAY !" << std::endl;
  return (false);
}

void Display::iaExportInfo()
{
  std::cout << "send info to LUA..." << std::endl;
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
	  return;
    //int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
    //int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];
  AICore ac(*this);
  //LUARes res;
  ac.fillArray();
  this->iaPlay.setIaMove(ac.executeBrain());

	if (this->iaPlay.getIaMove().idWorms == -1) //TODO: IA TIR DIRECT
	{
		LUARes tmplua;
		tmplua.idWorms = 0;
		tmplua.weaponType = 0;
		if (!this->gameloop.menuSet)
	        this->affWeaponsHUD();
		this->iaPlay.setIaMove(tmplua);
	}

  this->iaPlay.setAttack(false);
  this->iaPlay.reset();
}

int Display::sign(int x) const
{
  if (x < 0)
    return (-1);
  return 1;
}

bool Display::testLine(int x1, int y1, int x2, int y2)
{
  int x = x2;
  int y = y2;
  int dy = y2 - y1;
  int dx = x2 - x1;

  if (std::abs(dy) > std::abs(dx))
  {
    for(y = y1; y != y2; y += this->sign(dy))
    {
      x = x1 + ( y - y1 ) * dx / dy;
      //this->island.change(x, y, SAND);
      if (this->island.isDestructible(this->island.getMapping(x, y)))
        return (false);
    }
  }
  else
  {
    for( x = x1; x != x2; x += this->sign(dx))
    {
      y = y1 + ( x - x1 ) * dy / dx;
      //this->island.change(x, y, SAND);
      if (this->island.isDestructible(this->island.getMapping(x, y)))
        return (false);
    }
  }
  if (this->island.isDestructible(this->island.getMapping(x2, y2)))
    return (false);
  return (true);
}

bool Display::testIfToMuchFalling(int x, int y)
{
  /////////////////// don't turn if is falling !
	int z = y;
  while (z + 1 < this->island.getSizeY() - 1 && (!(this->island.isDestructible(this->island.getMapping(x, z)))))
  {
    ++z;
    if (z > this->island.getSizeY() - 5)
     return (false);
  }
  if (z - y >= (this->gameloop.getHeightWorms() * 5) || z > this->island.getSizeY() - 5)
  {
    std::cout << "FUCK FUCK FUCK !" << std::endl;
    return (false);
  }
  return (true);
}

void Display::hideWorms()
{
  std::cout << "hide !" << std::endl;
  if (!this->checkNbPlayer(this->iaPlay.getIaMove().idWorms))
	  return;
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
	  return;

  int idTeamTarget = this->gameloop.listPlayers[this->iaPlay.getIaMove().idWorms][0];
  int idWormsTarget = this->gameloop.listPlayers[this->iaPlay.getIaMove().idWorms][1];
  int idTeam = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][1];

  if ((this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == DYNAMIT
        && this->iaPlay.hideHoriz > this->iaPlay.maxHideDynamit)
  || (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() != DYNAMIT
      && this->iaPlay.hideHoriz > this->iaPlay.maxHide))
    return;
  this->iaPlay.hideHoriz++;

  int x = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int y = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y;

  int xEnemy = this->gameloop.getWormsFromGameLoop(idTeamTarget, idWormsTarget).getPos().x;
  int yEnemy = this->gameloop.getWormsFromGameLoop(idTeamTarget, idWormsTarget).getPos().y;

  int right = (x > xEnemy) ? -1 : 1;

  if (this->testIfToMuchFalling(x, y - right))
    this->changeHoriz(x, y, idTeam, idWorms, -right);
  else
    this->changeHoriz(x, y, idTeam, idWorms, right);

  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() != DYNAMIT)
    return;
  if (this->iaPlay.jumpHide < this->iaPlay.jumpHideMax)
  {
    std::cout << "jump hide" << std::endl;
    if (this->jump(x, y, idTeam, idWorms, JUMP_WORMS))
    {
      ++this->iaPlay.jumpHide;
    }
    return;
  }
}

bool Display::testIsGroundDown(int x, int y)
{
	int z = y;
  while (z + 1 < this->island.getSizeY() - 2)
  {
		if (this->island.isDestructible(this->island.getMapping(x, z)))
		{
			std::cout << "ok down" << std::endl;
			return (true);
		}
    ++z;
  }
	std::cout << "not ok" << std::endl;
	return (false);
}

void Display::iaMoveAfterJump()
{
	if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
		return;
	if (this->iaPlay.paraTime >= this->iaPlay.paraTimeMax)
		return;
	++this->iaPlay.paraTime;

	int idTeam = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][0];
	int idWorms = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][1];
	int x = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int y = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y;

	if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
	{
		std::cout << "right" << std::endl;
		if (this->testIsGroundDown(x + 1, y)
				&& this->testIsGroundDown(x + 2, y)
					&& this->testIsGroundDown(x + 3, y)
						&& this->testIsGroundDown(x + 4, y)
							&& this->testIsGroundDown(x + 5, y)
			)
			this->changeHoriz(x, y, idTeam, idWorms, 1);
		else
			this->changeHoriz(x, y, idTeam, idWorms, -1);
	}
	else
	{
		std::cout << "left" << std::endl;
		if (this->testIsGroundDown(x - 1, y)
				&& this->testIsGroundDown(x - 2, y)
				&& this->testIsGroundDown(x - 3, y)
				&& this->testIsGroundDown(x - 4, y)
				&& this->testIsGroundDown(x - 5, y)
			)
			this->changeHoriz(x, y, idTeam, idWorms, -1);
		else
			this->changeHoriz(x, y, idTeam, idWorms, 1);
	}
}

void Display::iaPlaying()
{
	if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
	  return;

  int idTeam = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][1];

  if (!this->weapons->getCanUsWeapon() && this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getWeaponsType() == JUMPTHOUGHTWALL)
	{
		this->iaMoveAfterJump();
		return;
	}
  if (this->iaPlay.getAttack())
  {
    this->hideWorms();
    return;
  }
  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getLife().getPv() < 5)
  {
		LUARes tmplua;
    tmplua.idWorms = this->iaPlay.getIaMove().idWorms;
    tmplua.weaponType = -1;
    this->iaPlay.setIaMove(tmplua);
    this->iaNoLoSe();
    return;
  }
  if (this->iaPlay.getIaMove().weaponType == 0)
    this->iaCac();
  else if (this->iaPlay.getIaMove().weaponType == 1)
    this->iaDirect();
  else if (this->iaPlay.getIaMove().weaponType == 2)
    this->iaIndirect();
  else
    this->iaNoLoSe();
}

void Display::iaJump()
{
  if (!this->weapons->getCanUsWeapon())
    return;
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
	  return;
  int idTeam = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][1];

  this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setWeaponsType(JUMPTHOUGHTWALL);
  if (!this->gameloop.menuSet)
    this->affWeaponsHUD();
  this->weapons->attack();
}

void Display::iaCac()
{
  std::cout << "cac !" << std::endl;
  std::cout << "attack the worms: " << this->iaPlay.getIaMove().idWorms << std::endl;
  if (!this->checkNbPlayer(this->iaPlay.getIaMove().idWorms))
	  return;
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
	  return;

  int idTeamTarget = this->gameloop.listPlayers[this->iaPlay.getIaMove().idWorms][0];
  int idWormsTarget = this->gameloop.listPlayers[this->iaPlay.getIaMove().idWorms][1];
  int idTeam = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][1];

	int x = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int y = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y;

  int xEnemy = this->gameloop.getWormsFromGameLoop(idTeamTarget, idWormsTarget).getPos().x;
  int yEnemy = this->gameloop.getWormsFromGameLoop(idTeamTarget, idWormsTarget).getPos().y;

  int right = (x > xEnemy) ? -1 : 1;

  /*if (std::abs(y - yEnemy) > this->gameloop.getHeightWorms() * 10)
  {
    LUARes tmplua;
    tmplua.idWorms = this->iaPlay.getIaMove().idWorms;
    tmplua.weaponType = 1;
    this->iaPlay.setIaMove(tmplua);
    return;
  }*/


  std::vector<int> wormsHit = this->weapons->getIaHit(x, y, this->gameloop.getWormsPlayer(), right);
  int i = 0;

  while (i < wormsHit.size())
  {
	  if (!this->checkNbPlayer(wormsHit[i]))
	  {
		  ++i;
		  continue;
	  }

    int tmpIdTeam = this->gameloop.listPlayers[wormsHit[i]][0];
    //if (wormsHit[i] == this->iaPlay.getIaMove().idWorms)
    if (tmpIdTeam != idTeam)
    {
      std::cout << "CAC ATTACK !!" << std::endl;
      //random CAC !
      WeaponsType tmpWeaponType = DYNAMIT;
      if (this->gameloop.getWormsFromGameLoop(idTeamTarget, idWormsTarget).getLife().getPv() <= 3)
        tmpWeaponType = FINGER;
      else if (this->gameloop.getWormsFromGameLoop(idTeamTarget, idWormsTarget).getLife().getPv() <= 25)
        tmpWeaponType = POUNCH;
      else if (this->gameloop.getWormsFromGameLoop(idTeamTarget, idWormsTarget).getLife().getPv() <= 30)
        tmpWeaponType = BASEBALL;

      this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setWeaponsType(tmpWeaponType);
      if (!this->gameloop.menuSet)
	this->affWeaponsHUD();

      if (tmpWeaponType == DYNAMIT)
      {
        int tmpRand = std::rand() % 100;
        if (tmpRand < 5)
					tmpWeaponType = FINGER;
				else if (tmpRand < 20)
					tmpWeaponType = BASEBALL;
				else if (tmpRand < 70 - ((this->gameloop.difficulty == HARD_GAME) ? ((this->gameloop.getWormsFromGameLoop(idTeamTarget, idWormsTarget).getType() == HUMAN) ? 25 : 0) : 0) )
					tmpWeaponType = POUNCH;
				else
        {
          if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
            this->dynamity(x + this->gameloop.getWidthWorm(), y);
          else
            this->dynamity(x - this->gameloop.getWidthWorm(), y);
        }
      }
      std::cout << "WEAPOIN TYPE: " << tmpWeaponType << std::endl;
      this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setWeaponsType(tmpWeaponType);
      if (!this->gameloop.menuSet)
	this->affWeaponsHUD();

      this->weapons->attack();
      //////////////////
      this->displayWeaponType();
      this->gameloop.setPhase(4);
      this->gameloop.setWaitTimeAfterAttack();
      this->gameloop._debugTimerGame = 0.0;
      //////////////////

      this->iaPlay.setAttack(true);
      return;
    }
    ++i;
  }
  int tmpXDebug = x;
  int tmpYDebug = y;
  if (!this->testIfToMuchFalling(x, y + right))
  {
    std::cout << "MEGAJUMP ?" << std::endl;
		if (right > 0 && x > (this->island.getSizeX() / 100) * 70)
			this->changeHoriz(x, y, idTeam, idWorms, -right);
		else if (right < 0 && x < (this->island.getSizeX() / 100) * 30)
			this->changeHoriz(x, y, idTeam, idWorms, -right);
    this->iaJump();
    return;
  }

  if (!this->changeHoriz(x, y, idTeam, idWorms, right))
  {
    if (this->iaPlay.jumpFocus < this->iaPlay.jumpFocusMax)
    {
      std::cout << "JUMPPPPPPPPPPPPp" << std::endl;
      if (this->jump(x, y, idTeam, idWorms, JUMP_WORMS))
      {
        ++this->iaPlay.jumpFocus;
      }
      return;
    }
    this->iaPlay.jumpDebugFocus++;
    std::cout << "err: " << this->iaPlay.jumpDebugFocus << std::endl;

    if (this->iaPlay.jumpDebugFocus > this->iaPlay.jumpDebugFocusMax)
    {
      LUARes tmplua;
      tmplua.idWorms = this->iaPlay.getIaMove().idWorms;
      tmplua.weaponType = -1;
      this->iaPlay.setIaMove(tmplua);
    }
  }

  /*if (!(tmpXDebug == x && tmpYDebug == y))
  {
  x = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  y = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y;
  }*/
}

void Display::iaDirect()
{
  std::cout << "direct !" << std::endl;
}

void Display::iaIndirect()
{
  std::cout << "indirect !" << std::endl;
}

void Display::iaNoLoSe()
{
	if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
		return;
  int idTeam = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->gameloop.listPlayers[this->gameloop.getWormsPlayer()][1];

  int x = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int y = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y;

	if (this->gameloop.menuSet)
		return;
  this->gameloop.getWormsFromGameLoop(idTeam, idWorms).setWeaponsType(DRILL);
  if (!this->gameloop.menuSet)
    this->affWeaponsHUD();

  int right = -1;
  if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
    right = 1;
	if (!this->testIfToMuchFalling(x, y + right))
		right *= -1;

	if (this->changeHoriz(x, y, idTeam, idWorms, right))
		return;

  int angleToFind = 140;
  if (this->iaPlay.angleTmpDrill == -420042)
  {
    if (y > this->island.getSizeY() - this->gameloop.getHeightWorms() * 2)
      angleToFind = 65 - 55 + (rand() % 70);
    else
      angleToFind = 140 - 55 + (rand() % 70);
    this->iaPlay.angleTmpDrill = angleToFind;
  }
  else
  {
    if (y > this->island.getSizeY() - this->gameloop.getHeightWorms() * 2)
      this->iaPlay.angleTmpDrill = 65 - 55 + (rand() % 70);
    //this->iaPlay.angleTmpDrill = this->iaPlay.angleTmpDrill - 5
  }


  if (this->gameloop._tmpAngle != this->iaPlay.angleTmpDrill)
  {
    if (this->gameloop._tmpAngle < this->iaPlay.angleTmpDrill)
      this->weapons->addAngleCursor(-1);
    else
      this->weapons->addAngleCursor(1);
  }
  else
  {
    std::cout << "drill !" << std::endl;
    bool tmpAdvance = false;

    if (this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getDirection() == RIGHT)
    {
      if (this->testIfToMuchFalling(x, y + 1))
        tmpAdvance = this->changeHoriz(x, y, idTeam, idWorms, 1);
    }
    else
    {
      if (this->testIfToMuchFalling(x, y - 1))
        tmpAdvance = this->changeHoriz(x, y, idTeam, idWorms, -1);
    }
    //if (!tmpAdvance)
    this->actionRepeat(idTeam, idWorms, true);
    this->actionRepeat(idTeam, idWorms, true);

  }
  std::cout << "anglezfc: " << this->gameloop._tmpAngle << std::endl;
}
