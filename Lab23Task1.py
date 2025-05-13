"""
TreeWork1. Дано бинарное дерево и корень дерева P1. Необходимо вывести содержимое
информационных полей дерева, используя концевой обход (снизу-вверх). Сначала
выводится левое поддерево, потом правое поддерево, потом значение информационного
поля текущей вершины. При выводе левого и правого поддерева так же используется
концевой обход.
"""

from dataclasses import dataclass
from typing import Optional, Set


@dataclass
class Node:
    value: int
    left: Optional["Node"] = None
    right: Optional["Node"] = None


def post_order_traversal(root: Optional[Node]) -> None:

    if root is None:
        return
    post_order_traversal(root.left)
    post_order_traversal(root.right)
    print(root.value, end=" ")


def create_node(value: int) -> Node:

    return Node(value)


def parse_yes_no_input(input_str: str) -> bool:

    input_str = input_str.strip().lower()
    if not input_str:
        raise ValueError("Ввод не может быть пустым")
    if input_str in ("да", "нет"):
        return input_str == "да"
    raise ValueError("Введите 'да' или 'нет'")


def get_node_input(
    parent_value: int,
    position: str,
    min_val: Optional[int],
    max_val: Optional[int],
    used_values: Set[int]
) -> Optional[Node]:

    try:
        has_node = parse_yes_no_input(
            input(f"Есть ли {position} у узла {parent_value}? (да/нет): ")
        )
        if not has_node:
            return None
        prompt = f"Введите значение {position} (целое число"
        if min_val is not None:
            prompt += f", больше {min_val}"
        if max_val is not None:
            prompt += f", меньше {max_val}"
        prompt += "): "
        value_str = input(prompt).strip()
        if not value_str:
            raise ValueError("Ввод не может быть пустым")
        value = int(value_str)
        if value in used_values:
            raise ValueError(f"Значение {value} уже использовано (дубликаты не допускаются)")
        if min_val is not None and value <= min_val:
            raise ValueError(f"Значение должно быть больше {min_val}")
        if max_val is not None and value >= max_val:
            raise ValueError(f"Значение должно быть меньше {max_val}")
        used_values.add(value)
        node = create_node(value)
        node.left = get_node_input(value, "левое поддерево", min_val, value, used_values)
        node.right = get_node_input(value, "правое поддерево", value, max_val, used_values)
        return node
    except ValueError as e:
        raise ValueError(f"Некорректный ввод для {position}: {str(e)}") from e


def get_user_input() -> Optional[Node]:

    try:
        p1_str = input("Введите значение корня P1 (целое число): ").strip()
        if not p1_str:
            raise ValueError("Ввод не может быть пустым")
        p1_value = int(p1_str)
        root = create_node(p1_value)
        used_values = {p1_value}
        root.left = get_node_input(p1_value, "левое поддерево", None, p1_value, used_values)
        root.right = get_node_input(p1_value, "правое поддерево", p1_value, None, used_values)
        return root
    except ValueError as e:
        raise ValueError(f"Некорректный ввод: {str(e)}") from e


def main() -> None:

    try:
        root = get_user_input()
        if not root:
            print("Дерево пусто")
            return
        if not root.left and not root.right:
            print("Дерево состоит только из корня")
            print("Концевой обход:", root.value)
            return
        print("Концевой обход:", end=" ")
        post_order_traversal(root)
        print()
    except ValueError as e:
        print(f"Ошибка: {e}")


if __name__ == "__main__":
    main()