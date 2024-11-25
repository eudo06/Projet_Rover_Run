#include <stdio.h>
#include "map.h"
#include "loc.h"

#include "tree.h"
#include <sys/time.h>



void test_all_functions();
void testEnSpeed(t_map map);

int main() {


    struct timeval start, end;

    // Temps de début
    gettimeofday(&start, NULL);

    // Opération à mesurer
    test_all_functions();

    // Temps de fin
    gettimeofday(&end, NULL);

    // Calculer le temps écoulé
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    printf("\nTemps écoulé test_all_functions: %.6f secondes\n", elapsed);




  /*  test_move();
    test_localisation();
    test_getRandomMoves();
*/
    return 0;
}




// Fonction de test pour vérifier toutes les fonctionnalités
void test_all_functions() {
    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps copie\\example24.map");
#else
    map = createMapFromFile("../maps copie/example24.map");
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
    displayMap(map);


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

    testEnSpeed(map);


}


void testEnSpeed(t_map map){

    t_localisation start_loc = {{1 ,5},NORTH };
    t_stack_node s = createStackNode(100);
    struct timeval start, end;

    // Temps de début
    gettimeofday(&start, NULL);
    drivingToBase(map, &start_loc, &s);
    // Temps de fin
    gettimeofday(&end, NULL);

    // Calculer le temps écoulé
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    printf("Temps nécessaire pour conduire le robot à la base: %.6f secondes\n", elapsed);
}
