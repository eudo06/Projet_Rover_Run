#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


typedef struct Node {
    int cost;                 // Coût associé au mouvement/position
    int movement;             // Identifiant du mouvement (ex : 0 = "Avancer de 10m")
    struct Node** children;   // Tableau de pointeurs vers les enfants
    int num_children;         // Nombre d'enfants
    struct Node* parent;      // Pointeur vers le parent
} Node;

Node* create_node(int cost, int movement, int max_children, Node* parent);

void add_child(Node* parent, Node* child);

void construct_tree(Node* root, int level, int max_levels, int* movements, int num_movements);

void find_min_cost_leaf(Node* root, int* min_cost, Node** min_leaf);

void print_path(Node* root, Node* leaf);

void free_tree(Node* root);