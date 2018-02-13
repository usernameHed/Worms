#include "GameLoop.hh"
#include "Spawn.hh"
#include "Spawner.hh"
#include "Display.hh"

bool GameLoop::deleteWormsFromListPlayer(unsigned int idTeam, unsigned int idWorms)
{
  unsigned int i = 0;
  while (i < this->listPlayers.size())
  {
    if (this->listPlayers[i][0] == idTeam
        && this->listPlayers[i][1] == idWorms)
    {
      std::cout << "delete: "  << idTeam << ":" << idWorms << std::endl;
      this->listPlayers.erase(this->listPlayers.begin() + i);
      return (true);
    }
    ++i;
  }
  return (false);
}

bool GameLoop::testIfCurrentWormsAlive()
{
  if (this->getWormsPlayer() < 0 || this->getWormsPlayer() >= this->listPlayers.size())
    return (false);

  int idTeam = this->listPlayers[this->getWormsPlayer()][0];
  int idWorms = this->listPlayers[this->getWormsPlayer()][1];
  if (this->getWormsFromGameLoop(idTeam, idWorms).getLife().isAlive())
    return (true);
  return (false);
}

Worms &GameLoop::getWormsFromGameLoop(int idTeam, int idWorms)
{
  if (!(idTeam >= 0 && idTeam < this->teams.size()
      && idWorms >= 0 && idWorms < this->teams[idTeam].getTeamNbWorms()))
  {
    std::cout << "ERROR GET WORMS FROM GAMELOOP, maybe set it to 0, 0 ?" << std::endl;
    exit(0);
  }
  return(this->teams[idTeam].getWorms(idWorms));
}

void GameLoop::findWhoPlay()
{
  unsigned int i = 0;

  while (i < this->listPlayers.size())
  {
    if (this->getWormsFromGameLoop(this->listPlayers[i][0], this->listPlayers[i][1]).getPlaying())
    {
      this->setWormsPlayer(i);
      return;
    }
    ++i;
  }
  std::cout << "NO one is playing !!" << std::endl;
  this->setWormsPlayer(-1);
}

void GameLoop::setWhoIsPlaying()
{
  if (this->getWormsPlayer() < 0 || this->getWormsPlayer() >= this->listPlayers.size() )
    this->setWormsPlayer(0);
  this->getWormsFromGameLoop(this->listPlayers[this->getWormsPlayer()][0], this->listPlayers[this->getWormsPlayer()][1]).setPlaying(true);
  std::cout << "worms " << this->listPlayers[this->getWormsPlayer()][0] << ", " << this->listPlayers[this->getWormsPlayer()][1] << " start playing !" << std::endl;
}

void GameLoop::nextWhoIsPlaying()
{
  int idTeam;
  int idWorms;
  int tmpCurrentPlayer = this->getWormsPlayer();

  if (this->getWormsPlayer() != -1)
  {
    int tmpIdTeam = this->listPlayers[this->getWormsPlayer()][0];
    int tmpIdWorms = this->listPlayers[this->getWormsPlayer()][0];

  }


  if (this->getWormsPlayer() != -1 && !this->tmpDead)
  {
    idTeam = this->listPlayers[this->getWormsPlayer()][0];
    idWorms = this->listPlayers[this->getWormsPlayer()][1];
    this->getWormsFromGameLoop(idTeam, idWorms).setPlaying(false);
  }
  this->tmpDead = false;
  if (this->getWormsPlayer() + 1 < this->listPlayers.size())
    this->setWormsPlayer(this->getWormsPlayer() + 1);
  else
    this->setWormsPlayer(0);

  idTeam = this->listPlayers[this->getWormsPlayer()][0];
  idWorms = this->listPlayers[this->getWormsPlayer()][1];

  if (tmpCurrentPlayer != -1)
  {
  }

  std::cout << "worms (" << idTeam << ":" << idWorms << ") prepare to play !" << std::endl;
  this->getWormsFromGameLoop(idTeam, idWorms).setPlaying(true);
}

bool GameLoop::posOfTwoWorms(int x1, int y1, int x2, int y2)
{
  int i = x1 - (this->_widhWorms / 2);
  int j;
  int k;
  int l;
  while (i < x1 + (this->_widhWorms / 2))
  {
    j = y1 - (this->_heightWorms / 2);
    while (j < y1 + (this->_heightWorms / 2))
    {
      k = x2 - (this->_widhWorms / 2);
      while (k < x2 + (this->_widhWorms / 2))
      {
        l = y2 - (this->_heightWorms / 2);
        while (l < y2 + (this->_heightWorms / 2))
        {
          if (i == k && j == l)
            return (false);
          ++l;
        }
        ++k;
      }
      ++j;
    }
    ++i;
  }
  return (true);
}

std::vector<int> GameLoop::allWormsInBox(int x1, int y1, int x2, int y2)
{
  int i = 0;
  std::vector<int> tmp;
  int idTeam;
  int idWorms;
  //std::cout << "ToTest:" << x1 << ":" << y1 << ":" << x2 << ":" << y2 << std::endl;
  int tmpX1 = x1;
  int tmpY1 = y1;
  int tmpX2 = x2;
  int tmpY2 = y2;
  if (this->getWormsPlayer() < 0 || this->getWormsPlayer() >= this->listPlayers.size() )
    return (tmp);
  int tmpIdTeam = this->listPlayers[this->getWormsPlayer()][0];

  while (i < this->listPlayers.size())
  {
    idTeam = this->listPlayers[i][0];
    idWorms = this->listPlayers[i][1];


    if (i == this->getWormsPlayer() || idTeam == tmpIdTeam)
    {
      ++i;
      continue;
    }
    int newX1;
    int newX2 = this->getWormsFromGameLoop(idTeam, idWorms).getPos().x + (this->getWidthWorm() / 2);
    int newY1;// = this->getWormsFromGameLoop(idTeam, idWorms).getPos().y - (this->getHeightWorms() / 2);
    int newY2 = this->getWormsFromGameLoop(idTeam, idWorms).getPos().y + (this->getHeightWorms() / 2);
    bool stop = false;
    //std::cout << "(-) " << newX1 << ":" << newY1 << ":" << newX2 << ":" << newY2 << std::endl;
    tmpX1 = x1;
    while (tmpX1 <= tmpX2)
    {
      tmpY1 = y1;
      while (tmpY1 < y2)
      {
        newX1 = this->getWormsFromGameLoop(idTeam, idWorms).getPos().x - (this->getWidthWorm() / 2);
        while (newX1 < newX2)
        {
          newY1 = this->getWormsFromGameLoop(idTeam, idWorms).getPos().y - (this->getHeightWorms() / 2);
          while (newY1 < newY2)
          {
            if (tmpY1 == newY1 && tmpX1 == newX2)
            {
              tmp.push_back(i);
              stop = true;
              break;
            }

            ++newY1;
          }

          if (stop)
            break;
          ++newX1;
        }
        if (stop)
          break;
        ++tmpY1;
      }

      if (stop)
        break;
      ++tmpX1;
    }


    ++i;
  }
  return (tmp);
}

bool GameLoop::testPosOfAllWorms(int x, int y, int idTeam, int idWorms)
{
  unsigned int i = 0;
  int tmpX = 0;
  int tmpY = 0;

  i = 0;
  while (i < this->listPlayers.size())
	{
	  tmpX = this->getWormsFromGameLoop(this->listPlayers[i][0], this->listPlayers[i][1]).getPos().x;
	  tmpY = this->getWormsFromGameLoop(this->listPlayers[i][0], this->listPlayers[i][1]).getPos().y;
	  if (idTeam == this->listPlayers[i][0] && idWorms == this->listPlayers[i][1])
    {
      ++i;
      continue;
    }
    if (!this->posOfTwoWorms(x, y, tmpX, tmpY))
      return (false);
	  ++i;
	}
  ++y;
  return (true);
}
