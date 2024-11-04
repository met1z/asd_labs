#include <iostream>
#include <string>

using namespace std;

struct Node {
    int key;
    int value;
    Node* next;
    Node(int k, int v) : key(k), value(v), next(nullptr) {}

	void print() {
        cout << "(" << key << ", " << value << ") ";
    }
};

class HashTable {
private:
    Node** table;
    int size;

    int hashFunction(int key) {
        return key % size;
    }

public:
    HashTable(int tableSize) : size(tableSize) {
        table = new Node*[size];
        for (int i = 0; i < size; ++i)
            table[i] = nullptr;
    }

    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            Node* entry = table[i];
            while (entry != nullptr) {
                Node* prev = entry;
                entry = entry->next;
                delete prev;
            }
            table[i] = nullptr;
        }
        delete[] table;
    }

	void print() {
		for (int i = 0; i < size; i++)
		{
			Node* current = table[i];
			cout << "[" << i << "]: ";

			while (current) {
				current->print();
				current = current->next;
			}
			cout << endl;
		}
    }

    void insert(int key, int value) {
        int hashIndex = hashFunction(key);
        Node* newNode = new Node(key, value);

        if (table[hashIndex] == nullptr) {
            table[hashIndex] = newNode;
        } else {
            Node* entry = table[hashIndex];
            while (entry->next != nullptr) {
                entry = entry->next;
            }
            entry->next = newNode;
        }
        cout << "Элемент с ключом " << key << " и значением \"" << value << "\" добавлен.\n";
    }

    int search(int key) {
        int hashIndex = hashFunction(key);
        Node* entry = table[hashIndex];
        while (entry != nullptr) {
            if (entry->key == key) return entry->value;
            entry = entry->next;
        }
        return -1;
    }

    bool remove(int key) {
        int hashIndex = hashFunction(key);
        Node* entry = table[hashIndex];
        Node* prev = nullptr;

        while (entry != nullptr && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            cout << "Элемент с ключом " << key << " не найден для удаления.\n";
            return false;
        }

        if (prev != nullptr) {
            prev->next = entry->next;
        } else {
            table[hashIndex] = entry->next;
        }

        delete entry;
        cout << "Элемент с ключом " << key << " удален.\n";
        return true;
    }
};

void menu(HashTable& hashTable) {
    int choice;
    do {
        cout << "\n Меню \n";
        cout << "1. Добавить элемент\n";
        cout << "2. Найти элемент\n";
        cout << "3. Удалить элемент\n";
        cout << "4. Показать элементы \n";
        cout << "5. Выход\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int key;
                int value;
                cout << "Введите ключ: ";
                cin >> key;
                cout << "Введите значение: ";
                cin >> value;
                hashTable.insert(key, value);
                break;
            }
            case 2: {
                int key;
                cout << "Введите ключ для поиска: ";
                cin >> key;
                int result = hashTable.search(key);
				if (result == -1) cout << "Не найден" << "\n";
                else cout << "Результат поиска: " << result  << "\n";
                break;
            }
            case 3: {
                int key;
                cout << "Введите ключ для удаления: ";
                cin >> key;
                hashTable.remove(key);
                break;
            }
            case 4:
                hashTable.print();
                break;
			case 5:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор, попробуйте снова.\n";
        }
    } while (choice != 5);
}

int main() {
    int tableSize;
    cout << "Введите размер хеш-таблицы: ";
    cin >> tableSize;

    HashTable hashTable(tableSize);
    menu(hashTable);

    return 0;
}
