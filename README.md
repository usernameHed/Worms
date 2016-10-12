# Worms
Indie Studio is the **last C++ project** of your second year in Epitech. It consists in **programming a 3D video game** with real tools. We choose the Worms, the most difficult game (and the funiest) in the list of choice. The game had to feature specific functionnalities and **to offer a real gaming experience**

This is our WorldWarWorms 3D !

The target is to Reproduce an iconic game with a graphical library (Irrlicht) in C++ to confirm our OOP skills. The game must be multi-player, but must also be able to play alone against the computer.

Time duration is about 1000 hours on 5 weeks with hard rush the 2 last week. And about 200 coffee :)
An incredible project group.

 - Firstly, I have participated in the design of the game and the division of tasks.

 - I then coupled to the random generation of the map as well as all connected destruction functions: a long **rasterizing algorithm design.**. Indeed he had created a large map (more than 10000 * 10000), show circles, triangles, lines and polygons in 3D ... For optimization questions, the display of the map s is made using a unique 3D Obj, he had created on the fly after each map destruction. For this, we studied the models of ".obj" Simple File Blender 3d shapes.

![alt tag](https://raw.githubusercontent.com/usernameHed/Worms/master/ObjWorms.gif)


Une fois le tout pris en main et la map affiché, j'ai effectué un long travail de gestion de variable et d'aléat pour que la génération aléatoire de la map soit jouable et attrayante, ainsi que challengante pour un worms !

Lorsque la création / destruction d'une map à été effectué, je me suis occupé entièrement du corps du jeu: la gameloop (boucle de jeu), le moteur physique ainsi que la gestion des armes et la liaison avec le graphique et l'implémentation de l'IA.

Here is the result of how to turn coffee in a game:
![alt tag](https://raw.githubusercontent.com/usernameHed/Worms/master/Worms.gif)

Here is the compilation !
![alt tag](https://raw.githubusercontent.com/usernameHed/Worms/master/CompileWorms.gif)