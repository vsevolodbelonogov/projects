#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

// Задание 1: Функция для вычисления квадрата числа через указатель
double square(double *num)
{
    return (*num) * (*num);
}

// Задание 2: Программа с массивом и меню
void arrayMenuProgram()
{
    int arr[10];
    int choice;

    std::cout << "\nМеню заполнения массива:\n";
    std::cout << "1. Вручную\n";
    std::cout << "2. Рандомно\n";
    std::cout << "3. С шагом k (+, -, *)\n";
    std::cout << "Выберите вариант: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
    {
        std::cout << "Введите 10 чисел:\n";
        for (int i = 0; i < 10; ++i)
        {
            std::cin >> arr[i];
        }
        break;
    }
    case 2:
    {
        srand(time(0));
        for (int i = 0; i < 10; ++i)
        {
            arr[i] = rand() % 100; // случайные числа от 0 до 99
        }
        break;
    }
    case 3:
    {
        int first, k;
        char op;
        std::cout << "Введите первый элемент: ";
        std::cin >> first;
        std::cout << "Введите шаг k: ";
        std::cin >> k;
        std::cout << "Выберите операцию (+, -, *): ";
        std::cin >> op;

        arr[0] = first;
        for (int i = 1; i < 10; ++i)
        {
            switch (op)
            {
            case '+':
                arr[i] = arr[i - 1] + k;
                break;
            case '-':
                arr[i] = arr[i - 1] - k;
                break;
            case '*':
                arr[i] = arr[i - 1] * k;
                break;
            default:
                std::cout << "Неверная операция. Используется '+' по умолчанию.\n";
                arr[i] = arr[i - 1] + k;
            }
        }
        break;
    }
    default:
        std::cout << "Неверный выбор. Массив будет заполнен нулями.\n";
        for (int i = 0; i < 10; ++i)
        {
            arr[i] = 0;
        }
    }

    // Находим минимальный и максимальный элементы
    int min = arr[0], max = arr[0];
    for (int i = 1; i < 10; ++i)
    {
        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
    }

    std::cout << "Массив: ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << "\nМинимальный элемент: " << min << "\n";
    std::cout << "Максимальный элемент: " << max << "\n";
}

// Задание 3: Программа с двумя массивами и операциями
void arrayOperationsProgram()
{
    int arr1[10], arr2[10];

    std::cout << "\nВведите 10 чисел для первого массива:\n";
    for (int i = 0; i < 10; ++i)
    {
        std::cin >> arr1[i];
    }

    std::cout << "Введите 10 чисел для второго массива:\n";
    for (int i = 0; i < 10; ++i)
    {
        std::cin >> arr2[i];
    }

    // Вычисляем сумму и разность
    int sum[10], diff[10];
    for (int i = 0; i < 10; ++i)
    {
        sum[i] = arr1[i] + arr2[i];
        diff[i] = arr1[i] - arr2[i];
    }

    std::cout << "Сумма массивов: ";
    for (int i = 0; i < 10; ++i)
    {
        std::cout << sum[i] << " ";
    }

    std::cout << "\nРазность массивов: ";
    for (int i = 0; i < 10; ++i)
    {
        std::cout << diff[i] << " ";
    }
    std::cout << "\n";
}

int main()
{
    // Задание 1
    double num;
    std::cout << "Введите число (для задания 1): ";
    std::cin >> num;
    double result = square(&num);
    std::cout << "Квадрат числа: " << result << "\n";

    // Задание 2
    arrayMenuProgram();

    // Задание 3
    arrayOperationsProgram();

    return 0;
}