#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std

struct Flight {
    int fuel;
    int distance;
    int priority;
};

struct TreeNode {
    struct Flight flight;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(struct Flight flight) {
    struct TreeNode* newNode = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    newNode->flight = flight;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct TreeNode* insertFlight(struct TreeNode* root, struct Flight flight) {
    if (root == NULL) {
        return createNode(flight);
    }

    if (flight.priority <= root->flight.priority) {
        root->left = insertFlight(root->left, flight);
    } else {
        root->right = insertFlight(root->right, flight);
    }

    return root;
}

void calculatePriority(struct Flight* flight) {
    flight->priority = flight->fuel * flight->distance;
}

void assignPriority(struct TreeNode* root, int* currentPriority) {
    if (root != NULL) {
        assignPriority(root->left, currentPriority);

        root->flight.priority = (*currentPriority)++;
        
        assignPriority(root->right, currentPriority);
    }
}

void preOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        printf("Fuel: %d, Distance: %d, Priority: %d\n", root->flight.fuel, root->flight.distance, root->flight.priority);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void deleteFlight(struct TreeNode** root, struct Flight flight) {
    if (*root == NULL) {
        return;
    }

    if (flight.priority < (*root)->flight.priority) {
        deleteFlight(&(*root)->left, flight);
    } else if (flight.priority > (*root)->flight. priority) {
        deleteFlight(&(*root)->right, flight);
    } else {
        // El nodo a eliminar tiene 0 o 1 hijo
        if ((*root)->left == NULL) {
            struct TreeNode* temp = (*root)->right;
            free(*root);
            *root = temp;
        } else if ((*root)->right == NULL) {
            struct TreeNode* temp = (*root)->left;
            free(*root);
            *root = temp;
        } else {
            // El nodo a eliminar tiene 2 hijos
            struct TreeNode* temp = (*root)->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }

            (*root)->flight = temp->flight;
            deleteFlight(&(*root)->right, temp->flight);
        }
    }
}

int main() {
    struct TreeNode* root = NULL;
    int currentPriority = 1;

    while (1) {
        printf("\nAcciones disponibles:\n");
        printf("1. Registrar el vuelo\n");
        printf("2. Calcular la prioridad de aterrizaje\n");
        printf("3. Ubicar el vuelo en el árbol binario\n");
        printf("4. Mostrar los vuelos ordenados por prioridad\n");
        printf("5. Eliminar el avión tras aterrizar\n");
        printf("6. Salir\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                struct Flight newFlight;
                printf("Ingrese la cantidad de combustible: ");
                scanf("%d", &newFlight.fuel);
                printf("Ingrese la distancia en millas náuticas: ");
                scanf("%d", &newFlight.distance);
                calculatePriority(&newFlight);
                root = insertFlight(root, newFlight);
                break;
            }
            case 2: {
                assignPriority(root, &currentPriority);
                break;
            }
            case 3: {
                printf("Vuelos ordenados por prioridad:\n");
                preOrderTraversal(root);
                break;
            }
            case 4: {
                printf("Vuelos ordenados por prioridad:\n");
                preOrderTraversal(root);
                break;
            }
            case 5: {
                struct Flight landedFlight;
                printf("Ingrese la prioridad del avión que aterriza: ");
                scanf("%d", &landedFlight.priority);
                deleteFlight(&root, landedFlight);
                break;
            }
            case 6:
                // Liberar la memoria y salir
                return 0;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    }

    return 0;
}
