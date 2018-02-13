#include "Team.hh"

Team::Team(unsigned int id, unsigned int maxWorms) : _id(id), _maxWorms(maxWorms)
{
  std::cout << "\033[1;31mCreating new Team with id [" << id << "] and [" << maxWorms << "] worms max\033[0m" << std::endl;
}

Team::~Team()
{

}

bool Team::addWorms(Worms const &worms)
{
  if (this->_worms.size() >= this->_maxWorms)
    return (false);
  this->_worms.push_back(worms);
  return (true);
}

Worms &Team::getWorms(int id)
{
  return (this->_worms[id]);
}

void Team::removeLastWorms()
{
  this->_worms.pop_back();
}

unsigned int Team::getTeamNbWorms() const
{
  return (this->_worms.size());
}

int Team::getTeamNbWormsAlive() const
{
  int count = 0;
  size_t i = 0;

  while (i < this->_worms.size())
  {
    //if (this->_worms[i].get
    if (this->_worms[i].getLife().isAlive())
      count++;
  }

  return (count);
}

unsigned int Team::getId() const
{
  return (this->_id);
}
