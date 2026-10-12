#include <stdio.h>
#include <stdlib.h>

// Node structure for singly circular linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of circular linked list
void insert(struct Node** head, int value, int* size) {
    struct Node* newNode = createNode(value);
    
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head; // Point to itself to make it circular
    } else {
        struct Node* current = *head;
        // Find the last node (the one whose next points to head)
        while (current->next != *head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = *head;
    }
    (*size)++;
}

// Function to remove the m-th node and return its value
int removeAndReturn(struct Node** head, int m, struct Node** current, int* size) {
    if (*size == 0) return -1;
    if (*size == 1) {
        int value = (*head)->data;
        free(*head);
        *head = NULL;
        *current = NULL;
        *size = 0;
        return value;
    }
    
    // Move to the node before the one to be deleted
    // We need to move (m-1) steps from current
    for (int i = 1; i < m; i++) {
        *current = (*current)->next;
    }
    
    // Now current points to the node to be deleted
    struct Node* toDelete = *current;
    struct Node* prev = *current;
    
    // Find the previous node
    while (prev->next != toDelete) {
        prev = prev->next;
    }
    
    // Remove the node
    prev->next = toDelete->next;
    
    // Update head if we're deleting it
    if (toDelete == *head) {
        *head = toDelete->next;
    }
    
    // Set current to the next node after the deleted one
    *current = toDelete->next;
    
    int value = toDelete->data;
    free(toDelete);
    (*size)--;
    
    return value;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    struct Node* head = NULL;
    int size = 0;
    
    // Create circular linked list with n elements (1 to n)
    for (int i = 1; i <= n; i++) {
        insert(&head, i, &size);
    }
    
    struct Node* current = head;
    
    // Simulate Josephus ring elimination
    while (size > 0) {
        int removed = removeAndReturn(&head, m, &current, &size);
        printf("%d\n", removed);
        
        // If list is not empty, current should point to the next node
        // If current is null (which happens when we delete the last node),
        // we don't need to do anything as the loop will exit
    }
    
    return 0;
}