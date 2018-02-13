#include		"driverChoice.h"

#include		"GameLoop.hh"
#include		"Display.hh"
#ifndef _WIN32
#include <unistd.h>
#else
#include <Windows.h>
#endif
#include		<iostream>

void		Display::CameraManager()
{
	if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
		return;

  int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];

  int X = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int Y = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y;

  //Noeud parent, vitesse rotation, vitesse deplacement, ID, keymap, taille de cam;
  this->cam = this->_smgr->addCameraSceneNode(0, vector3df(0,0,10), vector3df(0,0,20));
  this->cam->setFOV(cam->getFOV());
  this->setNewCameraPos(0, 0, 1);
}

void    Display::setZoomPlayer()
{
  if (!this->checkNbPlayer(this->gameloop.getWormsPlayer()))
    return;
  int idTeam = this->listPlayers[this->gameloop.getWormsPlayer()][0];
  int idWorms = this->listPlayers[this->gameloop.getWormsPlayer()][1];

  int X = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().x;
  int Y = this->gameloop.getWormsFromGameLoop(idTeam, idWorms).getPos().y;

  std::cout << "X: " << X << std::endl; 
  float y = -14 + (Y * 0.0266);
  float x = (X * 0.0266) - 25.4;
  std::cout << "x: " << x << std::endl;
  core::vector3df player = vector3df(x, -y, 0);
  cam->setPosition(player);
  player.Z = 20;
  cam->setTarget(player);
}
void    Display::setCameraPosition()
{
}


void Display::setNewCameraPos(float x, float y, float z)
{
}

void Display::zoomIn(float zoom)
{
}
