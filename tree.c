//
// Created by fortu on 11/11/2024.
//
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "tree.h"
#include <sys/time.h>

p_node createNode(t_localisation loc, int nbSons, const t_move *available_moves, int nbMoves, int depth, p_node parent, t_move move_to_do, t_map map) {
    if (nbSons < 0 || nbMoves < 0) {
        printf("Invalid number of sons or moves\n");
        return NULL;
    }

    p_node node = malloc(sizeof(t_node));
    if (node == NULL) {
        printf("Failed to allocate memory for node\n");
        return NULL;
    }

    if (!isValidLocalisation(loc.pos, map.x_max, map.y_max)) {
        printf("Invalid position\n");
        free(node);
        return NULL;
    }

    node->loc = loc;
    node->soil_type = map.soils[loc.pos.y][loc.pos.x];
    node->cost = map.costs[loc.pos.y][loc.pos.x];
    node->depth = depth;
    node->nbSons = nbSons;
    node->parent = parent;
    node->move_from_parent = move_to_do;
    node->nbMoves = nbMoves;

    if (nbMoves > 0) {
        node->moves_available = (t_move *)malloc(nbMoves * sizeof(t_move));
        if (node->moves_available == NULL) {
            free(node);
            printf("Failed to allocate memory for moves\n");
            return NULL;
        }
        for (int i = 0; i < nbMoves; i++) {
            node->moves_available[i] = available_moves[i];
        }
    } else {
        node->moves_available = NULL;
    }

    if (nbSons > 0) {
        node->sons = (p_node *)malloc(nbSons * sizeof(p_node));
        if (node->sons == NULL) {
            free(node->moves_available);
            free(node);
            printf("Failed to allocate memory for sons\n");
            return NULL;
        }
        for (int i = 0; i < nbSons; i++) {
            node->sons[i] = NULL;
        }
    } else {
        node->sons = NULL;
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
    if (parent->nbSons <= 0)
        return;

    for (int i = 0; i < parent->nbSons; i++) {
        int nbAvailsMove = 0;
        if (parent->nbMoves <= 1)
            continue;

        t_move *availsMove = malloc((parent->nbMoves - 1) * sizeof(t_move));
        if (availsMove == NULL)
            return;

        for (int j = 0; j < parent->nbMoves; j++) {
            if (j == i) continue;

            int movement = parent->moves_available[j];

            if (parent->soil_type == CREVASSE)
                continue;

            if (parent->soil_type == ERG) {
                switch (movement) {
                    case F_10:
                    case B_10:
                    case T_LEFT:
                    case T_RIGHT:
                        continue; // Skip forbidden movements
                    case F_20:
                        movement = F_10;
                        break;
                    case F_30:
                        movement = F_20;
                        break;
                    case U_TURN:
                        movement = T_LEFT;
                        break;
                    default:
                        break;
                }
            }
            availsMove[nbAvailsMove++] = movement;
        }

        t_localisation son_loc = move(parent->loc, parent->moves_available[i]);
        if (!isValidLocalisation(son_loc.pos, map.x_max, map.y_max)) {
            free(availsMove);
            continue;
        }

        p_node son = createNode(son_loc,
                                nbAvailsMove,
                                availsMove,
                                parent->nbSons - 1,
                                parent->depth + 1,
                                parent,
                                parent->moves_available[i],
                                map);

        if (son == NULL) {
            free(availsMove);
            continue;
        }

        parent->sons[i] = son;
        createTreeRecursivity(son, map, k);
    }
}
void findMinCostLeafInNode(p_node node, p_node *leaf) {
    if (node == NULL)
        return;
    if ((node->nbSons == 0 || node->nbSons == 4 ) && node->cost < 10000) {  // Consider defining 10000 as a constant
        if (*leaf == NULL || node->cost < (*leaf)->cost) {
            *leaf = node;
        }
    }
    for (int i = 0; i < node->nbSons; i++) {
        if (node->sons[i] != NULL) {  // Additional null check for node->sons[i]
            findMinCostLeafInNode(node->sons[i], leaf);
        }
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
    printf("Position (%d, %d), Orientation %d, Cost: %d,  NbSons : %d\n",  root->loc.pos.x, root->loc.pos.y, root->loc.ori, root->cost, root->nbSons);


    for (int i = 0; i < root->nbSons; i++) {
        printTree(root->sons[i], level + 1);
    }
}


void freeTree(p_node node) {
    if (node == NULL) {
        return;
    }

    if (node->sons != NULL) {
        for (int i = 0; i < node->nbSons; i++) {
            if (node->sons[i] != NULL) {
                freeTree(node->sons[i]);
            }
        }
        free(node->sons);
    }

    if (node->moves_available != NULL) {
        free(node->moves_available);
    }

    free(node);
}


void printPathToRoot(p_node leaf) {
    // Check if leaf is null
    if (leaf == NULL) return;

    // Print "START" since this is the beginning of the path
    if (leaf->parent == NULL) {
        printf("START");
    } else {
        // Recursively call the function until the root node is reached
        printPathToRoot(leaf->parent);

        // Ensure getMoveAsString returns a valid string
        char* moveStr = getMoveAsString(leaf->move_from_parent);
        if (moveStr != NULL) {
             printf(" -> %s", moveStr);
        } else {
            printf(" -> UNKNOWN_MOVE");
        }
    }
}


int hasReachedBase(t_map map, t_position pos){
    t_position base = getBaseStationPosition(map);
    if(pos.x == base.x && pos.y == base.y)
        return 1;
    return 0;
}
/***********************************************************************************************************************/
// Stacks functions definition

t_stack_node createStackNode(int size) {
    // Ensure the size of the stack is positive
    assert(size > 0);

    t_stack_node s;
    s.size = size;
    s.nbElts = 0;
    s.values = (p_node *)malloc(size * sizeof(p_node));

    // Check if malloc succeeded
    if (s.values == NULL)
    {
        // Handle memory allocation failure
        assert(!"Failed to allocate memory for stack node values");
    }

    return s;
}

void pushNode(t_stack_node *p_stack, p_node value)
{
    // Check for null pointers
    if (p_stack == NULL || p_stack->values == NULL) {
        // Log an error message or handle error
        fprintf(stderr, "pushNode() error: p_stack or p_stack->values is null\n");
    }

    // the stack must not be full
    assert(p_stack->nbElts < p_stack->size);

    // Ensure the stack length does not exceed its size
    if (p_stack->nbElts < p_stack->size) {
        p_stack->values[p_stack->nbElts] = value;
        p_stack->nbElts++;
    } else {
        // Handle error for full stack
        fprintf(stderr, "pushNode() error: stack is full\n");
    }
}


p_node popNode(t_stack_node *p_stack) {
    // the stack must not be empty
    assert(p_stack->nbElts > 0);
    p_node value = p_stack->values[p_stack->nbElts - 1];
    p_stack->nbElts--;
    return value;
}


p_node topNode(t_stack_node stack) {
    // the stack must not be empty
    assert(stack.nbElts > 0);
    return stack.values[stack.nbElts - 1];
}

int isStackEmptyNode(t_stack_node s) {
    return s.nbElts == 0;
}
 /**********************************************************************************************************************/

void executePath(t_stack_node *s, t_localisation *start_loc) {
    while (!isStackEmptyNode(*s)) {
        p_node current = popNode(s);
        if (current != NULL) {  // Additional check, even if redundant given assert in popNode
            updateLocalisation(start_loc, current->move_from_parent);
        } else {
            // Handle unexpected NULL (though popNode ensures it shouldn't happen)
            fprintf(stderr, "Unexpected NULL node encountered\n");
        }
    }
}

void getPath(p_node min_leaf, t_stack_node* stack) {
    if (min_leaf == NULL || stack == NULL || stack->values == NULL) {
        fprintf(stderr, "getPath() error: min_leaf or stack or stack->values is null\n");
        return;
    }

    p_node current = min_leaf;
    while (current != NULL) {
        if (stack->nbElts >= stack->size) {
            fprintf(stderr, "getPath() error: stack overflow\n");
            return; // Handle overflow by exiting the function
        }
        pushNode(stack, current);
        current = current->parent;
    }
}

int lauchPhase(t_map map, t_localisation *start_loc, t_stack_node *s) {
    t_move *moves = getRandomMoves(9);
    if (!moves) {
        printf("Failed to allocate memory for moves.\n");
        return 0;
    }

    p_node tree = createNode(*start_loc, 9, moves, 9, 0, NULL, START, map);
    free(moves);  // Freeing moves after it's no longer needed

    if (tree == NULL) {
        printf("Failed to create tree node.\n");
        return 0;
    }

    int nbMovementsInPhase = 5;
    if (tree->soil_type == REG) {
        nbMovementsInPhase = 4;
    }

    struct timeval start, end;

    // Temps de début
    gettimeofday(&start, NULL);

    createTreeRecursivity(tree, map, nbMovementsInPhase);

    gettimeofday(&end, NULL);

    // Calculer le temps écoulé
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    printf("\nTemps écoulé récurssivité: %.6f secondes\n", elapsed);

    //printTree(tree, 0);

    p_node minLeaf = NULL;
    struct timeval start1, end1;
    // Temps de début
    gettimeofday(&start1, NULL);
    findMinCostLeaf(tree, &minLeaf);
    gettimeofday(&end1, NULL);
    // Calculer le temps écoulé
    seconds = end1.tv_sec - start1.tv_sec;
    microseconds = end1.tv_usec - start1.tv_usec;
     elapsed = seconds + microseconds * 1e-6;
    printf("\nTemps écoulé coûts minimal: %.6f secondes\n", elapsed);


    if(minLeaf != NULL) {
        printf("\nMinimum cost leaf : %d\n", minLeaf->cost);
        printPathToRoot(minLeaf);
        getPath(minLeaf, s);
        executePath(s, start_loc);
    }else {
        printf("Failed to find minimum cost leaf\n");
        return 0;
    }

    freeTree(tree);
    return 1;
}

void drivingToBase(t_map map, t_localisation *start_loc, t_stack_node *s) {

    int nbPhases = 0;
    if (!isValidLocalisation(start_loc->pos, map.x_max, map.y_max) || map.soils[start_loc->pos.y][start_loc->pos.x] == CREVASSE) {
        printf(" Invalid position \n");
        return;
        }

    while (!hasReachedBase(map, start_loc->pos) && nbPhases < 10) {
        int phaseResult = lauchPhase(map, start_loc, s);

        if (!phaseResult) {
            printf("Failed to complete phase\n");
        break;
         }
        nbPhases++;
    }
    printf("\nNumber of phases : %d\n", nbPhases);

}
