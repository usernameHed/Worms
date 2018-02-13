//
// Sound.cpp for  in /home/rifki_i/rushFinal/cpp_indie_studio
//
// Made by 
// Login   <@epitech.net>
// 
// Started on  Thu Jun  2 20:10:44 2016 
// Last update Fri Jun  3 00:32:33 2016 
//

#include "Sound.hh"
#include <iostream>

Sound::Sound()
{}

Sound::~Sound()
{}

void Sound::PlaySound(std::string pathSound, sf::Sound* sound)
{
  if (!this->buffer.loadFromFile(pathSound))
    return;
  sound->setBuffer(this->buffer);
  sound->play();
  return;
}

void Sound::PlayMusic(std::string pathSound, sf::Music* music)
{
  music->openFromFile(pathSound.c_str());
  music->play();
  return;
}


void Sound::PlayLoopMusic(std::string pathSound, sf::Music* music)
{
  music->openFromFile(pathSound.c_str());
  music->play();
  music->setLoop(true);
  return;
}

void Sound::SetVolumeMusic(sf::Music* music, int volume)
{
  music->setVolume(volume);
}

void Sound::StopMusic(sf::Music* music)
{
  music->stop();
}
