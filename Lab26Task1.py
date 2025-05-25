"""
ЗАДАЧА: CalcTree1

В текстовом файле с именем filename дано арифметическое выражение в обратной польской записи.
Операндами являются целые числа из промежутка от 0 до 9. Используемые операции:
сложение (+), вычитание (-) и умножение (*).

1. Построить дерево, соответствующее данному выражению. Знаки операций кодируйте числами:
   сложение (-1), вычитание (-2), умножение (-3).
2. Преобразовать дерево так, чтобы в нем не было операций вычитания
   (замените поддеревья, в которых есть вычитание, значением данного поддерева).
3. Вывести указатель на корень полученного дерева.
"""

import os
from typing import Optional, Union


class Node:


    def __init__(
        self,
        value: Union[int, str],
        left: Optional["Node"] = None,
        right: Optional["Node"] = None,
    ) -> None:

        self.value = value
        self.left = left
        self.right = right

    def __repr__(self) -> str:
        return f"Node({self.value})"


def read_expression_from_file(filename: str) -> list[str]:
    """Считывает выражение из файла и возвращает список токенов.

    Args:
        filename (str): Путь к файлу с выражением.

    Returns:
        list[str]: Токены выражения.
    """
    if not os.path.isfile(filename):
        raise FileNotFoundError(f"Файл '{filename}' не найден.")

    with open(filename, "r", encoding="utf-8") as file:
        content = file.read().strip()

    if not content:
        raise ValueError("Файл пуст.")

    return content.split()


def build_expression_tree(tokens: list[str]) -> Node:
    """Построение дерева из постфиксного выражения.

    Args:
        tokens (list[str]): Список токенов выражения.

    Returns:
        Node: Корень дерева выражения.
    """
    stack: list[Node] = []
    operations = {"+": -1, "-": -2, "*": -3}

    for token in tokens:
        if token in operations:
            try:
                right = stack.pop()
                left = stack.pop()
            except IndexError:
                raise ValueError("Ошибка в структуре выражения: недостаточно операндов.")

            stack.append(Node(operations[token], left, right))
        elif token.isdigit():
            stack.append(Node(int(token)))
        else:
            raise ValueError(f"Недопустимый токен: {token}")

    if len(stack) != 1:
        raise ValueError("Ошибка: выражение содержит лишние элементы.")

    return stack[0]


def evaluate_node(node: Node) -> int:
    """Вычисляет значение поддерева.

    Args:
        node (Node): Узел дерева.

    Returns:
        int: Результат вычисления.
    """
    if node.left is None and node.right is None:
        return int(node.value)

    left_val = evaluate_node(node.left)
    right_val = evaluate_node(node.right)

    if node.value == -1:
        return left_val + right_val
    if node.value == -2:
        return left_val - right_val
    if node.value == -3:
        return left_val * right_val

    raise ValueError("Недопустимая операция.")


def simplify_subtractions(node: Optional[Node]) -> Optional[Node]:
    """Упрощает дерево: заменяет вычитание на числовое значение.

    Args:
        node (Optional[Node]): Узел дерева.

    Returns:
        Optional[Node]: Упрощённое поддерево.
    """
    if node is None:
        return None

    node.left = simplify_subtractions(node.left)
    node.right = simplify_subtractions(node.right)

    if node.value == -2:
        return Node(evaluate_node(node))

    return node


def print_tree(node: Optional[Node], indent: str = "") -> None:
    """Выводит дерево на экран в читаемом виде.

    Args:
        node (Optional[Node]): Узел дерева.
        indent (str): Отступ.
    """
    if node:
        print_tree(node.right, indent + "    ")
        print(f"{indent}{node.value}")
        print_tree(node.left, indent + "    ")


def main() -> None:
    """Запуск программы."""
    try:
        filename = "expression.txt"
        tokens = read_expression_from_file(filename)

        root = build_expression_tree(tokens)
        root = simplify_subtractions(root)

        print("\nУпрощённое дерево (вычитание заменено значениями):")
        print_tree(root)

        print(f"\nКорень дерева: {root}")

    except FileNotFoundError as e:
        print(e)
    except ValueError as e:
        print(f"Ошибка: {e}")
    except Exception as e:
        print(f"Непредвиденная ошибка: {e}")


if __name__ == "__main__":
    main()
