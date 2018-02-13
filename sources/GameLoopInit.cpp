#include "GameLoop.hh"
#include "Spawn.hh"
#include "Spawner.hh"
#include "Display.hh"

GameLoop::GameLoop(std::vector<Team> &tea)
  : teams(tea)
{
  this->lg.loadGame("logger.log");
  this->initGame(true);
}

GameLoop::~GameLoop()
{

}

void GameLoop::initGame(bool menu)
{
  this->menuSet = menu;
  this->firstTimeNoMenu = false;
  this->debugStaticHud = false;

  this->lg.log("[GameLoopInit.cpp] - initGame\n");
  if (this->menuSet)
  {
    this->initMap(ISLAND);
    this->initTeams();
    this->initListPlayer();

    this->initDisplay(menu);

    //this->loadMap = false;
  }
  else
  {
    //change type of map if needed...
    //TODO: change type of map PLAY GAME
    if (this->mapMenuType)
      this->initMap(PLANE);
    else
      this->initMap(ISLAND);
  }
}

void GameLoop::initListPlayer()
{
  std::vector<unsigned int> idTeam;
  for (size_t k = 0; k < teams.size(); k++)
    idTeam.push_back(0);

  unsigned int i = 0;
  unsigned int t = 0;
  this->listPlayers.clear();
  while (t < MAX_WORMS_PER_TEAM * MAX_TEAMS)
  {
    for (size_t k = 0; k < teams.size(); k++)
    {
        if (idTeam[k] < teams[k].getTeamNbWorms())
        {
          std::vector<int> tmp;
          tmp.push_back(k);//idTeam
          tmp.push_back(idTeam[k]);//idWorms
          this->listPlayers.push_back(tmp);
          //this->listPlayers.push_back(teams[k].getWorms(idTeam[k]));
          ++idTeam[k];
        }
    }
    ++t;
  }
}

void GameLoop::affListWorms()
{
  unsigned int i = 0;
  while (i < this->listPlayers.size())
  {
    std::cout << "team: " << this->listPlayers[i][0] << ", id: " << this->listPlayers[i][1] << "life: " << this->getWormsFromGameLoop(this->listPlayers[i][0], this->listPlayers[i][1]).getLife().getPv() << std::endl;
    ++i;
  }
  std::cout << std::endl;
}

void GameLoop::affWormsOnMap()
{
  this->changeTmpByWind();
  unsigned int i = 0;
  while (i < this->listPlayers.size())
  {
    //aff life
    this->writeLifePosition(this->listPlayers[i][0], this->listPlayers[i][1]);
    //aff worms
    this->changeWindByTmp(this->listPlayers[i][0], this->listPlayers[i][1]);
    ++i;
  }
  std::cout << std::endl;
}

void GameLoop::writeLifePosition(unsigned int idTeam, unsigned int idWorms)
{
  //aff lifePosition
  int tmpX = this->teams[idTeam].getWorms(idWorms).getLife().getPosLife().x;
  int tmpY = this->teams[idTeam].getWorms(idWorms).getLife().getPosLife().y;
  this->island.change(tmpX, tmpY, SIZE_LIFE);

  //aff slideLife
  std::vector<int> tmpSlide = this->teams[idTeam].getWorms(idWorms).getLife().getSlifeLifePos();
  int x1 = tmpSlide[0];
  int y1 = tmpSlide[1];
  int x2 = tmpSlide[2];
  int y2 = tmpSlide[3];

  while (y1 <= y2)
  {
    x1 = tmpSlide[0];
    while (x1 <= x2)
    {
      this->island.change(x1, y1, SIZE_LIFE);
      ++x1;
    }
    ++y1;
  }
}

void GameLoop::changeTmpByWind()
{
  unsigned int i = 0;
  unsigned int j = 0;
  while (j < this->island.getSizeY())
  {
    i = 0;
    while (i < this->island.getSizeX())
    {
      if (this->island.getMap()[j][i] == TMP_TEAM_1
          || this->island.getMap()[j][i] == TMP_TEAM_2
          || this->island.getMap()[j][i] == TMP_TEAM_3
          || this->island.getMap()[j][i] == TMP_TEAM_4
          || this->island.getMap()[j][i] == SIZE_LIFE)
        this->island.change(i, j, WIND);
      ++i;
    }
    ++j;
  }
}

void GameLoop::changeWindByTmp(unsigned int idTeam, unsigned int idWorms)
{
  int x = this->teams[idTeam].getWorms(idWorms).getPos().x;
  int y = this->teams[idTeam].getWorms(idWorms).getPos().y;
  unsigned int mini = x - (this->teams[idTeam].getWorms(idWorms).getWidth() / 2);
  unsigned int maxi = x + (this->teams[idTeam].getWorms(idWorms).getWidth() / 2);
  unsigned int minj = y - this->teams[idTeam].getWorms(idWorms).getHeight();
  unsigned int maxj = y;

  while (mini <= maxi)
  {
    minj = y - this->teams[idTeam].getWorms(idWorms).getHeight();
    while (minj < maxj)
    {
      if (idTeam == 0)
        this->island.change(mini, minj, TMP_TEAM_1);
      else if (idTeam == 1)
        this->island.change(mini, minj, TMP_TEAM_2);
      else if (idTeam == 2)
        this->island.change(mini, minj, TMP_TEAM_3);
      else if (idTeam == 3)
        this->island.change(mini, minj, TMP_TEAM_4);
      ++minj;
    }
    ++mini;
  }
}

void GameLoop::initMap(TypeOfGenerator typeGen)
{
  //this->island = new IslandGenerator();
  if (this->loadMapMenu)
  {
    this->island.loadMap("test.worms");
    this->loadMapMenu = false;
  }
  else
    this->island.constructMap(SIZE_MAX_X, SIZE_MAX_Y, typeGen);

  this->obj.makeStringObject(this->island);
  //this->island.saveMap("test.worms");
}

int GameLoop::addToIa()
{
  if (this->difficulty == EASY_GAME)
    return (-25);
  else if (this->difficulty == HARD_GAME)
    return (50);
  return (0);
}

int GameLoop::addToHuman()
{
  if (this->difficulty == EASY_GAME)
    return (50);
  else if (this->difficulty == HARD_GAME)
    return (-25);
  return (0);
}

void GameLoop::changeLifeWorms()
{
  int addIa = this->addToIa();
  int addHuman = this->addToHuman();
  for (size_t i = 0; i < this->teams.size(); i++)
  {
    std::vector<int> tmpListLife;
    tmpListLife.push_back(this->teams[i].getTeamNbWorms());
    int tmpLife = 0;
    for (size_t j = 0; j < this->teams[i].getTeamNbWorms(); j++)
    {
      if (this->getWormsFromGameLoop(i, j).getType() == IA)
        this->getWormsFromGameLoop(i, j).setPv(this->getWormsFromGameLoop(i, j).getLife().getPv() + addIa);
      else if (this->getWormsFromGameLoop(i, j).getType() == HUMAN)
        this->getWormsFromGameLoop(i, j).setPv(this->getWormsFromGameLoop(i, j).getLife().getPv() + addHuman);
      tmpLife += this->getWormsFromGameLoop(i, j).getLife().getPv();
    }
    tmpListLife.push_back(tmpLife);
    this->listLifeScore.push_back(tmpListLife);
  }
}

void GameLoop::initTeams()
{
  this->changeLifeWorms();
  Spawn spawn(this->island, this->obj);
  Spawner spawner(spawn, this->teams);
  this->nbPlayer = 0;
  this->_widhWorms = this->getWormsFromGameLoop(0, 0).getWidth();
  this->_heightWorms = this->getWormsFromGameLoop(0, 0).getHeight();
}

void GameLoop::initDisplay(bool menu)
{
  Display disp(this->island, this->obj, this->teams, this->listPlayers, *this);

  this->lg.log("[GameLoopInit.cpp] - initDisplay\n");
  if (menu)
  {
    if (!this->exitGame)
    {
      disp.InitWindow();  //initialise la fenetre
      disp.CameraManager(); // initialise la camera
      disp.DispBackground("media/background/background.jpg"); //default background
    }
  }
  else
  {
    //menu off, start real game !
    std::cout << "start real game " << std::endl;

    return;
  }
  disp.DispMap();
  disp.Spawn();
  sf::Music music;

  music.openFromFile("media/SFX/gameSound.wav");
  if (!this->menuSet)
    {
      music.play();
      music.setLoop(true);
      //  music.setVolume(0);
    }
  disp.DispBackground("media/background/background.jpg");
  disp.DrawAll();
  if (!this->exitGame)
  {
    disp.DispMap();
    disp.Spawn();

    disp.DrawAll();
  }
}

///////////////////////////////////////////////////////
/////////////// get / set of times ////////////////////
///////////////////////////////////////////////////////

//////////////////////////////// set ////////////////////////

void GameLoop::setGlobaleTime()
{
  this->startGlobaleTime = std::clock();
}

void GameLoop::setWormsTime()
{
  this->startWormsTime = std::clock();
}

void GameLoop::setWaitTime()
{
  this->startWaitTime = std::clock();
}

void GameLoop::setWaitTimeAfterAttack()
{
  this->startWaitTimeAfterAttack = std::clock();
}

void GameLoop::setMenuTime()
{
  this->startMenuTime = std::clock();
}

//////////////////////////

void GameLoop::setPhase(int phase)
{
  this->phase = phase;
}

void GameLoop::setTmpDead(bool set)
{
  this->tmpDead = set;
}

void GameLoop::setWormsPlayer(int worms)
{
  this->nbPlayer = worms;
}

void GameLoop::setInventory(bool open)
{
  this->_inventoryIsOpen = open;
}

void GameLoop::setPreselectedInventory(int pres)
{
  this->_preselected = pres;
}

void GameLoop::setCurrentTimeWorms(int timeMaxMinus)
{
  this->startWormsTime = timeMaxMinus;
}

void GameLoop::setPaused(bool pause)
{
  this->_paused = pause;
}

void GameLoop::setMenuSelection(int menu)
{
  this->_menuSelection = menu;
}

//////////////////////////////// get ////////////////////////

std::clock_t GameLoop::getStartGlobaleTime() const
{
  return (this->startGlobaleTime);
}

std::clock_t GameLoop::getStartWormsTime() const
{
  return (this->startWormsTime);
}

std::clock_t GameLoop::getStartWaitTime() const
{
  return (this->startWaitTime);
}

std::clock_t GameLoop::getStartWaitTimeAfterAttack() const
{
  return (this->startWaitTimeAfterAttack);
}

std::clock_t GameLoop::getStartMenuTime() const
{
  return (this->startMenuTime);
}

////

double GameLoop::getCurrentGlobalTime() const
{
  return (( std::clock() - this->getStartGlobaleTime() ) / (double) CLOCKS_PER_SEC);
}

double GameLoop::getCurrentTimeWorms() const
{
  return (( std::clock() - this->getStartWormsTime() ) / (double) CLOCKS_PER_SEC);
}

double GameLoop::getCurrentWaitTime() const
{
  return (( std::clock() - this->getStartWaitTime() ) / (double) CLOCKS_PER_SEC);
}

double GameLoop::getCurrentTimeAfterAttackWorms() const
{
  return (( std::clock() - this->getStartWaitTimeAfterAttack() ) / (double) CLOCKS_PER_SEC);
}

double GameLoop::getCurrentMenuTime() const
{
  return (( std::clock() - this->getStartMenuTime() ) / (double) CLOCKS_PER_SEC);
}


///

double GameLoop::getWormsMaxTime() const
{
  return (this->wormsMaxTime);
}

double GameLoop::getMaxTimeBetweenWorms() const
{
  return (this->betweenWormsMaxTime);
}

int GameLoop::getPhase() const
{
  return (this->phase);
}

bool GameLoop::getTmpDead() const
{
  return (this->tmpDead);
}

int GameLoop::getWormsPlayer() const
{
  return (this->nbPlayer);
}

int GameLoop::getWidthWorm() const
{
  return (this->_widhWorms);
}

int GameLoop::getHeightWorms() const
{
  return (this->_heightWorms);
}

bool    GameLoop::getInventory() const
{
  return (this->_inventoryIsOpen);
}

int     GameLoop::getPreselectedInventory() const
{
  return (this->_preselected);
}

bool GameLoop::getPaused() const
{
  return (this->_paused);
}

int GameLoop::getMenuSelection() const
{
  return (this->_menuSelection);
}

std::vector<std::vector<int> > &GameLoop::getListLifeScore()
{
  return (this->listLifeScore);
}
