#ifndef _AIEXECUTE_HH_
# define _AIEXECUTE_HH_

#include <lua.hpp>
#include <iostream>
#include <vector>

#define AIFILE	"scripts/ai.lua"

struct	LUARes
{
  int	idWorms;
  int	weaponType;
};

struct	AIChoices
{
  bool	AT_WEAPONTYPE_001;
  bool	AT_WEAPONTYPE_002;
  bool	AT_WEAPONTYPE_003;
  int	GROUND_SIZE;
  int	DIST_NEAREST_ENEMY;
  int	CURRENT_LIFE;
  int	DISTANCE;
  int ID_WORMS;
  bool RIGHT;
};

class		AIExecute
{
public:
  AIExecute();
  virtual ~AIExecute();

private:
  lua_State	*_state;

public:
  LUARes	executeLUA(std::vector<AIChoices> &);
  void		errorLUA();
};

#endif /* !AIEXECUTE_HH_ */
