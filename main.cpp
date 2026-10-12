#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = NULL;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    // Create circular linked list
    Node* head = NULL;
    Node* tail = NULL;
    
    for (int i = 1; i <= n; i++) {
        Node* newNode = new Node(i);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
            newNode->next = head; // Make it circular
        } else {
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
        }
    }
    
    Node* current = head;
    int remaining = n;
    
    while (remaining > 0) {
        // Move (m-1) steps to find the node to delete
        for (int i = 1; i < m; i++) {
            current = current->next;
        }
        
        // Now current points to the node to be deleted
        Node* toDelete = current;
        
        // Find the previous node
        Node* prev = current;
        while (prev->next != toDelete) {
            prev = prev->next;
        }
        
        // Remove the node
        prev->next = toDelete->next;
        
        // Update head if we're deleting it
        if (toDelete == head) {
            head = toDelete->next;
        }
        
        // Update tail if we're deleting it
        if (toDelete == tail) {
            tail = prev;
        }
        
        // Set current to the next node after the deleted one
        current = toDelete->next;
        
        cout << toDelete->data << endl;
        delete toDelete;
        remaining--;
    }
    
    return 0;
}