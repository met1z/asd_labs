#include <iostream>
using namespace std;

enum Color
{
	RED,
	BLACK
};

struct Node
{
	int value;
	Color color;
	Node *left, *right, *parent;

	Node(int val) : value(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree
{
private:
	Node *root;

	void rotateLeft(Node *&node)
	{
		Node *rightChild = node->right;
		node->right = rightChild->left;

		if (rightChild->left != nullptr)
		{
			rightChild->left->parent = node;
		}

		rightChild->parent = node->parent;

		if (node->parent == nullptr)
		{
			root = rightChild;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = rightChild;
		}
		else
		{
			node->parent->right = rightChild;
		}

		rightChild->left = node;
		node->parent = rightChild;
	}

	void rotateRight(Node *&node)
	{
		Node *leftChild = node->left;
		node->left = leftChild->right;

		if (leftChild->right != nullptr)
		{
			leftChild->right->parent = node;
		}

		leftChild->parent = node->parent;

		if (node->parent == nullptr)
		{
			root = leftChild;
		}
		else if (node == node->parent->right)
		{
			node->parent->right = leftChild;
		}
		else
		{
			node->parent->left = leftChild;
		}

		leftChild->right = node;
		node->parent = leftChild;
	}

	void fixInsertion(Node *&node)
	{
		while (node != root && node->parent->color == RED)
		{
			Node *grandparent = node->parent->parent;

			if (node->parent == grandparent->left)
			{
				Node *uncle = grandparent->right;

				if (uncle && uncle->color == RED)
				{
					node->parent->color = BLACK;
					uncle->color = BLACK;
					grandparent->color = RED;
					node = grandparent;
				}
				else
				{
					if (node == node->parent->right)
					{
						node = node->parent;
						rotateLeft(node);
					}
					node->parent->color = BLACK;
					grandparent->color = RED;
					rotateRight(grandparent);
				}
			}
			else
			{
				Node *uncle = grandparent->left;

				if (uncle && uncle->color == RED)
				{
					node->parent->color = BLACK;
					uncle->color = BLACK;
					grandparent->color = RED;
					node = grandparent;
				}
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						rotateRight(node);
					}
					node->parent->color = BLACK;
					grandparent->color = RED;
					rotateLeft(grandparent);
				}
			}
		}
		root->color = BLACK;
	}

	void insertNode(Node *&root, Node *&newNode)
	{
		if (!root)
		{
			root = newNode;
		}
		else if (newNode->value < root->value)
		{
			insertNode(root->left, newNode);
			root->left->parent = root;
		}
		else if (newNode->value > root->value)
		{
			insertNode(root->right, newNode);
			root->right->parent = root;
		}
	}

	Node *minimum(Node *node)
	{
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}

	void replaceNode(Node *oldNode, Node *newNode)
	{
		if (oldNode->parent == nullptr)
		{
			root = newNode;
		}
		else if (oldNode == oldNode->parent->left)
		{
			oldNode->parent->left = newNode;
		}
		else
		{
			oldNode->parent->right = newNode;
		}
		if (newNode)
		{
			newNode->parent = oldNode->parent;
		}
	}

	void fixDeletion(Node *&node)
	{
		while (node != root && node->color == BLACK)
		{
			if (node == node->parent->left)
			{
				Node *sibling = node->parent->right;

				if (sibling->color == RED)
				{
					sibling->color = BLACK;
					node->parent->color = RED;
					rotateLeft(node->parent);
					sibling = node->parent->right;
				}

				if ((!sibling->left || sibling->left->color == BLACK) &&
					(!sibling->right || sibling->right->color == BLACK))
				{
					sibling->color = RED;
					node = node->parent;
				}
				else
				{
					if (!sibling->right || sibling->right->color == BLACK)
					{
						if (sibling->left)
							sibling->left->color = BLACK;
						sibling->color = RED;
						rotateRight(sibling);
						sibling = node->parent->right;
					}
					sibling->color = node->parent->color;
					node->parent->color = BLACK;
					if (sibling->right)
						sibling->right->color = BLACK;
					rotateLeft(node->parent);
					node = root;
				}
			}
			else
			{
				Node *sibling = node->parent->left;

				if (sibling->color == RED)
				{
					sibling->color = BLACK;
					node->parent->color = RED;
					rotateRight(node->parent);
					sibling = node->parent->left;
				}

				if ((!sibling->left || sibling->left->color == BLACK) &&
					(!sibling->right || sibling->right->color == BLACK))
				{
					sibling->color = RED;
					node = node->parent;
				}
				else
				{
					if (!sibling->left || sibling->left->color == BLACK)
					{
						if (sibling->right)
							sibling->right->color = BLACK;
						sibling->color = RED;
						rotateLeft(sibling);
						sibling = node->parent->left;
					}
					sibling->color = node->parent->color;
					node->parent->color = BLACK;
					if (sibling->left)
						sibling->left->color = BLACK;
					rotateRight(node->parent);
					node = root;
				}
			}
		}
		node->color = BLACK;
	}

	void deleteNodeHelper(Node *&root, int value)
	{
		Node *node = root;
		Node *toDelete = nullptr, *child = nullptr;
		Color originalColor;

		while (node != nullptr)
		{
			if (value == node->value)
			{
				toDelete = node;
				break;
			}
			else if (value < node->value)
			{
				node = node->left;
			}
			else
			{
				node = node->right;
			}
		}

		if (!toDelete)
			return;

		originalColor = toDelete->color;

		if (toDelete->left == nullptr)
		{
			child = toDelete->right;
			replaceNode(toDelete, toDelete->right);
		}
		else if (toDelete->right == nullptr)
		{
			child = toDelete->left;
			replaceNode(toDelete, toDelete->left);
		}
		else
		{
			Node *successor = minimum(toDelete->right);
			originalColor = successor->color;
			child = successor->right;

			if (successor->parent == toDelete)
			{
				if (child)
					child->parent = successor;
			}
			else
			{
				replaceNode(successor, successor->right);
				successor->right = toDelete->right;
				successor->right->parent = successor;
			}

			replaceNode(toDelete, successor);
			successor->left = toDelete->left;
			successor->left->parent = successor;
			successor->color = toDelete->color;
		}

		delete toDelete;

		if (originalColor == BLACK && child)
		{
			fixDeletion(child);
		}
	}

public:
	RedBlackTree() : root(nullptr) {}

	void insert(int value)
	{
		Node *newNode = new Node(value);
		insertNode(root, newNode);
		fixInsertion(newNode);
	}

	void deleteNode(int value)
	{
		deleteNodeHelper(root, value);
	}

	void printTree()
	{
		printInOrder(root);
		cout << endl;
	}

	void printInOrder(Node *node)
	{
		if (!node)
			return;
		printInOrder(node->left);
		cout << node->value << " (" << (node->color == RED ? "RED" : "BLACK") << ") ";
		printInOrder(node->right);
	}
};

int main()
{
	RedBlackTree tree;
	int choice, value;
	do
	{
		cout << "\nМеню:\n";
		cout << "1. Добавить элемент\n";
		cout << "2. Удалить элемент\n";
		cout << "3. Показать элементы\n";
		cout << "0. Выход\n";
		cout << "Выбор: ";
		cin >> choice;
		if (choice == 1)
		{
			cout << "Введите: ";
			cin >> value;
			tree.insert(value);
		}
		else if (choice == 2)
		{
			cout << "Удалить: ";
			cin >> value;
			tree.deleteNode(value);
		}
		else if (choice == 3)
		{
			tree.printTree();
		}
	} while (choice != 0);
	return 0;
}
