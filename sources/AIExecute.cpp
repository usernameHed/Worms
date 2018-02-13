#include "AIExecute.hh"
#include <sstream>

AIExecute::AIExecute()
{
  this->_state = luaL_newstate();
}

AIExecute::~AIExecute()
{

}

LUARes	AIExecute::executeLUA(std::vector<AIChoices> &avChoices)
{
  int	result;
  LUARes res;

  res.idWorms = -1;
  res.weaponType = -1;
  luaL_openlibs(_state);
  result = luaL_loadfile(_state, AIFILE);

  if ( result != LUA_OK )
    {
      errorLUA();
      return res;
    }

  lua_newtable(_state);
  for (int i = 0; i < avChoices.size(); i++)
    {
      lua_newtable(_state);

      lua_pushnumber(_state, avChoices[i].AT_WEAPONTYPE_001);
      lua_setfield(_state, -2, "awt1");

      lua_pushnumber(_state, avChoices[i].AT_WEAPONTYPE_002);
      lua_setfield(_state, -2, "awt2");

      lua_pushnumber(_state, avChoices[i].AT_WEAPONTYPE_003);
      lua_setfield(_state, -2, "awt3");

      lua_pushnumber(_state, avChoices[i].ID_WORMS);
      lua_setfield(_state, -2, "wormsId");

      lua_pushnumber(_state, avChoices[i].CURRENT_LIFE);
      lua_setfield(_state, -2, "currentLife");

      lua_pushnumber(_state, avChoices[i].GROUND_SIZE);
      lua_setfield(_state, -2, "groundSize");

      lua_pushnumber(_state, avChoices[i].DISTANCE);
      lua_setfield(_state, -2, "distance");

      lua_pushnumber(_state, avChoices[i].DIST_NEAREST_ENEMY);
      lua_setfield(_state, -2, "distNearestEnemy");

      lua_rawseti(_state, -2, i+1);
    }
  lua_setglobal(_state, "data");

  result = lua_pcall(_state, 0, LUA_MULTRET, 0);
  if ( result != LUA_OK )
    {
      errorLUA();
      return res;
    }

    bool ok = false;
    std::stringstream str_buf;
    while(lua_gettop(_state))
    {
        str_buf.str(std::string());
        str_buf << " ";
        switch(lua_type(_state, lua_gettop(_state)))
        {
        case LUA_TNUMBER:
            if (ok)
              res.idWorms = lua_tonumber(_state, lua_gettop(_state));
            else
              res.weaponType = lua_tonumber(_state, lua_gettop(_state));
            ok = true;
            break;
        default:
            str_buf << "script returned an unknown-type value";
        }
        lua_pop(_state, 1);
        std::cout << str_buf.str() << std::endl;
    }
  std::cout << "RES.IDWORMS = " << res.idWorms << std::endl;
  std::cout << "RES.WEAPONT = " << res.weaponType << std::endl;

  lua_pop(_state, 1);
  return (res);
}

void	AIExecute::errorLUA()
{
  printf("%s\n", lua_tostring(_state, -1));
  lua_pop(_state, 1);
}
