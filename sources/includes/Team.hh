#ifndef _TEAM_HH_
# define _TEAM_HH_

#include "Worms.hh"
#include <vector>

#define MAX_WORMS_PER_TEAM  (4)
#define MAX_TEAMS           (4)
class Team
{
private:
  std::vector<Worms>  _worms;
  unsigned int        _id;
  unsigned int        _maxWorms;

public:
  Team(unsigned int id = 42, unsigned int maxWorms = MAX_WORMS_PER_TEAM);
  virtual ~Team();
  bool addWorms(Worms const &worms);
  Worms &getWorms(int id);
  void removeLastWorms();
  unsigned int getTeamNbWorms() const;
  int getTeamNbWormsAlive() const;
  unsigned int getId() const;
};

#endif /* !TEAM_HH_ */
