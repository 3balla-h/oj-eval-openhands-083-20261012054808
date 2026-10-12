#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int main() {
    int n, m;
    cin >> n >> m;
    
    Node* head = 0;
    Node* prev = 0;
    
    for (int i = 1; i <= n; i++) {
        Node* node = new Node;
        node->data = i;
        if (head == 0) {
            head = node;
        } else {
            prev->next = node;
        }
        prev = node;
    }
    
    prev->next = head;
    
    Node* current = head;
    int count = n;
    
    while (count > 0) {
        for (int i = 1; i < m; i++) {
            prev = current;
            current = current->next;
        }
        
        cout << current->data << endl;
        
        prev->next = current->next;
        Node* temp = current;
        current = current->next;
        delete temp;
        count--;
    }
    
    return 0;
}