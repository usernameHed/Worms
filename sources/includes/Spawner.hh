#ifndef _SPAWNER_HH_
#define _SPAWNER_HH_

#include "Spawn.hh"
#include "Team.hh"

class Spawner
{
private:
  Spawn &spawn;
  std::vector<Team> &teams;
  unsigned int sizeTeam;
  unsigned int sizeObj;

  unsigned int startX = 0;
  unsigned int lengthX = 0;

public:
  Spawner(Spawn &spa, std::vector<Team> &tea);
  ~Spawner();

  void spawnTeam();
  void setLenghtX();

  void setTallWorms(unsigned int idTeam, unsigned int idWorms);
  void setPositionWorms(unsigned int idTeam, unsigned int idWorms, unsigned int x, unsigned int y);
  void setRotationWorms(unsigned int idTeam, unsigned int idWorms);
  void setLifePosition(unsigned int idTeam, unsigned int idWorms);
};


#endif /* !SPAWNER_HH_ */
