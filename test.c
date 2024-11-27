//
// Created by PC Ismael Sangare on 23/11/2024.
//
#include "test.h"
#include "loc.h"
#include "moves.h"
#include "stdio.h"
#include "stdlib.h"
#include "map.h"



// Test : Vérification de la sortie de la carte
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



void test_localisation(){

    t_localisation Rover_loc = loc_init(4,6,NORTH);
    t_localisation Rover_init_loc = loc_init(6,6,NORTH);
    t_position Right_rover = RIGHT(Rover_loc.pos);
    t_position Left_rover = LEFT(Rover_loc.pos);
    t_position Up_rover = UP(Rover_loc.pos);
    t_position Down_rover = DOWN(Rover_loc.pos);



    printf("La localisation initiale de Rover est (%d,%d) oriente vers %d\n",Rover_init_loc.pos.x,Rover_init_loc.pos.y,Rover_init_loc.ori);
    printf("La localisation actuelle de Rover est (%d,%d) oriente vers %d\n",Rover_loc.pos.x,Rover_loc.pos.y,Rover_loc.ori);
    printf("La position de la case a droite de Rover est (%d,%d)\n",Right_rover.x,Right_rover.y);
    printf("La position de la case a gauche de Rover est (%d,%d)\n",Left_rover.x,Left_rover.y);
    printf("La position de la case au dessus de Rover est (%d,%d)\n",Up_rover.x,Up_rover.y);
    printf("La position de la case en dessous de Rover est (%d,%d)\n",Down_rover.x,Down_rover.y);
    printf("\n");
}



void test_move() {

    t_localisation Rover_loc = loc_init(4,6,NORTH);

    t_localisation move_1 = move(Rover_loc,F_10);
    t_localisation move_2 = move(Rover_loc,T_LEFT);
    t_localisation move_3 = move(Rover_loc,F_20);
    t_localisation move_4 = move(Rover_loc,T_RIGHT);
    t_localisation move_5 = move(Rover_loc,F_30);
    t_localisation move_6 = move(Rover_loc,B_10);
    t_localisation move_7 = move(Rover_loc,U_TURN);


    printf("La localisation de Rover apres avoir avance de 10m devrait etre (%d,%d) oriente vers %d\n",move_1.pos.x,move_1.pos.y,move_1.ori);
    printf("La localisation de Rover apres avoir tourner a gauche devrait etre (%d,%d) oriente vers %d\n",move_2.pos.x,move_2.pos.y,move_2.ori);
    printf("La localisation de Rover apres avoir avance de 20m devrait etre (%d,%d) oriente vers %d\n",move_3.pos.x,move_3.pos.y,move_3.ori);
    printf("La localisation de Rover apres avoir tourner a droite devrait etre (%d,%d) oriente vers %d\n",move_4.pos.x,move_4.pos.y,move_4.ori);
    printf("La localisation de Rover apres avoir avance de 30m devrait etre (%d,%d) oriente vers %d\n",move_5.pos.x,move_5.pos.y,move_5.ori);
    printf("La localisation de Rover apres avoir reculer de 10m devrait etre (%d,%d) oriente vers %d\n",move_6.pos.x,move_6.pos.y,move_6.ori);
    printf("La localisation de Rover apres fait demi-tour devrait etre (%d,%d) oriente vers %d\n",move_7.pos.x,move_7.pos.y,move_7.ori);
    printf("\n");
}
void test_getRandomMoves(){
    t_move *moves1 = (t_move *)malloc(9 * sizeof(t_move));
    t_move *moves2 = (t_move *)malloc(5 * sizeof(t_move));
    moves1 = getRandomMoves(9);
    moves2 = getRandomMoves(5);
    printf("[ ");
    for (int i=0; i <9;i++){
        printf("[ ");
        printf("%s ", getMoveAsString(moves1[i]));

    }
    printf("]\n");

    printf("[ ");
    for (int i=0; i <5;i++){
        printf("%s ", getMoveAsString(moves2[i]));
    }
    printf("]\n");
}

