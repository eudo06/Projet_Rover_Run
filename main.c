#include <stdio.h>
#include "map.h"
#include "loc.h"

#include "tree.h"
#include <sys/time.h>



void test_all_functions();
void testEnSpeed(t_map map);

int main() {


    test_all_functions();


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


    testEnSpeed(map);


}


void testEnSpeed(t_map map){

    t_localisation start_loc = {{2 ,4},SOUTH };
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
