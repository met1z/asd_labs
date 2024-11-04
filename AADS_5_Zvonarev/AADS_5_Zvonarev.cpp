#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int hashDivision(int key, int tableSize) {
    return key % tableSize;
}

int hashMultiplication(int key, int tableSize) {
    double A = 0.618033;
    double frac = key * A - floor(key * A);
    return floor(tableSize * frac);
}

int hashString(const string &key, int tableSize) {
    int hashValue = 0;
    for (char ch : key) {
        hashValue = (hashValue * 31 + ch) % tableSize;
    }
    return hashValue;
}

int main() {
    int tableSize;
    cout << "Введите размер хеш-таблицы: ";
    cin >> tableSize;

    while (true) {
        cout << "\nВведите строку для хеширования (или 'exit' для выхода): ";
        string input;
        cin >> input;
        
        if (input == "exit") break;

        cout << "Выберите метод хеширования:\n";
        cout << "1. Хеш-функция методом деления\n";
        cout << "2. Хеш-функция методом умножения\n";
        cout << "3. Хеш-функция для строковых ключей\n";
        cout << "Ваш выбор: ";
        
        int choice;
        cin >> choice;

        int hashValue;
        if (choice == 1) {
            int intKey = stoi(input);
            hashValue = hashDivision(intKey, tableSize);
            cout << "Хеш методом деления: " << hashValue << endl;
        } else if (choice == 2) {
            int intKey = stoi(input);
            hashValue = hashMultiplication(intKey, tableSize);
            cout << "Хеш методом умножения: " << hashValue << endl;
        } else if (choice == 3) {
            hashValue = hashString(input, tableSize);
            cout << "Хеш для строкового ключа: " << hashValue << endl;
        } else {
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    cout << "Выход из программы.\n";
    return 0;
}
