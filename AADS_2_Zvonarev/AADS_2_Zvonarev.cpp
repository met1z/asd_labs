#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {}
};

class CircularList {
private:
    Node* head;

public:
    CircularList() : head(nullptr) {}

    void addToEnd(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }

    int josephusProblem(int m) {
        if (head == nullptr)
            return -1;

        Node* current = head;
        Node* prev = nullptr;

        while (current->next != head) {
            current = current->next;
        }
        current->next = head;

        current = head;
        
        while (current->next != current) {
            for (int count = 1; count < m; count++) {
                prev = current;
                current = current->next;
            }

            prev->next = current->next;
            delete current;
            current = prev->next;
        }

        return current->data;
    }

    ~CircularList() {
        if (head == nullptr) return;

        Node* temp = head;
        do {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);
    }
};

int main() {
    int n, m;
    
    cout << "Enter number of soldiers (n): ";
    cin >> n;
    cout << "Enter step for elimination (m): ";
    cin >> m;

    CircularList soldiers;
    for (int i = 1; i <= n; i++) {
        soldiers.addToEnd(i);
    }

    int survivor = soldiers.josephusProblem(m);
    cout << "The last remaining soldier is at position: " << survivor << endl;

    return 0;
}

