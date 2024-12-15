#include <iostream>
#include <vector>

class BinaryTree {
private:
    struct TreeNode {
        int value;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    TreeNode* addNode(TreeNode* node, int value) {
        if (!node) return new TreeNode(value);
        if (value < node->value) {
            node->left = addNode(node->left, value);
        } else {
            node->right = addNode(node->right, value);
        }
        return node;
    }

    TreeNode* deleteNode(TreeNode* node, int value) {
        if (!node) return nullptr;

        if (value < node->value) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->value) {
            node->right = deleteNode(node->right, value);
        } else {
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = node->right;
            while (temp->left) {
                temp = temp->left;
            }
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->value);
        }
        return node;
    }

    bool findNodePreOrder(TreeNode* node, int value, std::vector<int>& path) {
        if (!node) return false;

        std::cout << node->value << " ";
        path.push_back(node->value);
        if (node->value == value) return true;

        if (findNodePreOrder(node->left, value, path)) return true;
        if (findNodePreOrder(node->right, value, path)) return true;

        path.pop_back();
        return false;
    }

    bool findNodePostOrder(TreeNode* node, int value, std::vector<int>& path) {
        if (!node) return false;

        if (findNodePostOrder(node->left, value, path)) return true;
        if (findNodePostOrder(node->right, value, path)) return true;

        std::cout << node->value << " ";
        path.push_back(node->value);
        if (node->value == value) return true;

        if (path.back() == value) return true;
        path.pop_back();
        return false;
    }

    bool findNodeInOrder(TreeNode* node, int value, std::vector<int>& path) {
        if (!node) return false;

        if (findNodeInOrder(node->left, value, path)) return true;

        std::cout << node->value << " ";
        path.push_back(node->value);
        if (node->value == value) return true;

        if (findNodeInOrder(node->right, value, path)) return true;

        path.pop_back();
        return false;
    }

    void collectValues(TreeNode* node, std::vector<int>& values) {
        if (!node) return;
        collectValues(node->left, values);
        values.push_back(node->value);
        collectValues(node->right, values);
    }

public:
    BinaryTree() : root(nullptr) {}

    void add(int value) {
        root = addNode(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    void search(int value, int method) {
        std::vector<int> path;
        bool found = false;

        switch (method) {
        case 1:
            found = findNodePreOrder(root, value, path);
            std::cout << "Прямой обход: ";
            break;
        case 2:
            found = findNodePostOrder(root, value, path);
            std::cout << "Обратный обход: ";
            break;
        case 3:
            found = findNodeInOrder(root, value, path);
            std::cout << "Симметричный обход: ";
            break;
        default:
            std::cout << "Неверный метод поиска.\n";
            return;
        }

        if (found) {
            for (int val : path) {
                std::cout << val << " ";
            }
            std::cout << "\n";
        } else {
            std::cout << "Элемент " << value << " не найден.\n";
        }
    }

	void printAllValues() {
        std::vector<int> values;
        collectValues(root, values);
        for (int val : values) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    BinaryTree tree;
    int choice, value, method;

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить элемент\n";
        std::cout << "2. Удалить элемент\n";
        std::cout << "3. Найти элемент (выбрать метод обхода)\n";
		std::cout << "4. Показать все значения\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите опцию: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите значение для добавления: ";
            std::cin >> value;
            tree.add(value);
            std::cout << "Элемент добавлен.\n";
            break;
        case 2:
            std::cout << "Введите значение для удаления: ";
            std::cin >> value;
            tree.remove(value);
            std::cout << "Элемент удален.\n";
            break;
        case 3:
            std::cout << "Введите значение для поиска: ";
            std::cin >> value;
            std::cout << "Выберите метод поиска (1 - прямой, 2 - обратный, 3 - симметричный): ";
            std::cin >> method;
            tree.search(value, method);
            break;
        case 4:
            tree.printAllValues();
            break;
        case 0:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Некорректный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
    return 0;
}
