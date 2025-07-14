#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include <limits>
#include <climits>
#include <iomanip>

using namespace std;

int safeInputInt(const string &prompt, int minVal = INT_MIN, int maxVal = INT_MAX)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (!(cin >> value))
        {
            cout << "Ошибка! Введите целое число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (cin.peek() != '\n')
        {
            cout << "Ошибка! Введены лишние символы. Пожалуйста, введите одно число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (value < minVal || value > maxVal)
        {
            cout << "Ошибка! Число должно быть от " << minVal << " до " << maxVal << ".\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

string safeInputString(const string &prompt, bool allowSpecialChars = true)
{
    string input;
    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty())
        {
            cout << "Ошибка! Ввод не может быть пустым.\n";
            continue;
        }

        if (!allowSpecialChars)
        {
            bool invalidChar = false;
            for (char c : input)
            {
                if (!isalnum(c) && !isspace(c))
                {
                    invalidChar = true;
                    break;
                }
            }
            if (invalidChar)
            {
                cout << "Ошибка! Строка содержит недопустимые символы.\n";
                continue;
            }
        }

        return input;
    }
}

// ================== ФУНКЦИИ ВЫВОДА МАТРИЦ ==================

void printMatrix(const vector<vector<int>> &matrix)
{
    cout << "\nТекущая матрица:\n";
    for (const auto &row : matrix)
    {
        for (int num : row)
        {
            cout << setw(5) << num << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// ================== ОСНОВНЫЕ ФУНКЦИИ ==================

void checkPalindrome()
{
    string input = safeInputString("Введите строку для проверки: ");

    bool isPalindrome = true;
    int left = 0;
    int right = input.length() - 1;

    while (left < right)
    {
        while (left < right && !isalnum(input[left]))
            left++;
        while (left < right && !isalnum(input[right]))
            right--;

        if (tolower(input[left]) != tolower(input[right]))
        {
            isPalindrome = false;
            break;
        }
        left++;
        right--;
    }

    cout << "Результат: " << (isPalindrome ? "Это палиндром!" : "Это не палиндром.") << endl;
}

void removeCharsFromString()
{
    string input = safeInputString("Введите исходную строку: ");
    string charsToRemove = safeInputString("Введите символы для удаления: ");

    string result;
    for (char c : input)
    {
        if (charsToRemove.find(c) == string::npos)
        {
            result += c;
        }
    }

    cout << "Результат: " << (result.empty() ? "(пустая строка)" : result) << endl;
}

void countCharFrequency()
{
    string input = safeInputString("Введите строку для анализа: ");

    map<char, int> frequency;
    for (char c : input)
    {
        frequency[c]++;
    }

    cout << "Частота символов:" << endl;
    for (const auto &pair : frequency)
    {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }
}

void mergeSortedArrays()
{
    int size1 = safeInputInt("Введите размер первого массива (1-100): ", 1, 100);
    vector<int> arr1;
    cout << "Введите " << size1 << " чисел первого массива в порядке возрастания:" << endl;

    for (int i = 0; i < size1;)
    {
        cout << "Элемент " << (i + 1) << ": ";
        int num = safeInputInt("", INT_MIN, INT_MAX);

        if (!arr1.empty() && num < arr1.back())
        {
            cout << "Ошибка! Массив должен быть отсортирован по возрастанию.\n";
            cout << "Предыдущее значение: " << arr1.back() << endl;
            continue;
        }

        arr1.push_back(num);
        i++;
    }

    int size2 = safeInputInt("Введите размер второго массива (1-100): ", 1, 100);
    vector<int> arr2;
    cout << "Введите " << size2 << " чисел второго массива в порядке возрастания:" << endl;

    for (int i = 0; i < size2;)
    {
        cout << "Элемент " << (i + 1) << ": ";
        int num = safeInputInt("", INT_MIN, INT_MAX);

        if (!arr2.empty() && num < arr2.back())
        {
            cout << "Ошибка! Массив должен быть отсортирован по возрастанию.\n";
            cout << "Предыдущее значение: " << arr2.back() << endl;
            continue;
        }

        arr2.push_back(num);
        i++;
    }

    vector<int> merged;
    merged.reserve(size1 + size2);
    merge(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), back_inserter(merged));

    cout << "Объединенный массив: ";
    for (int num : merged)
    {
        cout << num << " ";
    }
    cout << endl;
}

void rotateMatrix90()
{
    int size = safeInputInt("Введите размер квадратной матрицы (2-10): ", 2, 10);
    vector<vector<int>> matrix(size, vector<int>(size));

    cout << "Введите матрицу " << size << "x" << size << ":" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            string prompt = "Элемент [" + to_string(i + 1) + "][" + to_string(j + 1) + "]: ";
            matrix[i][j] = safeInputInt(prompt, INT_MIN, INT_MAX);
        }
    }

    printMatrix(matrix); // Вывод исходной матрицы

    vector<vector<int>> rotated(size, vector<int>(size));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            rotated[j][size - 1 - i] = matrix[i][j];
        }
    }

    cout << "Повернутая матрица:" << endl;
    printMatrix(rotated); // Вывод повернутой матрицы
}

void searchInSortedMatrix()
{
    int rows = safeInputInt("Введите количество строк (1-10): ", 1, 10);
    int cols = safeInputInt("Введите количество столбцов (1-10): ", 1, 10);
    vector<vector<int>> matrix(rows, vector<int>(cols));

    cout << "Введите отсортированную матрицу (по строкам и столбцам):" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            string prompt = "Элемент [" + to_string(i + 1) + "][" + to_string(j + 1) + "]: ";

            while (true)
            {
                matrix[i][j] = safeInputInt(prompt, INT_MIN, INT_MAX);

                if (j > 0 && matrix[i][j] < matrix[i][j - 1])
                {
                    cout << "Ошибка! Строка должна быть отсортирована по возрастанию.\n";
                    cout << "Предыдущее значение: " << matrix[i][j - 1] << endl;
                    continue;
                }

                if (i > 0 && matrix[i][j] < matrix[i - 1][j])
                {
                    cout << "Ошибка! Столбец должен быть отсортирован по возрастанию.\n";
                    cout << "Предыдущее значение: " << matrix[i - 1][j] << endl;
                    continue;
                }
                break;
            }
        }
    }

    printMatrix(matrix); // Вывод введенной матрицы

    int target = safeInputInt("Введите элемент для поиска: ", INT_MIN, INT_MAX);

    int row = 0;
    int col = cols - 1;
    bool found = false;

    while (row < rows && col >= 0)
    {
        if (matrix[row][col] == target)
        {
            found = true;
            break;
        }
        matrix[row][col] > target ? col-- : row++;
    }

    if (found)
    {
        cout << "Элемент найден в строке " << (row + 1)
             << ", столбце " << (col + 1) << endl;
    }
    else
    {
        cout << "Элемент не найден в матрице." << endl;
    }
}

// ================== ГЛАВНОЕ МЕНЮ ==================

void showMenu()
{
    cout << "\n=== Меню программы ===" << endl;
    cout << "1. Проверка строки на палиндром" << endl;
    cout << "2. Удаление символов из строки" << endl;
    cout << "3. Подсчет частоты символов" << endl;
    cout << "4. Объединение отсортированных массивов" << endl;
    cout << "5. Поворот матрицы на 90 градусов" << endl;
    cout << "6. Поиск в отсортированной матрице" << endl;
    cout << "0. Выход" << endl;
}

int main()
{
    int choice;

    do
    {
        showMenu();
        choice = safeInputInt("Выберите задание (0-6): ", 0, 6);

        switch (choice)
        {
        case 1:
            checkPalindrome();
            break;
        case 2:
            removeCharsFromString();
            break;
        case 3:
            countCharFrequency();
            break;
        case 4:
            mergeSortedArrays();
            break;
        case 5:
            rotateMatrix90();
            break;
        case 6:
            searchInSortedMatrix();
            break;
        case 0:
            cout << "Программа завершена." << endl;
            break;
        }

    } while (choice != 0);

    return 0;
}