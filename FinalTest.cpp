#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <limits>

using namespace std;

// Функция для безопасного ввода чисел
template <typename T>
T getInput(const string &prompt)
{
    T value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Пожалуйста, введите корректное значение.\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Задание 23: Сравнение двух чисел
void task23()
{
    cout << "\n=== Задание 23 ===" << endl;
    int num1 = getInput<int>("Введите первое целое число: ");
    int num2 = getInput<int>("Введите второе целое число: ");

    cout << "1. Числа " << (num1 == num2 ? "" : "не ") << "равны" << endl;
    cout << "2. Большее число: " << (num1 > num2 ? num1 : num2) << endl;
    cout << "3. Меньшее число: " << (num1 < num2 ? num1 : num2) << endl;
    cout << "4. Первое число " << (num1 >= num2 ? "" : "не ") << "больше или равно второму" << endl;
    cout << "5. Первое число " << (num1 <= num2 ? "" : "не ") << "меньше или равно второму" << endl;
}

// Задание 24: Логические операции с тремя числами
void task24()
{
    cout << "\n=== Задание 24 ===" << endl;
    int nums[3];
    cout << "Введите три целых числа:\n";
    for (int i = 0; i < 3; i++)
    {
        nums[i] = getInput<int>("Число " + to_string(i + 1) + ": ");
    }

    bool all_positive = nums[0] > 0 && nums[1] > 0 && nums[2] > 0;
    bool any_negative = nums[0] < 0 || nums[1] < 0 || nums[2] < 0;
    bool in_range = false;
    bool none_zero = nums[0] != 0 && nums[1] != 0 && nums[2] != 0;

    for (int num : nums)
    {
        if (num >= 1 && num <= 100)
        {
            in_range = true;
            break;
        }
    }

    cout << "1. Все числа положительные: " << (all_positive ? "да" : "нет") << endl;
    cout << "2. Хотя бы одно число отрицательное: " << (any_negative ? "да" : "нет") << endl;
    cout << "3. Хотя бы одно число в диапазоне 1-100: " << (in_range ? "да" : "нет") << endl;
    cout << "4. Ни одно число не равно нулю: " << (none_zero ? "да" : "нет") << endl;
}

// Задание 25: Проверка чётности числа
void task25()
{
    cout << "\n=== Задание 25 ===" << endl;
    int num = getInput<int>("Введите целое число: ");
    cout << "Число " << num << " является " << (num % 2 == 0 ? "чётным" : "нечётным") << endl;
}

// Задание 26: Структура Student
void task26()
{
    cout << "\n=== Задание 26 ===" << endl;
    struct Student
    {
        string name;
        int age;
        double average_score;
    };

    Student s;
    cout << "Введите данные студента:\n";
    cout << "Имя: ";
    getline(cin, s.name);
    s.age = getInput<int>("Возраст: ");
    s.average_score = getInput<double>("Средний балл: ");

    cout << "\nИнформация о студенте:\n";
    cout << "Имя: " << s.name << "\nВозраст: " << s.age
         << "\nСредний балл: " << s.average_score << endl;
}

// Задание 27: Класс Task
void task27()
{
    cout << "\n=== Задание 27 ===" << endl;
    class Task
    {
        string title;
        string description;
        int priority;

    public:
        Task(string t, string d, int p) : title(t), description(d), priority(p) {}

        void setTitle(string t) { title = t; }
        string getDescription() { return description; }
        int getPriority() { return priority; }

        void printTaskDetails()
        {
            cout << "\nИнформация о задаче:\n";
            cout << "Заголовок: " << title << "\nОписание: " << description
                 << "\nПриоритет: " << priority << endl;
        }
    };

    string title, desc;
    int priority;

    cout << "Создание новой задачи:\n";
    cout << "Введите заголовок: ";
    getline(cin, title);
    cout << "Введите описание: ";
    getline(cin, desc);
    priority = getInput<int>("Введите приоритет (число): ");

    Task t(title, desc, priority);
    t.printTaskDetails();
}

// Класс Circle для задания 28
class Circle
{
    double radius;

public:
    Circle(double r) : radius(r) {}
    double getArea() { return M_PI * radius * radius; }
    double getCircumference() { return 2 * M_PI * radius; }
};

// Задание 28: Работа с классом Circle
void task28()
{
    cout << "\n=== Задание 28 ===" << endl;
    double radius = getInput<double>("Введите радиус круга: ");
    while (radius <= 0)
    {
        cout << "Радиус должен быть положительным!\n";
        radius = getInput<double>("Введите радиус круга: ");
    }

    Circle c(radius);
    cout << "\nХарактеристики круга:\n";
    cout << "Площадь: " << c.getArea() << endl;
    cout << "Длина окружности: " << c.getCircumference() << endl;
}

int main()
{
    cout << "Программа для выполнения заданий 23-28\n";
    task23();
    task24();
    task25();
    task26();
    task27();
    task28();

    cout << "\nВсе задания выполнены!\n";
    return 0;
}