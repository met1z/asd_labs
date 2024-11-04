#include <iostream>
using namespace std;

class Stack {
private:
    int* stack;
    int top;
    int capacity;

    void resize(int newCapacity) {
        int* newStack = new int[newCapacity];
        for (int i = 0; i < top; i++) {
            newStack[i] = stack[i];
        }
        delete[] stack;
        stack = newStack;
        capacity = newCapacity;
    }

public:
    Stack(int size = 10) {
        stack = new int[size];
        capacity = size;
        top = 0;
    }

    ~Stack() {
        delete[] stack;
    }

    void push(int item) {
        if (top == capacity) {
            resize(capacity * 2);
        }
        stack[top++] = item;
        cout << "Added " << item << " to stack." << endl;
    }

    void pop() {
        if (!isEmpty()) {
            int removed = stack[--top];
            cout << "Removed " << removed << " from stack." << endl;
        } else {
            cout << "Stack is empty." << endl;
        }
    }

    bool isEmpty() {
        return top == 0;
    }

    void swapFirstLast() {
        if (top > 1) {
            swap(stack[0], stack[top - 1]);
            cout << "Swapped first and last elements." << endl;
        } else {
            cout << "Not enough elements to swap." << endl;
        }
    }

    void reverseStack() {
        for (int i = 0; i < top / 2; i++) {
            swap(stack[i], stack[top - i - 1]);
        }
        cout << "Stack has been reversed." << endl;
    }

    void contains(int item) {
        for (int i = 0; i < top; i++) {
            if (stack[i] == item) {
                cout << "Stack contains " << item << "." << endl;
                return;
            }
        }
        cout << item << " is not in the stack." << endl;
    }

    void clear() {
		delete[] stack;
        top = 0;
		stack = new int[capacity];
        cout << "Stack has been cleared." << endl;
    }

    void print() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
        } else {
            cout << "Stack: ";
            for (int i = 0; i < top; i++) {
                cout << stack[i] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Stack stack;
    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Add element to stack" << endl;
        cout << "2. Remove element from stack" << endl;
        cout << "3. Swap first and last element" << endl;
        cout << "4. Reverse stack" << endl;
        cout << "5. Check if element exists in stack" << endl;
        cout << "6. Clear stack" << endl;
        cout << "7. Display stack" << endl;
        cout << "8. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int item;
            cout << "Enter element to add: ";
            cin >> item;
            stack.push(item);
            break;
        }
        case 2:
            stack.pop();
            break;
        case 3:
            stack.swapFirstLast();
            break;
        case 4:
            stack.reverseStack();
            break;
        case 5: {
            int item;
            cout << "Enter element to search: ";
            cin >> item;
            stack.contains(item);
            break;
        }
        case 6:
            stack.clear();
            break;
        case 7:
            stack.print();
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
