#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
	int data;
	Node* next;
	Node(int data) : data(data), next(nullptr) {}
};

class List
{
private:
	Node* head;

public:
	List() : head(nullptr) {}

	void addToStart(int data)
	{
		Node *newNode = new Node(data);
		newNode->next = head;
		head = newNode;
	}

	void insertAfter(int n, int data)
	{
		Node* current = head;
		for (int i = 0; i < n && current != nullptr; i++)
		{
			current = current->next;
		}
		if (current != nullptr)
		{
			Node *newNode = new Node(data);
			newNode->next = current->next;
			current->next = newNode;
		}
	}

	void moveBy(int n)
	{
		if (head == nullptr || head->next == nullptr || n <= 0)
			return;

		Node* current = head;
		Node* prev = nullptr;
		int listLength = 0;

		while (current != nullptr)
		{
			listLength++;
			current = current->next;
		}

		if (n >= listLength)
			return;

		current = head;
		for (int i = 0; i < n; i++)
		{
			prev = current;
			current = current->next;
		}

		prev->next = nullptr;
		Node* last = current;
		while (last->next != nullptr)
		{
			last = last->next;
		}
		last->next = head;
		head = current;
	}

	void deleteNth(int n)
	{
		if (head == nullptr)
			return;

		if (n == 0)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
			return;
		}

		Node* current = head;
		for (int i = 0; i < n - 1 && current != nullptr; i++)
		{
			current = current->next;
		}

		if (current == nullptr || current->next == nullptr)
			return;

		Node *temp = current->next;
		current->next = temp->next;
		delete temp;
	}

	void deleteEveryNth(int n)
	{
		if (n <= 0 || head == nullptr)
			return;

		Node *current = head;
		Node *prev = nullptr;
		int count = 1;
		while (current != nullptr)
		{
			if (count % n == 0)
			{
				Node *temp = current;
				if (prev != nullptr)
				{
					prev->next = current->next;
				}
				else
				{
					head = current->next;
				}
				current = current->next;
				delete temp;
			}
			else
			{
				prev = current;
				current = current->next;
			}
			count++;
		}
	}

	void sortAscending()
	{
		if (head == nullptr)
			return;

		for (Node *i = head; i != nullptr; i = i->next)
		{
			for (Node *j = i->next; j != nullptr; j = j->next)
			{
				if (i->data > j->data)
				{
					swap(i->data, j->data);
				}
			}
		}
	}

	void sortDescending()
	{
		if (head == nullptr)
			return;

		for (Node *i = head; i != nullptr; i = i->next)
		{
			for (Node *j = i->next; j != nullptr; j = j->next)
			{
				if (i->data < j->data)
				{
					swap(i->data, j->data);
				}
			}
		}
	}

	List *copy()
	{
		List *newList = new List();
		Node *current = head;
		Node *tail = nullptr;

		while (current != nullptr)
		{
			Node *newNode = new Node(current->data);
			if (newList->head == nullptr)
			{
				newList->head = newNode;
				tail = newNode;
			}
			else
			{
				tail->next = newNode;
				tail = newNode;
			}
			current = current->next;
		}

		return newList;
	}

	void clear()
	{
		while (head != nullptr)
		{
			Node *temp = head;
			head = head->next;
			delete temp;
		}
	}

	void concatenate(List *other)
	{
		if (head == nullptr)
		{
			head = other->head;
		}
		else
		{
			Node *current = head;
			while (current->next != nullptr)
			{
				current = current->next;
			}
			current->next = other->head;
		}
	}

	List *commonElements(List *other)
	{
		List *result = new List();
		Node *current1 = head;
		while (current1 != nullptr)
		{
			Node *current2 = other->head;
			while (current2 != nullptr)
			{
				if (current1->data == current2->data)
				{
					result->addToStart(current1->data);
					break;
				}
				current2 = current2->next;
			}
			current1 = current1->next;
		}
		return result;
	}

	int getListSize()
	{
		int size = 0;
		Node *current = head;
		while (current != nullptr)
		{
			size++;
			current = current->next;
		}
		return size;
	}

	bool isEmpty()
	{
		return head == nullptr;
	}

	~List()
	{
		clear();
	}

	Node *getHead()
	{
		return head;
	}
};

void printList(List *list)
{
	Node *current = list->getHead();
	if (current == nullptr)
	{
		cout << "List is empty.\n";
		return;
	}

	while (current != nullptr)
	{
		cout << current->data;
		if (current->next != nullptr)
		{
			cout << " -> ";
		}
		current = current->next;
	}
	cout << endl;
}

void showMenu()
{
	cout << "\nOptions:\n";
	cout << "1. Add an item to the start\n";
	cout << "2. Insert item after n-th position\n";
	cout << "3. Move item by n positions\n";
	cout << "4. Remove the n-th item\n";
	cout << "5. Delete every n-th item\n";
	cout << "6. Sort the list (ascending or descending)\n";
	cout << "7. Make a copy of the list\n";
	cout << "8. Clear the list\n";
	cout << "9. Display the list\n";
	cout << "10. Merge two lists\n";
	cout << "11. Find common items in two lists\n";
	cout << "0. Exit\n";
	cout << "Select an option: ";
}

int main()
{
	List list1, list2;
	int choice, data, n;

	do
	{
		showMenu();
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Input data to add: ";
			cin >> data;
			list1.addToStart(data);
			break;

		case 2:
			if (list1.isEmpty())
			{
				cout << "List is empty! Please add data first.\n";
			}
			else
			{
				int size = list1.getListSize();
				cout << "Provide position to insert after (starting from 0): ";
				cin >> n;
				if (n >= size)
				{
					cout << "Error: position exceeds list size. Max index is " << size - 1 << ".\n";
				}
				else
				{
					cout << "Provide data to insert: ";
					cin >> data;
					list1.insertAfter(n, data);
				}
			}
			break;

		case 3:
			if (list1.isEmpty())
			{
				cout << "List is empty! Please add data first.\n";
			}
			else
			{
				cout << "Input number of positions to shift by: ";
				cin >> n;
				list1.moveBy(n);
			}
			break;

		case 4:
			if (list1.isEmpty())
			{
				cout << "List is empty! Please add data first.\n";
			}
			else
			{
				cout << "Provide the position of item to remove: ";
				cin >> n;
				list1.deleteNth(n);
			}
			break;

		case 5:
			if (list1.isEmpty())
			{
				cout << "List is empty! Please add data first.\n";
			}
			else
			{
				cout << "Provide step for deletion (every n-th): ";
				cin >> n;
				list1.deleteEveryNth(n);
			}
			break;

		case 6:
			if (list1.isEmpty())
			{
				cout << "List is empty! Please add data first.\n";
			}
			else
			{
				int order;
				cout << "Sort order: ascending (1) or descending (2)? ";
				cin >> order;
				if (order == 1)
				{
					list1.sortAscending();
				}
				else
				{
					list1.sortDescending();
				}
			}
			break;

		case 7:
		{
			List *copy = list1.copy();
			cout << "List copied.\n";
			printList(copy);
			delete copy;
			break;
		}

		case 8:
			list1.clear();
			cout << "The list has been cleared.\n";
			break;

		case 9:
			cout << "Displaying the list:\n";
			printList(&list1);
			break;

		case 10:
			cout << "Enter elements for the second list (type -1 to stop):\n";
			while (true)
			{
				cin >> data;
				if (data == -1)
					break;
				list2.addToStart(data);
			}
			list1.concatenate(&list2);
			cout << "Lists have been merged.\n";
			break;

		case 11:
			if (list1.isEmpty() || list2.isEmpty())
			{
				cout << "Both lists need to have elements for comparison.\n";
			}
			else
			{
				List *commonList = list1.commonElements(&list2);
				cout << "Common elements between the lists:\n";
				printList(commonList);
				delete commonList;
			}
			break;

		case 0:
			cout << "Exiting program...\n";
			break;

		default:
			cout << "Invalid choice. Please select a valid option.\n";
		}
	} while (choice != 0);

	return 0;
}
