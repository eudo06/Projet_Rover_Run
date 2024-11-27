#include <stdio.h>
#include "map.h"
#include "loc.h"
#include "test.h"
#include "tree.h"
#include <sys/time.h>

void menu();
void driving_function_test();


int main() {

    menu();
    return 0;
}


void driving_function_test(t_localisation start_loc) {
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

    t_stack_node s = createStackNode(100);
    struct timeval start, end;

    // start
    gettimeofday(&start, NULL);
    drivingToBase(map, &start_loc, &s);

   //end
    gettimeofday(&end, NULL);

    //elapsed
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    printf("Time needed to drive Marc too the base : %.6f secondes\n", elapsed);
}

void menu() {
    int choice;

    do {

        printf("\n=== MENU  ===\n");
        printf("1. Driving Marc to the base\n");
        printf("2. Testing of map functions  (map)\n");
        printf("3. Testing of localisation functions (loc)\n");
        printf("4. Testing of movements functions (moves)\n");
        printf("0. Quit\n");
        printf("Your choice : ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                printf("\n[INFO] Driving Marc to the base...\n");
                printf("Enter the starting position (x,y) : ");
                int x, y;
                scanf("%d %d", &x, &y);
                printf("Enter the starting orientation (NORTH, EAST, SOUTH, WEST) :");
                t_orientation ori;
                scanf("%s", &ori);
                t_localisation start_loc = {x, y, ori};
                driving_function_test(start_loc);
            break;
            case 2:
                printf("\n[INFO] Testing of map functions  (map)...\n");
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