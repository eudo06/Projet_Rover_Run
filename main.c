#include <stdio.h>
#include "map.h"
#include "loc.h"
#include "test.h"
#include "tree.h"
#include <sys/time.h>

// Prototypes des fonctions
void test_all_functions();
void test_map_functions();
void test_loc_functions();
void test_moves_functions();

int main() {
    int choice;

    do {
        // Affichage du menu
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Tester toutes les fonctionnalités\n");
        printf("2. Tester les fonctionnalités de la carte (map)\n");
        printf("3. Tester les fonctionnalités de localisation (loc)\n");
        printf("4. Tester les fonctionnalités des mouvements (moves)\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choice);

        // Gestion des choix
        switch (choice) {
            case 1:
                printf("\n[INFO] Test de toutes les fonctionnalités...\n");
                test_all_functions();
                break;
            case 2:
                printf("\n[INFO] Test des fonctionnalités de la carte...\n");
                test_map_functions();
                break;
            case 3:
                printf("\n[INFO] Test des fonctionnalités de localisation...\n");
                test_loc_functions();
                break;
            case 4:
                printf("\n[INFO] Test des fonctionnalités des mouvements...\n");
                test_moves_functions();
                break;
            case 0:
                printf("\n[INFO] Fin du programme.\n");
                break;
            default:
                printf("\n[ERREUR] Choix invalide. Veuillez réessayer.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

// Fonction de test pour vérifier toutes les fonctionnalités
void test_all_functions() {
    t_map map;

    // Vérification de la plateforme pour les chemins de fichiers
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\other.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // Affichage des coûts
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    t_localisation start_loc = {{4, 4}, SOUTH};
    t_stack_node s = createStackNode(100);
    struct timeval start, end;

    // Début du chronométrage
    gettimeofday(&start, NULL);
    drivingToBase(map, &start_loc, &s);

    // Fin du chronométrage
    gettimeofday(&end, NULL);

    // Calcul du temps écoulé
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    printf("Temps nécessaire pour conduire Marc à la base : %.6f secondes\n", elapsed);
}