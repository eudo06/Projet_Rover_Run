# Projet_Rover_Run



Rover Run

#Description

Rover Run est un projet en langage C visant à simuler le déplacement du rover MARC (Mars Rover Cartograph) sur une carte martienne. Le rover doit naviguer sur différents types de terrains, éviter les obstacles, et atteindre une station de base en minimisant les coûts associés à chaque déplacement. Ce projet met en œuvre des structures de données et des algorithmes pour la recherche du chemin optimal.

##Fonctionnalités

	1.	Chargement dynamique de cartes martiennes :
	•	Types de terrains : plaine, erg (sol meuble), reg (sol accidenté), crevasse, pente.
	2.	Calcul et utilisation d’un arbre des déplacements :
	•	Exploration de l’arbre pour trouver la meilleure séquence de mouvements.
	3.	Optimisation du chemin :
	•	Choix des déplacements minimisant les coûts associés à la carte.
	4.	Gestion des contraintes de terrain :
	•	Prise en compte des coûts spécifiques liés aux types de sols.
	•	Vérification des crevasses et des bords de carte.
	5.	Rapidité d’exécution :
	•	Mesure des temps d’exécution pour le calcul des coûts et la recherche dans l’arbre.

###Structure du projet

Le projet est organisé en plusieurs modules pour assurer la modularité et la clarté :
•	main.c : Point d’entrée du programme, gestion principale de l’exécution.

•	tree.c / tree.h : Construction et exploration de l’arbre des déplacements.

•	map.c / map.h : Chargement et gestion des cartes martiennes.

•	loc.c / loc.h : Mise à jour de la localisation du rover.

•	moves.c / moves.h : Gestion des mouvements disponibles pour chaque phase.

•	stack.c / stack.h : Structure pour gérer les séquences de mouvements.

•	queue.c / queue.h : File pour la gestion des voisins dans les calculs de coûts.

•	Fichiers .map : Cartes d’exemple (par exemple, example1.map, training.map).


#####Instructions d’installation

1.Compilation

Utilisez la commande suivante pour compiler le projet avec GCC :

gcc -o rover_run main.c tree.c loc.c map.c moves.c stack.c queue.c

2.Exécution

Une fois le programme compilé, exécutez-le avec :

./rover_run

3.Utilisation

	•	Placez les fichiers .map dans le répertoire attendu (par défaut, /mnt/data/maps ou dans le chemin défini dans le code).
	•	Utilisez les fichiers de carte fournis (example1.map, training.map) ou créez vos propres cartes pour tester.

Exemple de sortie

Voici un exemple de sortie obtenu après exécution avec une carte 7 x 6 :

Map created with dimensions 7 x 6
3 2 2 1 4 3
2 1 0 1 3 3
1 1 1 3 1 1
...

Temps écoulé récurssivité: 0.000145 secondes
Temps écoulé coûts minimal: 0.000015 secondes
Minimum cost leaf: 2
START -> T right -> F 10m -> T right -> F 20m
Temps écoulé récurssivité: 0.001220 secondes
Temps écoulé coûts minimal: 0.000136 secondes
Minimum cost leaf: 0
START -> F 10m -> T right -> F 10m -> F 10m -> B 10m
Number of phases: 2
Temps nécessaire pour conduire le robot à la base: 0.002141 secondes

######Tests effectués

	•	Cartes utilisées : example1.map et training.map.
	•	Fonctionnalités vérifiées :
	•	Chargement de la carte.
	•	Construction et exploration de l’arbre.
	•	Choix des séquences optimales.
	•	Prise en compte des types de terrains.
	•	Limites testées :
	•	Sortie de la carte.
	•	Gestion des crevasses.

######Limitations connues

	•	L’algorithme peut nécessiter des ajustements pour gérer des cartes très grandes ou des terrains complexes.
	•	Les tests peuvent être étendus pour vérifier des scénarios extrêmes.

Contributeurs

	•	Groupe PJT-B 2 - Rover Run

