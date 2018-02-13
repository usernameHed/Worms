LIBS		=	-ldl
PROJECT_NAME	=	indieStudio
DEST_PATH	=	$(PROJECT_NAME)$(SUFFIX)

SOURCES		=	sources/AddWater.cpp		\
			sources/AICore.cpp		\
			sources/AIExecute.cpp		\
			sources/Bullet.cpp		\
			sources/Circle.cpp		\
			sources/Cryptor.cpp		\
			sources/DisplayInit.cpp	\
			sources/Display.cpp		\
			sources/DisplayHUD.cpp		\
			sources/DisplayIa.cpp	\
			sources/DisplayWeapons.cpp	\
			sources/DisplayMenu.cpp		\
			sources/DisplayEvent.cpp	\
			sources/DisplayPhysics.cpp	\
			sources/DisplayFunctions.cpp	\
			sources/DisplayCamera.cpp	\
			sources/Dynamit.cpp		\
			sources/Drill.cpp		\
			sources/EventHandler.cpp	\
			sources/Forme2D.cpp		\
			sources/GameLoopInit.cpp	\
			sources/GameLoopFunctions.cpp	\
			sources/Grass.cpp		\
			sources/Grenade.cpp		\
			sources/Hole.cpp		\
			sources/IaThinking.cpp	\
			sources/IslandGenerator.cpp	\
			sources/Life.cpp		\
			sources/Line.cpp		\
			sources/Log.cpp	\
			sources/LineMaker.cpp		\
			sources/Map.cpp			\
			sources/MapOptimizor.cpp	\
			sources/Menu.cpp	\
			sources/RandNano.cpp		\
			sources/Rasterization.cpp	\
			sources/Rocket.cpp		\
			sources/Spawn.cpp		\
			sources/Spawner.cpp		\
			sources/Sound.cpp	\
			sources/StringObject.cpp	\
			sources/Team.cpp		\
			sources/Triangle.cpp		\
			sources/VecToObj.cpp		\
			sources/Weapons.cpp 		\
			sources/Worms.cpp		\
			sources/main.cpp		\

OBJECTS		=	$(SOURCES:.cpp=.o)

IRRLICHT_HOME	=	library/Irrlicht
CPPFLAGS	=	-I$(IRRLICHT_HOME)/include -I./sources/includes -I./library/Sfml/include
CPPFLAGS	+= 	-std=c++11 -I/usr/X11R6/include -I/usr/local/include -I./library/Lua/src53
CPPFLAGS	+=	-g -g3 -O3 -ffast-math ##TODO -W -Wall -Wextra -Werror
COMP		=	clang++ ##TODO g++

LINUX_FLAGS	= 	-L$(IRRLICHT_HOME)/lib/Linux -lIrrlicht -lpthread -L./library/Lua/src53 -llua -L/usr/lib/x86_64-linux-gnu/ -ldl
LINUX_FLAGS	+=	-L/usr/X11R6/lib$(LIBSELECT) -lGL -lXext -lXxf86vm -lX11 -L./library/Sfml/lib -lsfml-audio -lsfml-system -lsfml-window -lsfml-graphics

MAC_FLAGS	=	-L$(IRRLICHT_HOME)/lib/Mac -lIrrlicht -lpthread -L/usr/local/lib -llua -L./library/Sfml/lib -lsfml-audio
MAC_FLAGS	+=	-I/usr/X11R6/include -L/usr/local/include -L/usr/X11R6/lib -dylib_file /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib:/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib -framework Cocoa -framework OpenGL -framework IOKit -framework Carbon

all		: Linux

INSTALL_LINUX	:
		  sudo apt-get -y install build-essential xserver-xorg-dev x11proto-xf86vidmode-dev libxxf86vm-dev mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev libxext-dev libxcursor-dev subversion

INSTALL_LUA	:
		  cd library/Lua && $(MAKE) linux
		  $(MAKE) install

INSTALL_LUA_MAC	:
		  cd library/Lua && $(MAKE) macosx && $(MAKE) install

Linux		: $(OBJECTS)
		  $(CXX) $(OBJECTS) $(CPPFLAGS) $(LINUX_FLAGS) -o $(DEST_PATH) $(LDFLAGS) $(LIBS)
		  echo "export LD_LIBRARY_PATH=./library/Sfml/lib" >> ~/.bashrc
		  source ~/.bashrc
		  ./indieStudio

Mac		: $(OBJECTS)
		  $(COMP) $(MAC_FLAGS) $(LDFLAGS) $(OBJECTS) -o $(DEST_PATH)

clean		:
		  rm -rf $(OBJECTS)

fclean		: clean
		  rm -rf $(DEST_PATH)
		  rm -rf *.worms

reMac		: clean fclean Mac
reWindows	: clean fclean Windows
re		: clean fclean Linux

ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif

ifeq ($(HOSTTYPE), sun4)
LDFLAGS += -lrt
endif
