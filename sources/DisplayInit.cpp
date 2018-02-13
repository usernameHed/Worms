#include	   "GameLoop.hh"
#include		 "Menu.hh"
#include	   "Display.hh"
#ifndef		_WIN32
  #include <unistd.h>
#else
  #include <Windows.h>
#endif

Display::Display(IslandGenerator &is, StringObject const &object, std::vector<Team> &tea, std::vector<std::vector<int> > &list, GameLoop &game)
  : island(is), obj(object), team(tea), listPlayers(list), gameloop(game)
{
  this->weapons = new Weapons(this->gameloop);
}

Display::~Display()
{

}

///////////////////////////////// get set ///////////////////
GameLoop &Display::getGame()
{
  return (this->gameloop);
}

IslandGenerator &Display::getIsland()
{
  return (this->island);
}

Weapons *Display::getWeapons()
{
  return (this->weapons);
}

IVideoDriver *Display::getDriver()
{
  return (this->_driver);
}

IGUIEnvironment *Display::getEnv()
{
  return (this->_env);
}
