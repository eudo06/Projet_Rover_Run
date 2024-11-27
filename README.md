# Projet_Rover_Run




Rover Run

##Description

Rover Run est un projet en langage C simulant les déplacements du rover MARC sur une carte martienne. L’objectif est de guider MARC vers une base en tenant compte des coûts associés aux différents terrains (plaine, erg, reg, crevasse, etc.). Ce projet intègre un menu interactif permettant de tester différentes fonctionnalités du programme.

##Fonctionnalités

	1.	Menu interactif :
	•	Sélection de la carte à utiliser (example1.map ou other.map).
	•	Options pour tester différentes parties du programme.
	2.	Gestion des cartes :
	•	Chargement dynamique de cartes martiennes définies dans des fichiers .map.
	•	Affichage des dimensions, types de terrains, et coûts associés.
	3.	Déplacement de MARC :
	•	Simulation des mouvements de MARC sur la carte jusqu’à la base.
	•	Gestion des coûts de déplacements en fonction des types de terrains.
	4.	Tests intégrés :
	•	Vérification des fonctionnalités liées aux cartes, à la localisation, et aux mouvements.
	5.	Temps d’exécution :
	•	Mesure du temps nécessaire pour conduire MARC à la base.

##Structure du projet

Le projet est organisé en plusieurs fichiers pour assurer une modularité et une clarté optimales :
•	main.c : Point d’entrée principal du programme, avec le menu interactif.

•	map.c / map.h : Gestion des cartes (chargement, affichage, calcul des coûts).

•	loc.c / loc.h : Gestion de la localisation du rover (position et orientation).

•	tree.c / tree.h : Gestion de l’arbre des déplacements.

•	moves.c / moves.h : Gestion des mouvements possibles de MARC.

•	queue.c / queue.h : Gestion des files pour explorer les voisins.

•	stack.c / stack.h : Gestion des piles pour stocker les mouvements.

•	test.c / test.h : Tests pour vérifier le fonctionnement des différentes fonctionnalités.

•	Fichiers .map :

•	example1.map : Carte normale.

•	other.map : Carte complexe pour des tests avancés.

##nstructions d’installation

1.Compilation

Utilisez la commande suivante pour compiler le projet avec GCC :

gcc -o rover_run main.c map.c loc.c tree.c moves.c queue.c stack.c test.c -I.

2.Exécution

Exécutez le programme avec :

./rover_run

3.Instructions d’utilisation

	1.	Sélection de la carte :
	•	Lorsque vous exécutez le programme, vous devez d’abord choisir entre example1.map et other.map.
	•	Assurez-vous que les fichiers .map sont placés dans le dossier ../maps/.
	2.	Menu principal :
	•	Vous pouvez choisir entre plusieurs options :
	•	Conduire MARC à la base.
	•	Tester les fonctionnalités liées aux cartes.
	•	Tester la localisation et les mouvements.
	3.	Déplacements de MARC :
	•	Saisissez la position de départ (x, y) et l’orientation (NORTH, EAST, SOUTH, WEST).

4.Exemple de sortie

Voici un exemple de sortie avec example1.map :

=== MENU ===
1. Driving Marc to the base
2. Testing of map functions (map)
3. Testing of localisation functions (loc)
4. Testing of movements functions (moves)
0. Quit
   Your choice : 1

[INFO] Driving Marc to the base...
Enter the starting position x y : 4 4
Enter the starting orientation (0=NORTH, 1=EAST, 2=SOUTH, 3=WEST) : 2
Map created with dimensions 7 x 6
3 2 2 1 4 3
2 1 0 1 3 3
...

Time needed to drive Marc to the base : 0.002141 secondes

##Tests effectués

	1.	Fonctionnalités testées :
	•	Chargement et affichage des cartes.
	•	Mise à jour de la localisation après un mouvement.
	•	Simulation complète du déplacement vers la base.
	2.	Cartes utilisées :
	•	example1.map : Carte normale.
	•	other.map : Carte complexe avec des terrains combinés.

##Limitations connues

	•	L’algorithme peut nécessiter des ajustements pour des cartes très grandes ou très complexes.
	•	La gestion des terrains spéciaux comme les crevasses est partiellement implémentée.

##Contributeurs

	•	Kouadio Bli Jean Eudes
	•	Ismaël Sangaré
	•	Boudnoma Bienvenu Juvénis Fortune KABORE
    	(Groupe PJT-B 2 - Rover Run)

