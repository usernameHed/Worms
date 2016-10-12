# Worms
Indie Studio is the last C++ project of your second year in Epitech. It consists in programming a 3D video game with real tools. We choose the Worms, the most difficult game (and the funiest) in the list of choice. The game had to feature specific functionnalities and to offer a real gaming experience

This is our WorldWarWorms 3D !

The target is to Reproduce an iconic game with a graphical library (Irrlicht) in C++ to confirm our OOP skills.

Time duration is about 1000 hours on 5 weeks with hard rush the 2 last week. And about 200 coffee :)

Un incroyable projet de groupe. dans ce projet, j'ai d'abord participé à la conception du jeu et à la répartition des taches.

Je me suis ensuite attelé à la génération aléatoire de la map  ainsi que toutes les fonctions de destructions relié: une longue conception d'algorythme de rasterisation.
En effet il a fallut créé une map de grande taille (plus de 10000 * 10000), afficher des cercles, des triangles, des lignes et des polygones en 3D... Pour des questions d'optimisation, l'affichage de la map s'est faite à l'aide d'un unique Obj 3d, qu'il a fallu créé à la volé après chaque destructions de map.
Pour se faire, nous avons étudiés les modèles des ".obj", simple fichiers de formes 3d avec Blender.
Une fois le tout pris en main et la map affiché, j'ai effectué un long travail de gestion de variable et d'aléat pour que la génération aléatoire de la map soit jouable et attrayante, ainsi que chalengante pour un worms3d.

Lorsque la création / destruction d'une map à été effectué,