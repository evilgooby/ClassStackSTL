#include <iostream>
#include <list>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

// Класс DynamicListSTL, использующий контейнеры STL
class DynamicListSTL {
private:
    std::list<int> lst;

public:
    void create();
    void display();
    int search(int value);
    void add(int value);
    void deleteAt(int index);
    void modify(int index, int newValue);
    int count();
    void addStack(int a, int b);
    void clear();
};

// Функция для безопасного ввода целого числа
int safeInputInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка оставшегося ввода
            return value;
        } else {
            std::cin.clear(); // Сброс флагов ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка ввода
            std::cout << "Ошибка ввода! Пожалуйста, введите целое число.\n";
        }
    }
}

// Функция для ввода нескольких целых чисел в одной строке
std::vector<int> inputIntegers(int count) {
    std::vector<int> numbers;
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        int number;
        bool error = false;
        numbers.clear();

        while (iss >> number) {
            numbers.push_back(number);
        }

        if (numbers.size() != count) {
            std::cout << "Ожидалось " << count << " чисел. Пожалуйста, попробуйте снова:\n";
            continue;
        }

        // Проверка на наличие нечисловых символов
        if (iss.fail() && !iss.eof()) {
            std::cout << "Ошибка ввода! Пожалуйста, введите " << count << " целых чисел, разделенных пробелами:\n";
            continue;
        }

        break;
    }
    return numbers;
}

// Реализация методов класса DynamicListSTL
void DynamicListSTL::create() {
    clear();
    int n = safeInputInt("Введите количество элементов для добавления: ");
    std::cout << "Введите " << n << " целых чисел:\n";
    std::vector<int> values = inputIntegers(n);
    for (int val : values) {
        lst.push_back(val);
    }
}

void DynamicListSTL::display() {
    int index = 0;
    for (auto it = lst.begin(); it != lst.end(); ++it, ++index) {
        std::cout << "Элемент с индексом " << index << ": " << *it << "\n";
    }
}

int DynamicListSTL::search(int value) {
    int index = 0;
    for (auto it = lst.begin(); it != lst.end(); ++it, ++index) {
        if (*it == value)
            return index;
    }
    return -1;
}

void DynamicListSTL::add(int value) {
    lst.push_back(value);
}

void DynamicListSTL::deleteAt(int index) {
    if (index < 0 || index >= lst.size()) {
        std::cout << "Неверный индекс.\n";
        return;
    }
    auto it = lst.begin();
    std::advance(it, index);
    lst.erase(it);
}

void DynamicListSTL::modify(int index, int newValue) {
    if (index < 0 || index >= lst.size()) {
        std::cout << "Неверный индекс.\n";
        return;
    }
    auto it = lst.begin();
    std::advance(it, index);
    *it = newValue;
}

int DynamicListSTL::count() {
    return lst.size();
}

void DynamicListSTL::clear() {
    lst.clear();
}

//Поместили в стек все значения, попадающие в заданный интервал
void DynamicListSTL::addStack(int a, int b) {
    std::stack<int> s;
    for (auto val : lst) {
        if (val >= a && val <= b)
            s.push(val);
    }
    std::cout << "Содержимое стека:\n";
    while (!s.empty()) {
        std::cout << s.top() << "\n";
        s.pop();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    DynamicListSTL list;
    int choice;
    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Создать список\n";
        std::cout << "2. Вывести список\n";
        std::cout << "3. Поиск элемента по значению\n";
        std::cout << "4. Добавить элемент\n";
        std::cout << "5. Удалить элемент по индексу\n";
        std::cout << "6. Изменить значение элемента\n";
        std::cout << "7. Подсчитать количество элементов\n";
        std::cout << "8. Положить числа в диапозоне в стек\n";
        std::cout << "9. Очистить список\n";
        std::cout << "0. Выход\n";
        choice = safeInputInt("Введите ваш выбор: ");
        switch (choice) {
            case 1:
                list.create();
                break;
            case 2:
                list.display();
                break;
            case 3: {
                int val = safeInputInt("Введите значение для поиска: ");
                int idx = list.search(val);
                if (idx != -1)
                    std::cout << "Значение найдено на индексе " << idx << "\n";
                else
                    std::cout << "Значение не найдено в списке.\n";
                break;
            }
            case 4: {
                int val = safeInputInt("Введите значение для добавления: ");
                list.add(val);
                break;
            }
            case 5: {
                int idx = safeInputInt("Введите индекс для удаления: ");
                list.deleteAt(idx);
                break;
            }
            case 6: {
                int idx = safeInputInt("Введите индекс для изменения: ");
                int val = safeInputInt("Введите новое значение: ");
                list.modify(idx, val);
                break;
            }
            case 7:
                std::cout << "Количество элементов: " << list.count() << "\n";
                break;
            case 8: {
                int a = safeInputInt("Введите значение a: ");
                int b = safeInputInt("Введите значение b: ");
                list.addStack(a, b);
                break;
            }
            case 9:
                list.clear();
                std::cout << "Список очищен.\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Неверный выбор.\n";
        }
    } while (choice != 0);
    return 0;
}
