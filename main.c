#include <stdio.h>
#include "map.h"
#include "loc.h"
#include "test.h"
#include "tree.h"
#include <sys/time.h>

void menu();
void driving_function_test(t_localisation start_loc, char *map_file);

int main() {
    menu();
    return 0;
}

void driving_function_test(t_localisation start_loc, char *map_file) {
    t_map map;

    // Charger la carte sélectionnée
    map = createMapFromFile(map_file);

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

    t_stack_node s = createStackNode(100);
    struct timeval start, end;

    // Start
    gettimeofday(&start, NULL);
    drivingToBase(map, &start_loc, &s);

    // End
    gettimeofday(&end, NULL);

    // Calcul du temps écoulé
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    printf("Time needed to drive Marc to the base: %.6f secondes\n", elapsed);
}

void menu() {
    int choice;
    char *map_file = NULL;

    // Sélection de la carte
    printf("\n=== Sélection de la carte ===\n");
    printf("1. Normal map (example1.map)\n");
    printf("2. Complex map (other.map)\n");
    printf("Your choice : ");
    int map_choice;
    scanf("%d", &map_choice);

    if (map_choice == 1) {
        map_file = "../maps/example1.map";
        printf("Selected map: example1.map\n");
    } else if (map_choice == 2) {
        map_file = "../maps/other.map";
        printf("Selected map: other.map\n");
    } else {
        printf("[ERROR] Invalid map choice. Exiting program.\n");
        return;
    }

    // Menu principal
    do {
        printf("\n=== MENU ===\n");
        printf("1. Driving Marc to the base\n");
        printf("2. Testing of map functions (map)\n");
        printf("3. Testing of localisation functions (loc)\n");
        printf("4. Testing of movements functions (moves)\n");
        printf("0. Quit\n");
        printf("Your choice : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("\n[INFO] Driving Marc to the base...\n");
                printf("Enter the starting position x y : ");
                int x, y;
                scanf("%d %d", &x, &y);
                printf("Enter the starting orientation (0=NORTH, 1=EAST, 2=SOUTH, 3=WEST) : ");
                int ori;
                scanf("%d", &ori);
                t_orientation orientation = (t_orientation)ori;
                t_localisation start_loc = {{x, y}, orientation};
                driving_function_test(start_loc, map_file);
                break;
            }
            case 2:
                printf("\n[INFO] Testing of map functions (map)...\n");
                test_map_functions();
                break;
            case 3:
                printf("\n[INFO] Testing of localisation functions (loc)...\n");
                test_loc_functions();
                break;
            case 4:
                printf("\n[INFO] Testing of movements functions (moves)...\n");
                test_moves_functions();
                break;
            case 0:
                printf("\n[INFO] End of program.\n");
                break;
            default:
                printf("\n[ERROR] Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 0);
}