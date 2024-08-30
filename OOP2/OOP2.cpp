#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
// Клас AssocArray для роботи з асоціативним масивом
template <typename Key, typename Value>
class AssocArray {
public:
    // Конструктор за замовчуванням
    AssocArray() = default;

    // Конструктор з параметрами
    AssocArray(const std::map<Key, Value>& initMap) : data(initMap) {}

    // Конструктор копіювання
    AssocArray(const AssocArray& other) : data(other.data) {}

    // Оператор присвоєння
    AssocArray& operator=(const AssocArray& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    // Перевантаження оператора індексації
    Value& operator[](const Key& key) {
        return data[key];
    }

    const Value& operator[](const Key& key) const {
        return data.at(key);
    }

    // Перевантаження оператора -> для "розумного доступу"
    Value* operator->() {
        return &data.begin()->second;
    }

    // Перевантаження оператора потокового введення
    friend std::istream& operator>>(std::istream& in, AssocArray& array) {
        Key key;
        Value value;
        while (in >> key >> value) {
            array.data[key] = value;
        }
        return in;
    }

    // Перевантаження оператора потокового виведення
    friend std::ostream& operator<<(std::ostream& out, const AssocArray& array) {
        for (const auto& pair : array.data) {
            out << pair.first << ": " << pair.second << "\n";
        }
        return out;
    }

    // Збереження на диск
    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << *this;
            outFile.close();
        }
    }

    // Відновлення з диска
    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            inFile >> *this;
            inFile.close();
        }
    }

    // Діалогове керування
    void displayMenu() const {
        std::cout << "1. Показати всі елементи\n";
        std::cout << "2. Додати елемент\n";
        std::cout << "3. Видалити елемент\n";
        std::cout << "4. Знайти елемент\n";
        std::cout << "5. Зберегти на диск\n";
        std::cout << "6. Завантажити з диска\n";
        std::cout << "7. Вийти\n";
    }

    void runDialog() {
        int choice;
        do {
            displayMenu();
            std::cin >> choice;
            switch (choice) {
            case 1:
                std::cout << *this;
                break;
            case 2: {
                Key key;
                Value value;
                std::cout << "Введіть ключ та значення: ";
                std::cin >> key >> value;
                data[key] = value;
                break;
            }
            case 3: {
                Key key;
                std::cout << "Введіть ключ для видалення: ";
                std::cin >> key;
                data.erase(key);
                break;
            }
            case 4: {
                Key key;
                std::cout << "Введіть ключ для пошуку: ";
                std::cin >> key;
                auto it = data.find(key);
                if (it != data.end()) {
                    std::cout << "Значення: " << it->second << "\n";
                }
                else {
                    std::cout << "Ключ не знайдено\n";
                }
                break;
            }
            case 5: {
                std::string filename;
                std::cout << "Введіть ім'я файлу для збереження: ";
                std::cin >> filename;
                saveToFile(filename);
                break;
            }
            case 6: {
                std::string filename;
                std::cout << "Введіть ім'я файлу для завантаження: ";
                std::cin >> filename;
                loadFromFile(filename);
                break;
            }
            case 7:
                std::cout << "Вихід...\n";
                break;
            default:
                std::cout << "Невірний вибір\n";
            }
        } while (choice != 7);
    }

private:
    std::map<Key, Value> data;
};

// Демонстраційна програма
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    AssocArray<std::string, int> array;

    // Додавання елементів
    array["apple"] = 3;
    array["banana"] = 2;
    array["orange"] = 5;

    // Виведення асоціативного масиву
    std::cout << "Асоціативний масив:\n" << array << std::endl;

    // Збереження на диск
    array.saveToFile("assoc_array.txt");

    // Завантаження з диска
    AssocArray<std::string, int> loadedArray;
    loadedArray.loadFromFile("assoc_array.txt");

    // Виведення завантаженого асоціативного масиву
    std::cout << "Завантажений асоціативний масив:\n" << loadedArray << std::endl;

    // Діалогове керування
    loadedArray.runDialog();

    return 0;
}

