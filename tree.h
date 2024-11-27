//
// Created by fortu on 11/11/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "loc.h"
#include "map.h"
#include "moves.h"

/**
 *
 */
typedef struct s_node {
 /**
  * @typedef t_localisation
  * @brief This type describes the localization of a node in a tree structure.
  *
  * It includes information about the position and orientation, which can be
  * used to determine the node's location within a map and how it is oriented.
  */
 t_localisation loc;
 /**
  * @var t_soil soil_type
  * @brief Type representing the soil classification for a node's location.
  *
  * This variable indicates the type of soil at a specific node's location.
  * The possible values are defined in the `e_soil` enumeration.
  * It is used to determine movement constraints and costs within the map.
  */
 t_soil soil_type;
 /**
  * Attribute representing the cost associated with a node.
  * This cost is used in various algorithms, including the
  * determination of the minimum cost leaf in the tree structure.
  */
 int cost;
 /**
  * The depth of the current tree node.
  *
  * This variable indicates the level of the node within the tree.
  * Root nodes have a depth of 0, and the depth increases by 1 for
  * each level down the tree.
  */
 int depth;
 /**
  * Field representing the move action taken to transition from the parent node to this node.
  * It is used to trace back the path from the current node to the root node in a search tree.
  * Possible values are defined in the t_move enum, which include moves such as Forward 10 meters, Turn left, U-turn, etc.
  */
 t_move move_from_parent;
 /**
  * A pointer to an array of pointers to child nodes of the current node.
  * Each element in the array points to one of the child nodes.
  */
 struct s_node **sons;
    /**
     * @brief Number of child nodes that a t_node can have.
     */
    int nbSons;
 /**
  * @brief Pointer to a dynamically allocated array of available moves from the current node.
  *
  * This array holds the possible moves that can be taken from the current node within the search tree.
  * Each move is of type `t_move`, which represents a specific action such as moving forward, turning left, etc.
  * The array can be populated during the creation of the node if there are any valid moves to be performed.
  * The number of available moves is indicated by the `nbMoves` member of the `t_node` structure.
  *
  * @note The array should be properly allocated and freed to avoid memory leaks.
  * @see t_move, t_node
  */
 t_move *moves_available;
 /**
  * @brief Represents the number of possible moves available from the current node.
  *
  * This variable holds the count of legitimate moves that can be made from the current node
  * to its potential children nodes. It is used in conjunction with the `moves_available`
  * array to manage and limit the actions that can be taken from this node in the tree structure.
  */
 int nbMoves;
 /**
  * Pointer to the parent node in a tree structure.
  * This member allows navigating from a child node back to its parent within the tree.
  */
 struct s_node *parent;
} t_node, *p_node;

/**
 * @struct s_stack_node
 * @brief Represents a stack node used to store tree nodes.
 *
 * This structure is used to manage a dynamic collection of tree nodes,
 * allowing for operations such as pushing and popping nodes from the stack.
 */
typedef struct s_stack_node
{
 /**
  * @var p_node *values
  * @brief Pointer to an array of node pointers in a stack structure.
  *
  * This member variable is used to store the nodes in a stack manner, where
  * each element in the array represents a node within the stack. It supports
  * stack operations such as push and pop for managing tree nodes.
  */
 p_node *values;
 /**
  * @var int size
  * @brief Represents the maximum number of elements that a stack node can hold.
  *
  * This variable determines the capacity of the stack, dictating how many elements
  * can be pushed onto it before it becomes full. It is essential to ensure that the
  * value of `size` is set to a positive integer during stack initialization to
  * prevent issues with memory allocation and stack operations.
  */
 int size;
 /**
  * @brief The current number of elements in the stack.
  *
  * This variable holds the count of elements currently present in the `t_stack_node`.
  * It is incremented each time a new element is added to the stack and decremented
  * when an element is removed. It is used to manage the stack's operational status,
  * ensuring the stack does not overflow and helping in checking whether the stack is empty.
  */
 int nbElts;
}t_stack_node;

/**
 * @brief Creates a new node in a tree structure.
 *
 * This function initializes a node with the specified parameters, including
 * its localization, the number of sons, the available moves, its depth, its
 * parent node, the move to be performed, and the map. It also allocates memory
 * for the node's sons and moves.
 *
 * @param loc The localization of the node.
 * @param nbSons The number of child nodes (sons) of the new node.
 * @param available_moves An array of possible moves available to the node.
 * @param nbMoves The number of available moves.
 * @param depth The depth of the node in the tree.
 * @param parent A pointer to the parent node of the new node.
 * @param move_to_do The move to be performed to reach this node from its parent.
 * @param map The map which includes information about positions, soil types, and costs.
 * @return A pointer to the newly created node, or NULL if memory allocation fails or parameters are invalid.
 */
p_node createNode(t_localisation loc, int nbSons, const t_move *available_moves, int nbMoves, int depth, p_node parent, t_move move_to_do,t_map map);

/**
 * @brief Recursively creates a tree structure with specified depth and constraints.
 *
 * The function `createTreeRecursivity` initializes and populates a tree structure
 * starting from a given parent node, `parent`. It recursively generates child nodes as
 * long as the specified constraints (depth, map boundaries, soil type, etc.) are met.
 *
 * @param parent The parent node from where the recursion starts. This node serves
 *               as the root for the subsequent recursive tree construction.
 * @param map The map structure that provides the boundaries and costs associated
 *            with different positions. It includes information crucial for checking
 *            valid localizations and calculating movement costs.
 * @param k The maximum depth of the tree to be created. This parameter restricts the
 *          depth of recursion, ensuring the tree will only be built up to this depth.
 */
void createTreeRecursivity(p_node parent, t_map map, int k);

/**
 * @brief Finds the leaf node with the minimum cost in a tree.
 *
 * @param root The root node of the tree to be searched. If the root is NULL, the function does nothing.
 * @param leaf Output parameter that will point to the leaf node with the minimum cost found. This pointer is updated during the search.
 *
 * This function traverses the tree starting from the given root node and finds the leaf node with the minimum cost.
 * The result is stored in the provided `leaf` parameter, which should be a pointer to a node pointer.
 * If multiple leaves have the same minimum cost, the first one encountered is selected.
 */
void findMinCostLeaf(p_node root, p_node *leaf);

/**
 * @brief Prints the path from a given leaf node to the root node in a tree structure.
 *
 * This function traces the path from a specified leaf node up to the root node in a tree,
 * printing each step taken along the way. The path is displayed in the format of move descriptions
 * linked by arrows, with "START" indicating the root node. If an invalid move is encountered,
 * "UNKNOWN_MOVE" is printed.
 *
 * @param leaf The leaf node from which to start tracing the path back to the root node.
 *             If this parameter is NULL, the function will not perform any action.
 */
void printPathToRoot(p_node leaf);

/**
 * @brief Recursively prints the details of a tree structure.
 *
 * This function traverses a tree starting from the root node and prints
 * detailed information about each node at each level of the tree.
 * The printed information includes position coordinates, orientation,
 * cost, and the number of children nodes `nbSons` each node has.
 *
 * @param root Pointer to the root node of the tree.
 * @param level The current level of the node being printed. This parameter
 *              is used to determine the indentation level for printing.
 */
void printTree(p_node root, int level);

/**
 * @brief Launches the phase of creating a tree structure and finding the minimum cost leaf.
 *
 * This function generates random moves, creates a tree node using the provided starting localization,
 * recursively generates the tree, and finds the minimum cost leaf in the tree. It also measures
 * the time taken for both tree creation and finding the minimum cost leaf. Upon successfully
 * finding the minimum cost leaf, it prints the path to the root and executes the path.
 *
 * @param map The map on which the tree is to be created.
 * @param start_loc Pointer to the starting localization of the tree.
 * @param s Pointer to a stack node used to store the path from the minimum cost leaf to the root.
 *
 * @return 1 on success, 0 on failure.
 */
int lauchPhase(t_map map, t_localisation *start_loc, t_stack_node *s);

/**
 * @brief Drives a vehicle from a starting location to a base station on a map.
 *
 * This function attempts to navigate from a given starting position on a map to
 * the base station position within a maximum of 10 phases. It continuously updates
 * the position through successive phases and checks if the destination base station
 * has been reached.
 *
 * @param map The map containing terrain information and base station location.
 * @param start_loc The starting localization of the vehicle, including position and orientation.
 * @param s A stack structure used to manage the traversal phases.
 *
 * If the initial position is invalid or in a crevasse, the function will print a message and return.
 * If unable to reach the base station after 10 phases, a message indicating the number of
 * completed phases will be printed.
 * If a phase fails to complete, the function will print a failure message and terminate.
 */
void drivingToBase(t_map map, t_localisation *start_loc, t_stack_node *s);

/**
 * @brief Recursively frees memory allocated to a tree structure.
 *
 * This function traverses a tree starting from the given node, freeing memory
 * allocated to its children, available moves, and the node itself.
 *
 * @param node Pointer to the root node of the tree to be freed. If the pointer
 *             is NULL, the function returns immediately.
 */
void freeTree(p_node root);


/**
 * Creates a stack node with a specified size.
 *
 * This function initializes a stack node structure with the given size, allocating
 * memory for its values and setting its initial number of elements to zero. It also
 * ensures that the size provided is positive and that memory allocation is successful.
 *
 * @param size The maximum number of elements the stack node can hold. Must be positive.
 * @return A new stack node structure initialized with the specified size.
 *         If memory allocation fails, an assertion will be triggered.
 */
t_stack_node createStackNode(int);

/**
 * @brief Pushes a node onto the stack.
 *
 * This function adds a node to the top of the stack, ensuring that the stack’s
 * constraints are respected. The stack should not be full when this function
 * is called, and any issues with the stack's pointers are logged.
 *
 * @param p_stack A pointer to the stack where the node will be pushed.
 * @param value The node that will be pushed onto the stack.
 */
void pushNode(t_stack_node *p_stack, p_node value);

/**
 * @brief Checks whether the stack node is empty.
 *
 * This function determines if the provided stack node has no elements
 * by checking if the number of elements (`nbElts`) is zero.
 *
 * @param s The stack node to be checked.
 * @return 1 if the stack node is empty, 0 otherwise.
 */
int isStackEmptyNode(t_stack_node );

/**
 * Removes the top node from the stack and returns it.
 *
 * This function asserts that the stack is not empty before removing
 * the top element.
 *
 * @param p_stack Pointer to the stack from which the top node is removed.
 * @return The top node that was removed from the stack.
 */
p_node popNode(t_stack_node *);

/**
 * @brief Retrieves the top node from the stack.
 *
 * This function returns the top node from the provided stack without
 * removing it. It is assumed that the stack is not empty when this
 * function is called.
 *
 * @param stack The stack from which to retrieve the top node.
 * @return The top node of the stack.
 */
p_node topNode(t_stack_node);

#endif //UNTITLED1_TREE_H
