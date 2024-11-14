//
// Created by fortu on 11/11/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H
#include "loc.h"
#include "map.h"
#include "moves.h"

typedef struct s_node {
    t_localisation loc;             // Localisation du rover à ce nœud
    t_soil soil_type;               // Type de sol pour ce nœud
    int cost;                       // Coût cumulé pour atteindre ce nœud
    t_move move_from_parent;        // Mouvement menant ici depuis le parent
    struct s_node **sons;           // Enfants représentant les prochains mouvements possibles
    int nbSons;
    struct s_node *parent;          // Nœud parent
} t_node, *p_node;
p_node createNode(t_localisation loc, t_soil soil_type, int cost,int nbSons, p_node parent);
p_node addSon(p_node parent,t_move mov,int nbSons, t_map map);
p_node findMinCostLeaf(p_node root);
void printPathToRoot(p_node leaf);
void printTree(p_node root, int level);
void freeTree(p_node root);
p_node buildTree(p_node root, t_map map, int depth);
#endif //UNTITLED1_TREE_H
