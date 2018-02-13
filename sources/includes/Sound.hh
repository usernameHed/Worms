#ifndef _SOUND_HH_
# define _SOUND_HH_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#ifndef _WIN32
	#include <unistd.h>
#else
	#include <Windows.h>
#endif


class Sound
{
public:
  Sound();
  ~Sound();
  void PlayMusic(std::string, sf::Music*);
  void PlayLoopMusic(std::string, sf::Music*);
  void SetVolumeMusic(sf::Music*, int);
  void StopMusic(sf::Music*);

  void PlaySound(std::string, sf::Sound*);
  // void PlayLoopSound(std::string, sf::Music*);
  // void SetVolumeSound(sf::Music*, int);
  // void StopSound(sf::Music*);
private:
  sf::SoundBuffer buffer;
};

#endif
