# Worms
Indie Studio is the **last C++ project** of your second year in Epitech. It consists in **programming a 3D video game** with real tools. We choose the Worms, the most difficult game (and the funiest) in the list of choice. The game had to feature specific functionnalities and **to offer a real gaming experience**. 
This project is normally done in groups of 7 in 4 month. We were 3, and we had 2 month:
 - Benjamin Goutfer - Project leader - It is in charge of communication, and helped me to AI
 - Illiasse Rifki - Graphist / UI - He is responsible for the graphic / GUI and library Irrlicht
 - Myself, Ugo Belfiore - I made the whole game engine

This is our WorldWarWorms 3D !

The target is to Reproduce an iconic game with a graphical library (Irrlicht) in C++ to confirm our OOP skills. The game must be multi-player, but must also be able to play alone against the computer.

Time duration is about 1000 hours on 5 weeks with hard rush the 2 last week. And about 200 coffee :)
An incredible project group.

 - Firstly, I have participated in the design of the game and the division of tasks.

 - I then coupled to the random generation of the map as well as all connected destruction functions: a long **rasterizing algorithm design.**. Indeed he had created a large map (more than 10000 * 10000), show circles, triangles, lines and polygons in 3D ... For optimization questions, the display of the map s is made using a unique 3D Obj. We had to create on the fly after each map destruction a new obj model. For this, Goutfer and I studied the models of ".obj" Simple File Blender 3d shapes. After a long work, we finaly got the algorithm for this:

![alt tag](https://raw.githubusercontent.com/usernameHed/Worms/master/ObjWorms.gif)

 - Once the displayed map, I made a long mork on variable management for random generation of the map. For the map is the most attractive, playable, challengeante for worms: **The map is Randomized, good looking, alterable on the fly and playable ! Hard work done !**
 
 - Finally, and not least, I handled entirely from the body of the game: the **gameLoop**, the **physics engine** and **weapons management.**
 - My friends responsable of the Graphic Library Irrlicht took charge of it, a very difficult task to do in C++. We worked together to link the map, display of games and HUD with the library
 
 - My second partner and I worked on the AI system of ennemy worms.

Here is the result of how to turn coffee into a game !
![alt tag](https://raw.githubusercontent.com/usernameHed/Worms/master/Worms.gif)

Here is the compilation !
![alt tag](https://raw.githubusercontent.com/usernameHed/Worms/master/CompileWorms.gif)
