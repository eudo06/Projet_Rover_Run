//
// Created by fortu on 11/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#define NUM_MOVEMENTS 7
#define PHASE_MOVES  5


p_node createNode(t_localisation loc, t_soil soil_type, int cost, int nbSons, const t_move *available_moves, int nbMoves, int depth, p_node parent, t_move move_to_do) {
    p_node node = (p_node) malloc(sizeof(t_node));
    if (node == NULL)
        return NULL;

    node->loc = loc;
    node->soil_type = soil_type;
    node->cost = cost;
    node->depth = depth;
    node->nbSons = nbSons;
    node->parent = parent;
    node->move_from_parent = move_to_do;
    node->nbMoves = nbMoves;
    node->moves_available = (t_move *)malloc(nbMoves *sizeof(t_move));

    if (node->moves_available == NULL) {
        free(node);
        printf("Moves configuration failed\n");
        return NULL;
    }

    for (int i = 0; i < nbMoves; i++) {
        node->moves_available[i] = available_moves[i];
    }
    node->sons = (p_node *) malloc(nbSons * sizeof(p_node));

    if (node->sons == NULL) {
        free(node);
        printf("Sons configuration failed\n");
        return NULL;
    }

    for (int i = 0; i < nbSons; i++){
        node->sons[i] = NULL;
    }

    return node;
}


void createTreeRecursivity(p_node parent, t_map map, int k) {
    if (parent == NULL || parent->depth >= k || !isValidLocalisation(parent->loc.pos, map.x_max, map.y_max))
        return;

    if (map.costs[parent->loc.pos.y][parent->loc.pos.x] > 10000) {
        parent->nbSons = 0;
        parent->nbMoves = 0;
        return;
    }

    for (int i = 0; i < parent->nbSons; i++) {
        int nbAvailsMove = 0;
        t_move *availsMove = malloc((parent->nbMoves - 1) * sizeof(t_move));
        if (availsMove == NULL)
            return;

        for (int j = 0; j < parent->nbMoves; j++) {
            if (j != i) {
                availsMove[nbAvailsMove++] = parent->moves_available[j];
            }
        }

        t_localisation son_loc = move(parent->loc, parent->moves_available[i]);
        if (!isValidLocalisation(son_loc.pos, map.x_max, map.y_max)) {
            free(availsMove);
            continue;
        }

        p_node son = createNode(son_loc,
                                map.soils[son_loc.pos.y][son_loc.pos.x],
                                map.costs[son_loc.pos.y][son_loc.pos.x],
                                nbAvailsMove,
                                availsMove,
                                parent->nbSons - 1,
                                parent->depth + 1,
                                parent,
                                parent->moves_available[i]);
        if (son == NULL) {
            free(availsMove);
            continue;
        }

        parent->sons[i] = son;
        createTreeRecursivity(son, map, k);

        free(availsMove);
    }
}

void findMinCostLeafInNode(p_node node, p_node *leaf) {
    if (node == NULL)
        return;

    if (*leaf == NULL || node->cost < (*leaf)->cost)
        *leaf = node;

    for (int i = 0; i < node->nbSons; i++) {
        findMinCostLeafInNode(node->sons[i], leaf);
    }
}

void findMinCostLeaf(p_node root, p_node *leaf) {
    if (root == NULL)
        return;

    findMinCostLeafInNode(root, leaf);
}


void printTree(p_node root, int level) {
    if (root == NULL)
        return;

    for (int i = 0; i <= level; i++) printf("  ");
    printf("Position (%d, %d), Orientation %d, Cost: %d\n", root->loc.pos.x, root->loc.pos.y, root->loc.ori, root->cost);


    for (int i = 0; i < root->nbSons; i++) {
        printTree(root->sons[i], level + 1);
    }
}


void freeTree(p_node node) {
    if (node == NULL) return;

    for (int i = 0; i < node->nbSons; i++) {
        freeTree(node->sons[i]);
    }
    free(node->sons);
    free(node->moves_available);
    free(node);
}





void printPathToRoot(p_node leaf) {
    if (leaf == NULL) return;

    if (leaf->parent != NULL) {
        printPathToRoot(leaf->parent);

        printf(" -> %s", getMoveAsString(leaf->move_from_parent));
    } else {

        printf("START");
    }
}

int hasReachedBase(t_map map, t_position pos){
    t_position base = getBaseStationPosition(map);
    if(pos.x == base.x && pos.y == base.y)
        return 1;
    return 0;
}
