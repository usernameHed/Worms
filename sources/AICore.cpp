#include "AICore.hh"
#include "Line.hh"
#include "template.hh"
#include "Weapons.hh"

AICore::AICore(Display &disp)
  : display(disp)
{

}

AICore::~AICore()
{

}

void	AICore::fillArray()
{
  if (this->display.getGame().getWormsPlayer() < 0 || this->display.getGame().getWormsPlayer() >= this->display.getGame().listPlayers.size())
     return;
  this->idTeamPlayer = this->display.getGame().listPlayers[this->display.getGame().getWormsPlayer()][0];
  this->idWormsPlayer = this->display.getGame().listPlayers[this->display.getGame().getWormsPlayer()][1];

  this->currentLife = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getLife().getPv();
  this->getGroundSize();

  for (int i = 0; i < this->display.getGame().listPlayers.size(); i++)
  {
    int idTeam = this->display.getGame().listPlayers[i][0];
    int idWorms = this->display.getGame().listPlayers[i][1];
    if (idTeam == idTeamPlayer) //pass if same team
      continue;

    AIChoices choice;

    this->isAtWeapon1(choice, i);
    this->isAtWeapon2(choice, i);
    this->isAtWeapon3(choice, i);
    this->getGroundSize(choice, i);
    this->getNearestEnemy(choice, i);
    this->getCurrentLife(choice, i);
    this->getDistance(choice, i);
    this->getId(choice, i);
    this->getDirection(choice, i);

    std::cout << "worms " << idTeam << ":" << idWorms
              << " type: (" << choice.AT_WEAPONTYPE_001 << "," << choice.AT_WEAPONTYPE_002 << "," << choice.AT_WEAPONTYPE_003 << ")"
              << " other: " << choice.GROUND_SIZE << " " << choice.DIST_NEAREST_ENEMY << " " << choice.CURRENT_LIFE << " " << choice.DISTANCE << " " << choice.ID_WORMS << " " << choice.RIGHT  << std::endl;
    _avAiChoices.push_back(choice);
  }

}


void	AICore::isAtWeapon1(AIChoices &choice, int nb_player)
{
  //std::cout << "CAC !!" << std::endl;
  if (nb_player < 0 || nb_player >= this->display.getGame().listPlayers.size())
	 return;

  int idTeam = this->display.getGame().listPlayers[nb_player][0];
  int idWorms = this->display.getGame().listPlayers[nb_player][1];
std::cout << "[get] AICore 57" << std::endl;
  int x = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().x;
  int y = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().y;
std::cout << "[get] AICore 60" << std::endl;
  int xEnemy = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int yEnemy = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().y;

  int right = (x > xEnemy) ? -1 : 1;
  this->deplacement = 0;
  while (this->deplacement < this->maxDeplacement)
  {
    while (y < this->display.getIsland().getSizeY() && !this->display.getIsland().isDestructible(this->display.getIsland().getMapping(x, y)))
      ++y;
    int cpt = 0;
    int z = y;
    while ((this->display.getIsland().isDestructible(this->display.getIsland().getMapping(x + right, z))))
    {
      ++cpt;
      --z;
    }
    if (!this->display.getGame().testPosOfAllWorms(x + right, y - (this->display.getGame().getHeightWorms() / 2), this->idTeamPlayer, this->idWormsPlayer))
      cpt = MAX_UP_WORMS + 1;

    if (cpt <= MAX_UP_WORMS)
    {
      //std::cout << "advande " << right << std::endl;
      x += right;
      y = z;
    }
    else
    {
      std::cout << "blocked !" << std::endl;
      //this->display.replacePlayer(x + right, z, nb_player);
      break;
    }
    ++this->deplacement;
  }

  std::vector<int> wormsHit = this->display.getWeapons()->getIaHit(x, y, this->display.getGame().getWormsPlayer(), right);
  int i = 0;
  while (i < wormsHit.size())
  {
    if (wormsHit[i] == nb_player)
    {
      std::cout << "i can pounch it !" << std::endl;
      //this->display.replacePlayer(x, y, this->display.getGame().getWormsPlayer());
      choice.AT_WEAPONTYPE_001 = true;
      return;
    }
    ++i;
  }
  choice.AT_WEAPONTYPE_001 = false;
}

void	AICore::isAtWeapon2(AIChoices &choice, int nb_player)
{
	if (nb_player < 0 || nb_player >= this->display.getGame().listPlayers.size())
		return;
  int x = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().x;
  int y = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().y - this->display.getGame().getHeightWorms() / 2;

  int idTeam = this->display.getGame().listPlayers[nb_player][0];
  int idWorms = this->display.getGame().listPlayers[nb_player][1];

  int xEnemy = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int yEnemy = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().y - this->display.getGame().getHeightWorms() / 2;

  choice.AT_WEAPONTYPE_002 = this->display.testLine(x, y, xEnemy, yEnemy);
}

void	AICore::isAtWeapon3(AIChoices &choice, int nb_player)
{
	if (nb_player < 0 || nb_player >= this->display.getGame().listPlayers.size())
		return;
  int x = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().x;
  int y = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().y - this->display.getGame().getHeightWorms() / 2;

  int idTeam = this->display.getGame().listPlayers[nb_player][0];
  int idWorms = this->display.getGame().listPlayers[nb_player][1];

  int xEnemy = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int yEnemy = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().y - this->display.getGame().getHeightWorms() / 2;

  int xHalf = std::abs(x - xEnemy) / 2;
  if (x > xEnemy)
    XORSWAP(x, xEnemy);

  int xMiddle = x + (xEnemy - x / 2);
  int yMiddle = y + (yEnemy - y / 2);
  yMiddle -= xHalf;
  if (this->display.testLine(x, y, xMiddle, yMiddle) && this->display.testLine(xMiddle, yMiddle, xEnemy, yEnemy))
  {
    choice.AT_WEAPONTYPE_003 = true;
    return;
  }
  choice.AT_WEAPONTYPE_003 = false;
}

void	AICore::getGroundSize(AIChoices &choice, int nb_player)
{
	if (nb_player < 0 || nb_player >= this->display.getGame().listPlayers.size())
		return;
  int idTeam = this->display.getGame().listPlayers[nb_player][0];
  int idWorms = this->display.getGame().listPlayers[nb_player][1];

  int x = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int y = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().y;
  int cnt = 0;
  while (y < this->display.getIsland().getSizeY() && this->display.getIsland().isDestructible(this->display.getIsland().getMapping(x, y)))
  {
    ++cnt;
    ++y;
  }
  choice.GROUND_SIZE = cnt;
  std::cout << "Ground: " << cnt << std::endl;
}

void	AICore::getGroundSize()
{
  int x = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().x;
  int y = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().y;
  int cnt = 0;
  while (y < this->display.getIsland().getSizeY() && this->display.getIsland().isDestructible(this->display.getIsland().getMapping(x, y)))
  {
    ++cnt;
    ++y;
  }
  this->groundSize = cnt;
}

void	AICore::getDistance(AIChoices &choice, int nb_player)
{
	if (nb_player < 0 || nb_player >= this->display.getGame().listPlayers.size())
		return;
  int x = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().x;
  int y = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().y - this->display.getGame().getHeightWorms() / 2;

  int idTeam = this->display.getGame().listPlayers[nb_player][0];
  int idWorms = this->display.getGame().listPlayers[nb_player][1];

  int xEnemy = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int yEnemy = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().y - this->display.getGame().getHeightWorms() / 2;

  float dist = sqrt( pow(x - xEnemy, 2) + pow(y - yEnemy, 2));

  choice.DISTANCE = (int)dist;
}

void	AICore::getCurrentLife(AIChoices &choice, int nb_player)
{
	if (nb_player < 0 || nb_player >= this->display.getGame().listPlayers.size())
		return;
  int idTeam = this->display.getGame().listPlayers[nb_player][0];
  int idWorms = this->display.getGame().listPlayers[nb_player][1];

  choice.CURRENT_LIFE = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getLife().getPv();
}

void	AICore::getNearestEnemy(AIChoices &choice, int nb_player)
{
  int minDist = 100000000;
  int x = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().x;
  int y = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().y - this->display.getGame().getHeightWorms() / 2;

  for (int i = 0; i < this->display.getGame().listPlayers.size(); i++)
  {
    int idTeam = this->display.getGame().listPlayers[i][0];
    int idWorms = this->display.getGame().listPlayers[i][1];
    if (idTeam != this->idTeamPlayer) //pass if same team
      continue;

    int xEnemy = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().x;
    int yEnemy = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().y - this->display.getGame().getHeightWorms() / 2;
    float dist = sqrt( pow(x - xEnemy, 2) + pow(y - yEnemy, 2));
    if (dist < minDist)
      minDist = dist;
  }
  choice.DIST_NEAREST_ENEMY = minDist;
}

void AICore::getId(AIChoices &choice, int nb_player)
{
  choice.ID_WORMS = nb_player;
}

void AICore::getDirection(AIChoices &choice, int nb_player)
{
  int x = this->display.getGame().getWormsFromGameLoop(this->idTeamPlayer, this->idWormsPlayer).getPos().x;
  if (nb_player < 0 || nb_player >= this->display.getGame().listPlayers.size())
		return;
  int idTeam = this->display.getGame().listPlayers[nb_player][0];
  int idWorms = this->display.getGame().listPlayers[nb_player][1];

  int xEnemy = this->display.getGame().getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  if (x > xEnemy)
  {
    choice.RIGHT = false;
    return;
  }
  choice.RIGHT = true;
  }

//////////////////////exec !

LUARes	AICore::executeBrain()
{
  return (this->brain.executeLUA(this->_avAiChoices));
}
