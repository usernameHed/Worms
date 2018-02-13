--[[data = {
  {
    awt1 = 0,
    awt2 = 0,
    awt3 = 0,
    distance = 30,
    groundSize = 20,
    distNearestEnemy = 30,
    currentLife = 0,
    wormsId = 0
  },
  {
    awt1 = 1,
    awt2 = 0,
    awt3 = 0,
    distance = 30,
    groundSize = 20,
    distNearestEnemy = 30,
    currentLife = 0,
    wormsId = 1
  },
  {
    awt1 = 0,
    awt2 = 0,
    awt3 = 0,
    distance = 10,
    groundSize = 20,
    distNearestEnemy = 10,
    currentLife = 0,
    wormsId = 2
  },
  {
    awt1 = 1,
    awt2 = 0,
    awt3 = 0,
    distance = 20,
    groundSize = 20,
    distNearestEnemy = 20,
    currentLife = 0,
    wormsId = 3
  }
}]]

local function checkPriorityMelee()
  local distance = -1
  local wormsId = -1
  local i = 1

  while i ~= #data + 1 do
    print("Checking atw1 for worms " .. data[i].wormsId .." ("..data[i].distance.."/"..data[i].awt1..")")
    print("MinDistance = "..distance)
    print("AtWorms = "..wormsId)
    print("")
    if (data[i].awt1 == 1 and (data[i].distance < distance or distance == -1)) then
      distance = data[i].distance
      wormsId = data[i].wormsId
    end
    i = i + 1
  end
  return wormsId, 0
end

local function checkPriorityRect()

end

local function checkPriorityParabol()

end

local function checkPriorityGround()

end

local function checkPriorityDistE()

end

local function checkPriorityDist()

end

local function checkPriorityLife()

end

-- DEFINES
  local PRIORITY =  {{level = 9, fct = checkPriorityMelee},
                    {level = 4, fct = checkPriorityRect},
                    {level = 2, fct = checkPriorityParabol},
                    {level = 0, fct = checkPriorityGround},
                    {level = 5, fct = checkPriorityDistE},
                    {level = 3, fct = checkPriorityDist},
                    {level = 8, fct = checkPriorityDist}}

-- DUMPERs MOTOR --
require "scripts.dumper"
function dump(...)
  print(DataDumper(...), "\n")
end
---- DUMPERs MOTOR END

-- AI BRAIN --
io.write("[LUA] Fetching array from C++ ...\n")
print(dump(data))
--print(dump(PRIORITY))

local attackWorms = -1
local weaponType = -1

attackWorms, weaponType = checkPriorityMelee()

print("["..attackWorms.." <> "..weaponType.."]")
return attackWorms, weaponType
---- AI BRAIN END
