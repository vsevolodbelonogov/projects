"""Преобразовать бинарное дерево поиска в двусвязный список без использования дополнительной памяти."""

from typing import Optional, Tuple

class TreeNode:
    def __init__(self, val: int):
        self.val = val
        self.left: Optional['TreeNode'] = None
        self.right: Optional['TreeNode'] = None

def print_tree(root: Optional[TreeNode]) -> None:
    if root:
        print_tree(root.left)
        print(root.val, end=' ')
        print_tree(root.right)

def print_list(list_head: Optional[TreeNode]) -> None:
    while list_head:
        print(list_head.val, end=' ')
        list_head = list_head.right

def tree_to_doubly_list(tree_root: Optional[TreeNode]) -> Optional[TreeNode]:
    def _convert(current_node: TreeNode) -> Tuple[TreeNode, TreeNode]:
        l_head = r_tail = current_node
        if current_node.left:
            l_head, l_tail = _convert(current_node.left)
            l_tail.right = current_node
            current_node.left = l_tail
        if current_node.right:
            r_head, r_tail = _convert(current_node.right)
            current_node.right = r_head
            r_head.left = current_node
        return l_head, r_tail
    return _convert(tree_root)[0] if tree_root else None

def get_root_value() -> int:
    while True:
        try:
            val = int(input("Введите значение корня дерева: "))
            return val
        except ValueError:
            print("Ошибка: введите целое число")

def get_next_values(root_val: int) -> list[int]:
    values = []
    while True:
        try:
            input_str = input("Введите следующие значения через пробел (или Enter для завершения): ").strip()
            if not input_str:
                break

            nums = [int(n) for n in input_str.split()]
            for num in nums:
                if num == root_val:
                    print(f"Ошибка: значение {num} равно корню. Игнорируем.")
                else:
                    values.append(num)
            return values
        except ValueError:
            print("Ошибка: вводите только целые числа")

def build_tree(root_val: int, other_values: list[int]) -> TreeNode:
    root = TreeNode(root_val)
    for num in other_values:
        current = root
        while True:
            if num < current.val:
                if current.left:
                    current = current.left
                else:
                    current.left = TreeNode(num)
                    break
            elif num > current.val:
                if current.right:
                    current = current.right
                else:
                    current.right = TreeNode(num)
                    break
            else:
                print(f"Значение {num} уже существует в дереве. Игнорируем.")
                break
    return root

if __name__ == "__main__":
    print("Построение BST:")
    root_val = get_root_value()
    other_values = get_next_values(root_val)

    bst = build_tree(root_val, other_values)

    print("\nИсходное дерево:")
    print_tree(bst)

    list_head = tree_to_doubly_list(bst)
    print("\n\nРезультат преобразования:")
    print_list(list_head)