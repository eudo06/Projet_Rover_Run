#include <stdio.h>

#include "map.h"
#include "loc.h"
#include "moves.h"
#include "tree.h"
#define PHASE_MOVES 3

void test_all_functions();
void createTestTree(p_node root, int level, int max_level);
void testTree(t_map map);

int main() {

    test_all_functions();


    return 0;
}



// Fonction de test pour vérifier toutes les fonctionnalités
void test_all_functions() {
    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    //displayMap(map);


    // Vérification de la station de base
   /* t_position base_pos = getBaseStationPosition(map);
    printf("Base Station Position: (%d, %d)\n", base_pos.x, base_pos.y);

    // Test de la localisation initiale
    t_localisation init = loc_init(4, 6, NORTH);
    printf("Initial localisation: Position (%d, %d), Orientation %d\n", init.pos.x, init.pos.y, init.ori);

    // Test de validation de localisation
    t_position pos = {4, 6};
    printf("Is position (%d, %d) valid? %d\n", pos.x, pos.y, isValidLocalisation(pos, map.x_max, map.y_max));

    // Tests de mouvements individuels
    printf("\n--- Testing Moves ---\n");
    t_localisation loc = init;

    t_move moves[] = {F_10, T_RIGHT, F_20, T_LEFT, B_10, U_TURN};
    for (int i = 0; i < 6; i++) {
        loc = move(loc, moves[i]);
        printf("Move %s: New Position (%d, %d), Orientation %d\n", getMoveAsString(moves[i]), loc.pos.x, loc.pos.y, loc.ori);
    }
printf("\n__________________________________________\n");

*/
   //testTree(map);

  t_localisation start_loc = { {2, 4}, NORTH };
    p_node root = createNode(start_loc, map.soils[start_loc.pos.y][start_loc.pos.x], map.costs[start_loc.pos.y][start_loc.pos.x], PHASE_MOVES,NULL);
    p_node tree = buildTree(root, map, 5);
    printTree(tree,0);

    //p_node minLeaf = findMinCostLeaf(root);

    /*printf("\nFeuille de cout minimal : %d\n", minLeaf->cost);
    printPathToRoot(minLeaf);  // Affiche le chemin de mouvements jusqu'à la feuille de coût minimal
    printf("\n"); */

    // Libération de la mémoire */
   //freeTree(tree);
}










void testTree(t_map map) {
    // Initialisation de la racine de l'arbre avec position (0, 0), coût 0, et sans mouvement initial
    t_localisation start_loc = { {5, 4}, NORTH };
    p_node root = createNode(start_loc, map.soils[start_loc.pos.y][start_loc.pos.x], map.costs[start_loc.pos.y][start_loc.pos.x], PHASE_MOVES,NULL);


    // Ajout de nœuds enfants avec différents mouvements et coûts
    addSon(root, F_10,PHASE_MOVES, map);
    addSon(root,   T_RIGHT, PHASE_MOVES,map);
    addSon(root,   T_LEFT, PHASE_MOVES,map);

    // Ajout de fils pour le premier fils de la racine
    addSon(root->sons[0],F_30,PHASE_MOVES,map);
    addSon(root->sons[0],T_RIGHT, PHASE_MOVES,map);
    addSon(root->sons[0],T_LEFT, PHASE_MOVES,map);

    // Ajout de fils pour le deuxième fils de la racine
    addSon(root->sons[1],F_10, PHASE_MOVES,map);
    addSon(root->sons[1],T_RIGHT, PHASE_MOVES,map);
    addSon(root->sons[1], T_LEFT, PHASE_MOVES,map);

    // Ajout de fils pour le troisième fils de la racine
    addSon(root->sons[2], F_20,PHASE_MOVES, map);
    addSon(root->sons[2],T_RIGHT,PHASE_MOVES, map);
    addSon(root->sons[2],U_TURN,PHASE_MOVES, map);

    /******************************************************/



    /******************************************************/
    // Affichage de l'arbre complet pour vérification
    printf("Test de l'arbre :\n");
    printTree(root, 0);

    // Recherche de la feuille de coût minimal
    p_node minLeaf = findMinCostLeaf(root);
    printf("\nFeuille de cout minimal : %d\n", minLeaf->cost);
    printPathToRoot(minLeaf);  // Affiche le chemin de mouvements jusqu'à la feuille de coût minimal
    printf("\n");

    // Libération de la mémoire
    freeTree(root);
}
