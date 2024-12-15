#include <iostream>
#include <string>

using namespace std;

struct Node {
    int key;
    int value;
    bool isDeleted;
    Node(int k, int v) : key(k), value(v), isDeleted(false) {}

    void print() {
        cout << "(" << key << ", " << value << ") ";
    }
};

class HashTable {
private:
    Node** table;
    int size;
    int count;
    const int MIN_SIZE = 3;

    int hashFunction(int key) {
        return key % size;
    }

    void resize(int newSize) {
        Node** newTable = new Node*[newSize];
        for (int i = 0; i < newSize; ++i) {
            newTable[i] = nullptr;
        }

        for (int i = 0; i < size; ++i) {
            if (table[i] != nullptr && !table[i]->isDeleted) {
                int newHashIndex = table[i]->key % newSize;
                while (newTable[newHashIndex] != nullptr) {
                    newHashIndex = (newHashIndex + 1) % newSize;
                }
                newTable[newHashIndex] = table[i];
            } else {
                delete table[i];
            }
        }

        delete[] table;
        table = newTable;
        size = newSize;
    }

    void grow() {
        int newSize = size * 2;
        resize(newSize);
    }

    void shrink() {
        int newSize = size / 2;
        if (newSize >= MIN_SIZE) {
            resize(newSize);
        }
    }

    double loadFactor() {
        return (double)count / size;
    }

public:
    HashTable(int tableSize) : size(tableSize), count(0) {
        table = new Node*[size];
        for (int i = 0; i < size; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            delete table[i];
        }
        delete[] table;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "]: ";
            if (table[i] != nullptr && !table[i]->isDeleted) {
                table[i]->print();
            } else {
                cout << "Empty";
            }
            cout << endl;
        }
    }

    void insert(int key, int value) {
        int hashIndex = hashFunction(key);

        while (table[hashIndex] != nullptr && !table[hashIndex]->isDeleted) {
            if (table[hashIndex]->key == key) {
                table[hashIndex]->value = value;
                return;
            }
            hashIndex = (hashIndex + 1) % size;
        }

        delete table[hashIndex];
        table[hashIndex] = new Node(key, value);
        count++;
        if (loadFactor() > 0.7) {
            grow();
        }
        cout << "Элемент с ключом " << key << " и значением \"" << value << "\" добавлен.\n";
    }

    int search(int key) {
        int hashIndex = hashFunction(key);
        while (table[hashIndex] != nullptr) {
            if (table[hashIndex]->key == key && !table[hashIndex]->isDeleted) {
                return table[hashIndex]->value;
            }
            hashIndex = (hashIndex + 1) % size;
        }
        return -1;
    }

    void remove(int key) {
        int hashIndex = hashFunction(key);

        while (table[hashIndex] != nullptr) {
            if (table[hashIndex]->key == key && !table[hashIndex]->isDeleted) {
                table[hashIndex]->isDeleted = true;
                count--;
                cout << "Элемент с ключом " << key << " удален.\n";

                if (loadFactor() < 0.5 && size > MIN_SIZE) {
                    shrink();
                }
                return;
            }
            hashIndex = (hashIndex + 1) % size;
        }
        cout << "Элемент с ключом " << key << " не найден для удаления.\n";
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

    if (tableSize < 3) tableSize = 3;

    HashTable hashTable(tableSize);
    menu(hashTable);

    return 0;
}
