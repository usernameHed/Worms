#include "Display.hh"

void Display::affNameHUD()
{
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
    return;
  int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];
  std::string name = "media/names/" + this->getGame().getWormsFromGameLoop(idTeam, idWorms).getName() + ".png";
  nameSprite = _env->addImage(_driver->getTexture(name.c_str()), core::position2d<int>(WINDOW_SIZE_X / 2.5f, WINDOW_SIZE_Y / 1.06));
}


void Display::affWeaponsHUD()
{
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
    return;

  int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];
  static int i = false;
 int z = this->getGame().getWormsFromGameLoop(idTeam, idWorms).getWeaponsType();
  std::string weaponPath = "media/hud/weapon" + std::to_string (z) + ".png";
  if (i == true)
    weaponSprite->remove();
    weaponSprite = _env->addImage(_driver->getTexture(weaponPath.c_str()), core::position2d<int>(10, 5));
  i = true;
}

void Display::affLifeHUD()
{
  //static int previousLife = -1;
  static bool first = false;
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
  {
    //no one is playing
    if (first)
      lifeDisp->remove();
    return;
  }

  int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];
  int life = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getLife().getPv();

  //if (life == previousLife)
  //return;

  if (first)
    lifeDisp->remove();

  first = true;
  //previousLife = life;

  float disp = 1770;
  std::cout << "life: " << life << std::endl;

  std::string str = std::to_string(life);

  int x = 0;
  while (str[x])
    {
      lifeDisp = affNumb(str[x] - 48, disp, 20);
      disp += 50;
      x++;
    }
}

IGUIImage *Display::affNumb(int timer, float x, float y)
{
  std::string tmp = "media/numbers/" + std::to_string(timer) + ".png";
  return (_env->addImage(_driver->getTexture(tmp.c_str()), core::position2d<int>(x, y)));
}

void Display::affTime(int timing)
{

  static bool timerIsDisplayed = false;
  static bool timer2IsDisplayed = false;

  if (timerIsDisplayed && timer2IsDisplayed)
    {
      timerDisp->remove();
      timerDisp2->remove();
    }
  else if (timerIsDisplayed)
    timerDisp->remove();

  int timer1 = 0;
  int timer2 = 0;

  if (this->gameloop.menuSet)
    return;
  if (timing >= 10)
    {
      timer1 = timing % 10;
      timerDisp = affNumb(timer1, WINDOW_SIZE_X / 1.98, 5);
      timer2 = timing % 100 / 10;
      if (timer2 != 0)
	{
	  timerDisp2 = affNumb(timer2, WINDOW_SIZE_X / 2.08, 5);
	  timer2IsDisplayed = true;
	}
      else
	timer2IsDisplayed = false;
      timerIsDisplayed = true;
    }
  else
    {
      timer1 = timing;
      timerDisp = affNumb(timer1, WINDOW_SIZE_X / 2.02, 5);
      timerIsDisplayed = true;
      timer2IsDisplayed = false;
    }
}
