#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class AVLTree {
private:
    struct TreeNode {
        int value;
        int height;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int val) : value(val), height(1), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    int getHeight(TreeNode* node) {
        return node ? node->height : 0;
    }

    void updateHeight(TreeNode* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int getBalance(TreeNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    TreeNode* balance(TreeNode* node) {
        int balanceFactor = getBalance(node);

        if (balanceFactor > 1) {
            if (getBalance(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (balanceFactor < -1) {
            if (getBalance(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    TreeNode* addNode(TreeNode* node, int value) {
        if (!node) return new TreeNode(value);

        if (value < node->value) {
            node->left = addNode(node->left, value);
        } else if (value > node->value) {
            node->right = addNode(node->right, value);
        } else {
            return node;
        }

        updateHeight(node);
        return balance(node);
    }

    TreeNode* getMinValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current->left) current = current->left;
        return current;
    }

    TreeNode* deleteNode(TreeNode* node, int value) {
        if (!node) return nullptr;

        if (value < node->value) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->value) {
            node->right = deleteNode(node->right, value);
        } else {
            if (!node->left || !node->right) {
                TreeNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }

            TreeNode* temp = getMinValueNode(node->right);
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->value);
        }

        updateHeight(node);
        return balance(node);
    }

    void printPreOrder(TreeNode* node) {
        if (!node) return;
        cout << node->value << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }

    void printInOrder(TreeNode* node) {
        if (!node) return;
        printInOrder(node->left);
        cout << node->value << " ";
        printInOrder(node->right);
    }

    void printPostOrder(TreeNode* node) {
        if (!node) return;
        printPostOrder(node->left);
        printPostOrder(node->right);
        cout << node->value << " ";
    }

public:
    AVLTree() : root(nullptr) {}

    void add(int value) {
        root = addNode(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    void printAllValues(int method) {
        switch (method) {
        case 1:
            cout << "Прямой обход (PreOrder): ";
            printPreOrder(root);
            break;
        case 2:
            cout << "Симметричный обход (InOrder): ";
            printInOrder(root);
            break;
        case 3:
            cout << "Обратный обход (PostOrder): ";
            printPostOrder(root);
            break;
        default:
            cout << "Некорректный метод.\n";
            return;
        }
        cout << "\n";
    }
};

int main() {
    AVLTree tree;
    int choice, value, method;

    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить элемент\n";
        cout << "2. Удалить элемент\n";
        cout << "3. Показать все значения (выбрать метод обхода)\n";
        cout << "0. Выход\n";
        cout << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите значение для добавления: ";
            cin >> value;
            tree.add(value);
            cout << "Элемент добавлен.\n";
            break;
        case 2:
            cout << "Введите значение для удаления: ";
            cin >> value;
            tree.remove(value);
            cout << "Элемент удален.\n";
            break;
        case 3:
            cout << "Выберите метод обхода (1 - прямой, 2 - симметричный, 3 - обратный): ";
            cin >> method;
            tree.printAllValues(method);
            break;
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Некорректный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
