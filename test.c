//
// Created by PC Ismael Sangare on 23/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "test.h"
#include "loc.h"
#include "moves.h"





void testOutOfBounds() {
    printf("=== Test : Vérification de la sortie de la carte ===\n");

    // Charger une carte de test
    t_map map = createMapFromFile("/mnt/data/maps/example1.map");

    // Initialisation de la position de départ
    t_localisation start;
    start.pos.x = 0;  // Coin supérieur gauche
    start.pos.y = 0;
    start.ori = 0;    // Orientation initiale (par exemple, Nord)

    // Simuler un mouvement hors des limites
    t_move move = B_10;  // Reculer de 10m, définition dans vos fichiers
    updateLocalisation(&start, move);

    // Vérifier si la position est valide
    if (start.pos.x < 0 || start.pos.y < 0 || start.pos.x >= map.x_max || start.pos.y >= map.y_max) {
        printf("Erreur : MARC est sorti des limites de la carte !\n");
    } else {
        printf("Position après le mouvement : (%d, %d)\n", start.pos.x, start.pos.y);
    }
}



void test_map_functions(){
  t_map map;
	// The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\other.map");
#else
    map = createMapFromFile("../maps/other.map");
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
}

void test_loc_functions() {
    // Testing loc_init
    t_localisation loc = loc_init(5, 5, NORTH);
    printf("loc_init: x=%d, y=%d, ori=%d\n", loc.pos.x, loc.pos.y, loc.ori);

    // Testing isValidLocalisation
    t_position pos = {5, 5};
    int isValid = isValidLocalisation(pos, 10, 10);
    printf("isValidLocalisation: %d\n", isValid);

    // Testing LEFT
    t_position new_pos = LEFT(pos);
    printf("LEFT: x=%d, y=%d\n", new_pos.x, new_pos.y);

    // Testing RIGHT
    new_pos = RIGHT(pos);
    printf("RIGHT: x=%d, y=%d\n", new_pos.x, new_pos.y);

    // Testing UP
    new_pos = UP(pos);
    printf("UP: x=%d, y=%d\n", new_pos.x, new_pos.y);

    // Testing DOWN
    new_pos = DOWN(pos);
    printf("DOWN: x=%d, y=%d\n", new_pos.x, new_pos.y);
}



// Function to test rotate function
void test_rotate() {
    printf("Testing rotate function:\n");

    t_orientation ori = NORTH;
    t_move move = T_LEFT;
    t_orientation new_ori = rotate(ori, move);
    printf("Rotate from NORTH with T_LEFT: %d\n", new_ori);

    move = T_RIGHT;
    new_ori = rotate(ori, move);
    printf("Rotate from NORTH with T_RIGHT: %d\n", new_ori);

    move = U_TURN;
    new_ori = rotate(ori, move);
    printf("Rotate from NORTH with U_TURN: %d\n", new_ori);

    printf("\n");
}

// Function to test translate function
void test_translate() {
    printf("Testing translate function:\n");

    t_localisation loc = loc_init(0, 0, NORTH);
    t_move move = F_10;
    t_localisation new_loc = translate(loc, move);
    printf("Translate from (0,0) facing NORTH with F_10: (%d,%d)\n", new_loc.pos.x, new_loc.pos.y);

    move = F_20;
    new_loc = translate(loc, move);
    printf("Translate from (0,0) facing NORTH with F_20: (%d,%d)\n", new_loc.pos.x, new_loc.pos.y);

    move = F_30;
    new_loc = translate(loc, move);
    printf("Translate from (0,0) facing NORTH with F_30: (%d,%d)\n", new_loc.pos.x, new_loc.pos.y);

    move = B_10;
    new_loc = translate(loc, move);
    printf("Translate from (0,0) facing NORTH with B_10: (%d,%d)\n", new_loc.pos.x, new_loc.pos.y);

    printf("\n");
}


// Function to test move function
void test_move() {
    printf("Testing move function:\n");

    t_localisation loc = loc_init(0, 0, NORTH);
    t_move move_cmd = F_10;
    t_localisation new_loc = move(loc, move_cmd);
    printf("Move from (0,0) facing NORTH with F_10: (%d,%d)\n", new_loc.pos.x, new_loc.pos.y);

    move_cmd = T_RIGHT;
    new_loc = move(loc, move_cmd);
    printf("Move from (0,0) facing NORTH with T_RIGHT: (%d,%d)\n", new_loc.ori, new_loc.pos.y);

    printf("\n");
}

// Function to test updateLocalisation function
void test_updateLocalisation() {
    printf("Testing updateLocalisation function:\n");

    t_localisation loc = loc_init(0, 0, NORTH);
    t_move move_cmd = F_10;
    updateLocalisation(&loc, move_cmd);
    printf("Update localisation from (0,0) facing NORTH with F_10: (%d,%d)\n", loc.pos.x, loc.pos.y);

    printf("\n");
}

// Function to test getRandomMoves function
void test_getRandomMoves() {
    printf("Testing getRandomMoves function:\n");

    int N = 10;
    t_move *moves = getRandomMoves(N);

    if (moves != NULL) {
        printf("Random moves: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", moves[i]);
        }
        printf("\n");
        free(moves);
    }


    printf("\n");
}

void test_moves_functions() {
    test_rotate();
    test_translate();
    test_move();
    test_updateLocalisation();
    test_getRandomMoves();
}

