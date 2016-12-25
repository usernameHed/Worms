# Worms
Indie Studio is the **last C++ project** of your second year in Epitech (IT school in Montpellier). It consists in **programming a 3D video game** with real tools. We choose the Worms, the most difficult game (and the funniest) in the list of choice. The game had to feature specific functionalities  and **to offer a real gaming experience**. 
This project is normally done in groups of 7 in 4 months. We were 3, and we had 2 months:
 - Benjamin Goutfer - Project leader - He is in charge of communication, and helped me with AI (Artificial Intelligence)
 - Illiasse Rifki - Graphist / UI - He is responsible for the graphic / GUI and library Irrlicht
 - Myself, Ugo Belfiore - I was in charge of the management of the game developement for the whole game engine.

This is our WorldWarWorms 3D!

The target is to reproduce an iconic game with a graphical library (Irrlicht) in C++ to confirm our OOP skills. The game must be multi-player, but must also be able to play alone against the computer.

Time duration is about 1000 hours on 5 weeks with hard rush the 2 last weeks. And about 200 coffees :)
An incredible project group.

 - Firstly, I was in charge of the project managment I have participated in the design of the game and the division of tasks.

 - I then coupled to the random generation of the map as well as all connected destruction functions: a long **rasterizing algorithm design.**. Indeed it had created a large map (more than 10.000 * 10.000), show circles, triangles, lines and polygons in 3D ... For optimization questions, the display of the map s is made using a unique 3D Obj. We had to create on the fly after each map destruction a new obj model. For this, Goutfer and I studied the models of ".obj" Simple File Blender 3d shapes. After a long work, we finaly got the algorithm for this:

![alt tag](https://raw.githubusercontent.com/usernameHed/Worms/master/ObjWorms.gif)

 - Once the map has been displayed, I made a long management work on variable in order to generate the map randomly so as to make it the most attractive, playable, challenging for the player: **The map is randomized, good looking, alterable on the fly and playable ! Hard work done!**
 
 - Finally, and not least, I handled entirely the game design: the **gameLoop**, the **physics engine** and **weapons management.**
 - Illiasse, responsable of the Graphic Library Irrlicht took charge of it, a very difficult task to do in C++. We worked together to link the map, display and HUD of games with the library.
 
 - My second partner and I worked on the AI system of ennemy worms.

Here is the result of how to turn coffee into a game !
![alt tag](https://raw.githubusercontent.com/usernameHed/Worms/master/Worms.gif)

Here is the compilation !
![alt tag](https://raw.githubusercontent.com/usernameHed/Worms/master/CompileWorms.gif)

Youtube: https://www.youtube.com/watch?v=AsmTaDdmi34

Worms gameplay: https://youtu.be/AsmTaDdmi34

Worms Map Obj: https://youtu.be/GwvtKQPFBtc

Worms compilation: https://youtu.be/Xzk8UXcJUc8
