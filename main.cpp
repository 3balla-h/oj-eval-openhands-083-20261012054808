#include <cstdio>
#include <cstdlib>

struct Node {
    int data;
    Node* next;
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    Node* nodes = (Node*)malloc(n * sizeof(Node));
    
    // Initialize nodes
    for (int i = 0; i < n; i++) {
        nodes[i].data = i + 1;
        if (i == n - 1) {
            nodes[i].next = &nodes[0];  // Last node points to first (circular)
        } else {
            nodes[i].next = &nodes[i + 1];
        }
    }
    
    Node* current = &nodes[0];
    int remaining = n;
    
    while (remaining > 0) {
        // Move (m-1) steps to find the node to delete
        for (int i = 1; i < m; i++) {
            current = current->next;
        }
        
        // Find the previous node
        Node* prev = current;
        while (prev->next != current) {
            prev = prev->next;
        }
        
        // Output the value to be deleted
        printf("%d\n", current->data);
        
        // Remove the node
        prev->next = current->next;
        
        // Move to next node
        Node* toDelete = current;
        current = current->next;
        
        remaining--;
        
        // If this was the last node, free memory
        if (remaining == 0) {
            free(nodes);
        }
    }
    
    return 0;
}