#ifndef _AICORE_HH_
# define _AICORE_HH_

#include "AIExecute.hh"
#include "Worms.hh"
#include "Team.hh"
#include "Display.hh"

#define XORSWAP(a, b)   ((&(a) == &(b)) ? (a) : ((a)^=(b),(b)^=(a),(a)^=(b)))

enum	ATWeapons
{
  UNAVAIBLE = -1,
  UNAT = 0,
  AT = 1,
};

class	AICore
{
public:
  AICore(Display &display);
  virtual ~AICore();

private:
  Display &display;
  std::vector<AIChoices> _avAiChoices;
  int idTeamPlayer;
  int idWormsPlayer;

  int deplacement = 0;
  int maxDeplacement = 200;


  int				currentLife;
  int       groundSize;
  AIExecute			brain;

public:
  void	fillArray();

  void	isAtWeapon1(AIChoices &choice, int);
  void	isAtWeapon2(AIChoices &choice, int);
  void	isAtWeapon3(AIChoices &choice, int);

  void	getGroundSize(AIChoices &choice, int);
  void	getGroundSize();

  void	getDistance(AIChoices &choice, int);
  void	getCurrentLife(AIChoices &choice, int);
  void	getNearestEnemy(AIChoices &choice, int);
  void getId(AIChoices &choice, int);
  void getDirection(AIChoices &choice, int);

  LUARes	executeBrain();
};

#endif /* !AICORE_HH_ */
