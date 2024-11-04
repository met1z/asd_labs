#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(int data) {
        Node* newNode = new Node(data);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "Queue is empty!\n";
            return;
        }
        Node* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    void contains(int data) {
        Node* current = front;
        while (current != nullptr) {
            if (current->data == data) {
                cout << "Queue contains " << data << "." << endl;
                return;
            }
            current = current->next;
        }
        cout << data << " is not in the stack." << endl;
    }

    void swapFrontAndRear() {
		if (front == nullptr || front == rear) {
			cout << "Need at least 2 elements.\n";
			return;
		}

		if (front->next == rear) {
			rear->next = front;
			front->next = nullptr;
			front = rear;
			rear = rear->next;
			return;
		}

		Node* current = front;
		Node* prev = nullptr;

		while (current->next != nullptr) {
			prev = current;
			current = current->next;
		}

		if (prev != nullptr) {
			current->next = front->next;
			prev->next = front;
			front->next = nullptr;

			rear = front;
			front = current;
		}
	}


    void reverse() {
        Node* prev = nullptr;
        Node* current = front;
        Node* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        rear = front;
        front = prev;
    }

    void clear() {
        while (front != nullptr) {
            dequeue();
        }
        cout << "Queue cleared!\n";
    }

    void print() {
        Node* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    Queue queue;
    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Add element to queue" << endl;
        cout << "2. Remove element from queue" << endl;
        cout << "3. Swap first and last element" << endl;
        cout << "4. Reverse queue" << endl;
        cout << "5. Check if element exists in queue" << endl;
        cout << "6. Clear queue" << endl;
        cout << "7. Display queue" << endl;
        cout << "8. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int item;
            cout << "Enter element to add: ";
            cin >> item;
            queue.enqueue(item);
            break;
        }
        case 2:
            queue.dequeue();
            break;
        case 3:
            queue.swapFrontAndRear();
            break;
        case 4:
            queue.reverse();
            break;
        case 5: {
            int item;
            cout << "Enter element to search: ";
            cin >> item;
            queue.contains(item);
            break;
        }
        case 6:
            queue.clear();
            break;
        case 7:
            queue.print();
            break;
        case 8:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid input. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}

