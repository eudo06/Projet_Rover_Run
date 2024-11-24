/*
#include "complexite.h"
// Définitions des types de terrains martiens
#define PLAINE 0
#define ERG 1
#define REG 2
#define CREVASSE 3

// Coûts associés aux types de terrains
#define COUT_PLAINE 1
#define COUT_ERG 2
#define COUT_REG 4
#define COUT_CREVASSE 10000

// Structure représentant un nœud de l'arbre N-aire


// Fonction pour créer un nouveau nœud
Node* create_node(int cost, int movement, int max_children, Node* parent) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->cost = cost;
    new_node->movement = movement;
    new_node->num_children = 0;
    new_node->children = (Node**)malloc(max_children * sizeof(Node*));
    new_node->parent = parent;
    return new_node;
}

// Fonction pour ajouter un enfant à un nœud
void add_child(Node* parent, Node* child) {
    parent->children[parent->num_children++] = child;
}

// Fonction récursive pour construire l'arbre N-aire
void construct_tree(Node* root, int level, int max_levels, int* movements, int num_movements) {
    if (level == max_levels) return;  // Arrêter la récursion si le niveau maximal est atteint

    for (int i = 0; i < num_movements; i++) {
        // Simuler le calcul du coût basé sur le mouvement
        int new_cost = root->cost + movements[i];

        // Créer un nouveau nœud enfant et le lier au parent
        Node* child = create_node(new_cost, movements[i], num_movements - 1, root);
        add_child(root, child);

        // Construire récursivement les sous-arbres pour cet enfant
        construct_tree(child, level + 1, max_levels, movements, num_movements - 1);
    }
}

// Fonction récursive pour trouver la feuille avec le coût minimal
void find_min_cost_leaf(Node* root, int* min_cost, Node** min_leaf) {
    if (root->num_children == 0) {  // Si c'est une feuille
        if (root->cost < *min_cost) {
            *min_cost = root->cost;
            *min_leaf = root;
        }
        return;
    }

    for (int i = 0; i < root->num_children; i++) {
        find_min_cost_leaf(root->children[i], min_cost, min_leaf);
    }
}

// Fonction pour afficher le chemin de la racine à une feuille
void print_path(Node* root, Node* leaf) {
    if (!leaf) return;

    printf("Chemin de la racine à la feuille de coût minimal : ");
    Node* current = leaf;
    while (current != NULL) {
        if (current->movement != -1) {  // Ignorer la racine qui n'a pas de mouvement
            printf("%d <- ", current->movement);
        }
        current = current->parent;
    }
    printf("Racine\n");
}

// Fonction pour libérer la mémoire de l'arbre
void free_tree(Node* root) {
    for (int i = 0; i < root->num_children; i++) {
        free_tree(root->children[i]);
    }
    free(root->children);
    free(root);
}

// Fonction principale
int main() {
    int movements[] = {10, 15, 20, 25, 30, 35, 40, 45, 50}; // Tous les coûts positifs // Liste de mouvements
    int max_levels[] = {3, 4, 5}; // Niveaux de test progressifs

    printf("=== Passage à l'échelle : Tests progressifs ===\n");
    for (int i = 0; i < 3; i++) {
        printf("\nTest avec %d niveaux et %d mouvements\n", max_levels[i], max_levels[i]);

        // Créer la racine de l'arbre
        Node* root = create_node(0, -1, max_levels[i], NULL);

        // Mesurer le temps de construction de l'arbre
        clock_t start_construction = clock();
        construct_tree(root, 0, max_levels[i], movements, max_levels[i]);
        clock_t end_construction = clock();
        double construction_time = ((double)(end_construction - start_construction)) / CLOCKS_PER_SEC;

        // Rechercher la feuille de coût minimal
        int min_cost = INT_MAX;
        Node* min_leaf = NULL;
        clock_t start_search = clock();
        find_min_cost_leaf(root, &min_cost, &min_leaf);
        clock_t end_search = clock();
        double search_time = ((double)(end_search - start_search)) / CLOCKS_PER_SEC;

        // Afficher les résultats
        printf("Temps de construction de l'arbre : %.6f secondes\n", construction_time);
        printf("Temps de recherche du coût minimal : %.6f secondes\n", search_time);
        printf("Coût minimal trouvé : %d\n", min_cost);
        print_path(root, min_leaf);

        // Libérer la mémoire de l'arbre
        free_tree(root);
    }

    printf("\n=== Fin des tests progressifs ===\n");

    return 0;
}
*/