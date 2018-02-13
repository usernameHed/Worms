#include <iostream>
#include <vector>
#include "Team.hh"
#include "GameLoop.hh"
#include "RandNano.hh"
#include "Menu.hh"

/*
** Lancement du menu
** TODO: scène 1 et 2 du menu
** Ici représente la scène 3 du menu
*/

int main()
{
  /* initialisation du random en nanoseconde pour tout le projet */
  RandNano	r;

  /*
  ** TODO: SCENE 3 DU MENU (A LANCER VIA UNE CLASS)
  ** Cette class va utiliser le vector TEAM pour remplire
  ** les infos
  **
  ** Ensuite: cette class appelle Gameloop en envoyant
  ** en paramettre les information Teams
  */

  //call generic:
  //Generic gen;
/////////////////////////////////////////class start here

  //Menu menu;
  //menu.createMenu();


  /* création du vector TEAM */
  std::vector<Team> teams;
  for (size_t i = 0; i < MAX_TEAMS; i++)
  {
    teams.push_back(Team(i));
    for (size_t j = 0; j < MAX_WORMS_PER_TEAM; j++)
    {
      if (i == 1)
        teams[i].addWorms(Worms(j, i, HUMAN, "adolf", 100, LEFT));
      else
        teams[i].addWorms(Worms(j, i, IA, "adolf", 100, LEFT));
    }
  }
  GameLoop game(teams);

////////////////////////////////////////class end here
  return (0);
}
