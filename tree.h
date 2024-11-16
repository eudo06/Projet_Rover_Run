//
// Created by fortu on 11/11/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H
#include "loc.h"
#include "map.h"
#include "moves.h"

typedef struct s_node {
    t_localisation loc;
    t_soil soil_type;
    int cost;
    int depth;
    t_move move_from_parent;
    struct s_node **sons;
    int nbSons;
    t_move *moves_available;
    int nbMoves;
    struct s_node *parent;
} t_node, *p_node;

p_node createNode(t_localisation loc, t_soil soil_type, int cost, int nbSons, const t_move *available_moves, int nbMoves, int depth, p_node parent, t_move move_to_do);
void createTreeRecursivity(p_node parent, t_map map, int k);
p_node addSon(p_node parent,t_move mov,int nbSons, t_map map);
void findMinCostLeaf(p_node root, p_node *leaf);
void printPathToRoot(p_node leaf);
void printTree(p_node root, int level);
void freeTree(p_node root);
p_node buildTree(p_node root, t_map map, int depth);

#endif //UNTITLED1_TREE_H
