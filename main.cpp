#include <iostream>

// Node structure for singly circular linked list
struct Node {
    int data;
    Node* next;
};

class CircularLinkedList {
private:
    Node* head;
    int size;
    
public:
    CircularLinkedList() : head(nullptr), size(0) {}
    
    ~CircularLinkedList() {
        if (head == nullptr) return;
        
        Node* current = head;
        Node* next;
        
        // Break the circular link to avoid infinite loop
        do {
            next = current->next;
            delete current;
            current = next;
        } while (current != head);
    }
    
    // Insert a new node at the end of the list
    void insert(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
        
        if (head == nullptr) {
            head = newNode;
            newNode->next = head; // Point to itself to make it circular
        } else {
            Node* current = head;
            // Find the last node (the one whose next points to head)
            while (current->next != head) {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head;
        }
        size++;
    }
    
    // Remove the m-th node starting from current position
    // Returns the value of the removed node
    int removeAndReturn(int m, Node*& current) {
        if (size == 0) return -1;
        if (size == 1) {
            int value = head->data;
            delete head;
            head = nullptr;
            current = nullptr;
            size = 0;
            return value;
        }
        
        // Move to the node before the one to be deleted
        // We need to move (m-1) steps from current
        for (int i = 1; i < m; i++) {
            current = current->next;
        }
        
        // Now current points to the node to be deleted
        Node* toDelete = current;
        Node* prev = current;
        
        // Find the previous node
        while (prev->next != toDelete) {
            prev = prev->next;
        }
        
        // Remove the node
        prev->next = toDelete->next;
        
        // Update head if we're deleting it
        if (toDelete == head) {
            head = toDelete->next;
        }
        
        // Set current to the next node after the deleted one
        current = toDelete->next;
        
        int value = toDelete->data;
        delete toDelete;
        size--;
        
        return value;
    }
    
    // Get the head node
    Node* getHead() const {
        return head;
    }
    
    // Get the size of the list
    int getSize() const {
        return size;
    }
    
    // Check if list is empty
    bool isEmpty() const {
        return size == 0;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    
    // Create circular linked list with n elements (1 to n)
    CircularLinkedList list;
    for (int i = 1; i <= n; i++) {
        list.insert(i);
    }
    
    Node* current = list.getHead();
    
    // Simulate Josephus ring elimination
    while (!list.isEmpty()) {
        int removed = list.removeAndReturn(m, current);
        std::cout << removed << std::endl;
        
        // If list is not empty, current should point to the next node
        // If current is null (which happens when we delete the last node),
        // we don't need to do anything as the loop will exit
    }
    
    return 0;
}