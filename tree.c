//
// Created by fortu on 11/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#define NUM_MOVEMENTS 7
#define PHASE_MOVES  5

p_node createNode(t_localisation loc, t_soil soil_type, int cost, int nbSons, p_node parent) {
    p_node node = malloc(sizeof(t_node));
    if (!node) return NULL;

    node->loc = loc;
    node->soil_type = soil_type;
    node->cost = cost;
    node->nbSons = nbSons;
    node->parent = parent;
    node->sons = malloc(nbSons * sizeof(p_node));

    if (!node->sons) {
        free(node);
        return NULL;
    }

    for (int i = 0; i < nbSons; i++)
        node->sons[i] = NULL;

    return node;
}

p_node addSon(p_node parent, t_move mov, int nbSons, t_map map) {
    t_localisation loc = move(parent->loc, mov);


    if (!isValidLocalisation(loc.pos, map.x_max, map.y_max))
        return NULL;


    int new_cost = map.costs[loc.pos.y][loc.pos.x];
    p_node son = createNode(loc, map.soils[loc.pos.y][loc.pos.x], new_cost, nbSons, parent);

    if (!son)
        return NULL;

    son->move_from_parent = mov;


    for (int i = 0; i < nbSons; i++) {
        if (parent->sons[i] == NULL) {
            parent->sons[i] = son;
            break;
        }
    }

    return son;
}


p_node findMinCostLeaf(p_node root) {
    if (root->nbSons == 0) {
        return root;  // Si aucun fils, c'est une feuille
    }

    p_node minLeaf = NULL;
    int minCost = 2000;

    for (int i = 0; i < root->nbSons; i++) {
        p_node leaf = findMinCostLeaf(root->sons[i]);
        if (leaf->cost < minCost) {
            minCost = leaf->cost;
            minLeaf = leaf;
        }
    }
    return minLeaf;
}

void printPathToRoot(p_node leaf) {
    if (leaf == NULL) return;

    // Appel récursif pour atteindre la racine
    if (leaf->parent != NULL) {
        printPathToRoot(leaf->parent);
        // Affiche le mouvement pour arriver jusqu'au nœud actuel
        printf(" -> %s", getMoveAsString(leaf->move_from_parent));
    } else {
        // Premier nœud (racine)
        printf("START");
    }
}
void printTree(p_node root, int level) {
    if (root == NULL) return;

    // Indentation pour montrer le niveau dans l'arbre
    for (int i = 0; i <= level; i++) printf("  ");
    printf("Position (%d, %d), Orientation %d, Cost: %d\n", root->loc.pos.x, root->loc.pos.y, root->loc.ori, root->cost);

    // Appel récursif pour chaque enfant (fils) du noeud actuel
    for (int i = 0; i < root->nbSons; i++) {
        printTree(root->sons[i], level + 1);
    }
}


// Fonction pour libérer toute la mémoire allouée pour l'arbre
void freeTree(p_node root) {
    if (root == NULL) return;

    // Libère chaque enfant (fils) du noeud actuel
    for (int i = 0; i < root->nbSons; i++) {
        freeTree(root->sons[i]);
    }

    // Libère le tableau de pointeurs vers les fils
    free(root->sons);
    // Libère le noeud lui-même
    free(root);
}


// Tableau des disponibilités initiales des mouvements
int movement_availability[NUM_MOVEMENTS] = {22, 15, 7, 7, 21, 21, 7};

// Fonction pour réinitialiser les disponibilités des mouvements à chaque phase
void resetMovementAvailability() {
    // Les disponibilités initiales sont définies ici
    const int default_availability[NUM_MOVEMENTS] = {22, 15, 7, 7, 21, 21, 7};

    // Réinitialise chaque disponibilité de mouvement
    for (int i = 0; i < NUM_MOVEMENTS; i++) {
        movement_availability[i] = default_availability[i];
    }
}

// Fonction pour tirer un mouvement au hasard selon les disponibilités restantes
int drawRandomMovement() {
    // Calcule la somme totale des mouvements disponibles
    int total = 0;
    for (int i = 0; i < NUM_MOVEMENTS; i++) {
        total += movement_availability[i];
    }

    // Vérifie s'il reste des mouvements disponibles
    if (total == 0) {
        return -1; // Aucun mouvement disponible
    }

    // Génère un choix aléatoire basé sur la disponibilité des mouvements
    int choice = rand() % total;

    // Parcourt les mouvements et sélectionne celui correspondant à 'choice'
    for (int i = 0; i < NUM_MOVEMENTS; i++) {
        if (choice < movement_availability[i] && movement_availability[i] > 0) {
            movement_availability[i]--;
            return i;
        }
        choice -= movement_availability[i];
    }

    return -1; // Au cas où aucun mouvement n'a été sélectionné, ce qui ne devrait pas arriver
}

void initializePhase(int selected_moves[]) {
    resetMovementAvailability();  // Réinitialise la table des disponibilités
    for (int i = 0; i < 9; i++) {
        int move = drawRandomMovement();
        if (i < PHASE_MOVES) {
            selected_moves[i] = move;  // Conserver les 5 premiers choix optimaux
        }
    }
}
int hasReachedBase(t_map map, t_position pos){
    t_position base = getBaseStationPosition(map);
    if(pos.x == base.x && pos.y == base.y)
        return 1;
    return 0;
}

p_node buildTree(p_node root, t_map map, int depth) {
    // Si la profondeur maximale est atteinte ou si MARC est arrivé à la base
    if (depth == 0 || hasReachedBase(map, root->loc.pos)) {
        return root;
    }

    // Initialise les mouvements pour la phase
    int selected_moves[PHASE_MOVES];
    initializePhase(selected_moves);  // Tirer et sélectionner les meilleurs mouvements

    // Boucle sur chaque mouvement de la phase
    for (int i = 0; i < PHASE_MOVES; i++) {
        int movement = selected_moves[i];

        // Effectue le mouvement
        t_localisation new_loc = move(root->loc, movement);

        // Vérifie si la localisation est valide sur la carte
        if (!isValidLocalisation(new_loc.pos, map.x_max, map.y_max)) {
            continue;
        }

        // Obtient le type de sol pour la nouvelle localisation
        t_soil soil_type = map.soils[new_loc.pos.y][new_loc.pos.x];

        // Évite les zones de crevasse où MARC serait détruit
        if (soil_type == CREVASSE) {
            continue;  // On ignore les mouvements qui mènent à une crevasse
        }

        // Applique les restrictions pour le sol Erg
        if (soil_type == ERG) {
            // Diminue le prochain mouvement d'unité
            if (movement == F_10 || movement == B_10) {
                continue;  // Avancer de 10m ou Reculer de 10m ne sont pas valides sur un Erg
            } else if (movement == F_20) {
                movement = F_10;  // Avancer de 20m se réduit à 10m
            } else if (movement == F_30) {
                movement = F_20;  // Avancer de 30m se réduit à 20m
            }
            // Empêche les rotations de quart de tour
            if (movement == T_LEFT || movement == T_RIGHT) {
                continue;  // Tourner d’un quart de tour est interdit
            }
            if (movement == U_TURN) {
                movement = T_LEFT;  // On choisit de tourner à gauche à chaque fois dans ce cas
            }

        }

        // Applique les restrictions pour le sol Reg
        if (soil_type == REG && root->parent && root->parent->soil_type != REG) {
            root->nbSons = 4;  // Limite à 4 mouvements si le dernier mouvement a terminé sur un Reg
        }

       /* // Applique les restrictions pour le sol Pente
        if (soil_type == PENTE) {
            // Déplace MARC d'une case dans la direction descendante
            // Exemple simplifié : on suppose ici que la direction descendante est vers le bas
            new_loc.pos.y += 1;
            // Vérifie si la localisation après la pente est valide
            if (!isValidLocalisation(new_loc.pos, map->x_max, map->y_max)) {
                continue;
            }
        } */

        // Crée et ajoute le nœud fils avec les informations de la nouvelle localisation
        p_node son = addSon(root, movement,PHASE_MOVES, map);
        if(son != NULL){
            son->loc = new_loc;
            son->soil_type = soil_type;

            // Construction récursive de l'arbre à partir du nouveau nœud
            buildTree(son, map, depth - 1);
        }

    }

    return root;
}
