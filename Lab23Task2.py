"""
TreeWork10. Дано бинарное дерево и корень дерева P1. Необходимо вставить в дерево
значение X.
"""

from dataclasses import dataclass
from typing import Optional, Set


@dataclass
class Node:
    value: int
    left: Optional["Node"] = None
    right: Optional["Node"] = None


def insert_bst(root: Optional[Node], x: int, used_values: Set[int]) -> Node:

    if x in used_values:
        raise ValueError(f"Значение {x} уже существует в дереве (дубликаты не допускаются)")
    if root is None:
        used_values.add(x)
        return Node(x)
    if x < root.value:
        root.left = insert_bst(root.left, x, used_values)
    elif x > root.value:
        root.right = insert_bst(root.right, x, used_values)
    return root


def post_order_traversal(root: Optional[Node]) -> None:

    if root is None:
        return
    post_order_traversal(root.left)
    post_order_traversal(root.right)
    print(root.value, end=" ")


def get_user_input() -> tuple[Optional[Node], int, Set[int]]:

    try:

        p1_str = input("Введите корень P1 (целое число): ").strip()
        if not p1_str:
            return None, 0, set()
        p1 = int(p1_str)

        used_values = {p1}
        root = Node(p1)

        values_str = input("Введите значения остальных узлов дерева (целые числа, разделённые пробелами, пустая строка для отсутствия узлов): ").strip()
        if values_str:
            values = [int(x) for x in values_str.split()]

            if any(v in used_values for v in values):
                raise ValueError("Значения узлов должны быть уникальными и отличаться от P1")

            for value in values:
                root = insert_bst(root, value, used_values)

        x_str = input("Введите значение X для вставки (целое число): ").strip()
        if not x_str:
            raise ValueError("Ввод для X не может быть пустым")
        x_value = int(x_str)
        return root, x_value, used_values
    except ValueError as e:
        raise ValueError(f"Некорректный ввод: {str(e)}") from e


def main() -> None:

    try:
        root, x_value, used_values = get_user_input()
        if not root:
            print("Дерево пусто")
            return
        root = insert_bst(root, x_value, used_values)
        if not root.left and not root.right:
            print("Дерево состоит только из корня")
            print("Концевой обход:", root.value)
            return
        print("Концевой обход после вставки:", end=" ")
        post_order_traversal(root)
        print()
    except ValueError as e:
        print(f"Ошибка: {e}")


if __name__ == "__main__":
    main()