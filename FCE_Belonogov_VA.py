"""Реализует структуру данных 'очередь' с указанными методами.

Программа позволяет создавать очередь, добавлять элементы (push), удалять первый элемент (pop),
просматривать первый элемент (front), проверять размер (size), очищать очередь (clear) и завершать работу (exit).
Обеспечивает обработку ошибок при некорректном вводе.

Пример 1:
push 1
ok
front
1
exit
bye

Пример 2:
size
0
push 1
ok
size
1
push 2
ok
size
2
push 3
ok
size
3
exit
bye
"""


class Queue:
    """Класс для реализации очереди.

        Атрибуты:
            _items (list): Приватный список для хранения элементов очереди.
        """
    def __init__(self) -> None:
        """Инициализирует пустую очередь."""
        self._items = []

    def push(self, item: str) -> None:
        """Добавляет элемент в конец очереди.

        Args:
            item (str): Элемент для добавления (должен быть строкой, содержащей только цифры,
                       не длиннее 100 символов и не командой).

        Raises:
            ValueError: Если элемент не является цифрами, пустой, слишком длинный или является командой.
        """
        commands = {"push", "pop", "front", "size", "clear", "exit"}
        if not item or len(item) > 100:
            raise ValueError("Элемент пустой или слишком длинный (максимум 100 символов)")
        if item.lower() in commands:
            raise ValueError(f"Нельзя использовать команду '{item}' как элемент")
        if not item.isdigit():
            raise ValueError("Элемент должен содержать только цифры")
        self._items.append(item)

    def pop(self) -> str:
        """Удаляет и возвращает первый элемент очереди.

                Returns:
                    str: Первый элемент очереди.

                Raises:
                    IndexError: Если очередь пуста.
                """
        if not self._items:
            raise IndexError("error")
        return self._items.pop(0)

    def front(self) -> str:
        """Возвращает первый элемент очереди без удаления.

               Returns:
                   str: Первый элемент очереди.

               Raises:
                   IndexError: Если очередь пуста.
               """
        if not self._items:
            raise IndexError("error")
        return self._items[0]

    def size(self) -> int:
        """Возвращает количество элементов в очереди.

                Returns:
                    int: Количество элементов.
                """
        return len(self._items)

    def clear(self) -> None:

        self._items.clear()


def process_command(queue: Queue, command: str) -> None:
    """Обрабатывает введенную команду.

        Args:
            queue (Queue): Экземпляр очереди.
            command (str): Введенная команда.

        Raises:
            ValueError: Если команда некорректна.
        """
    def validate_command() -> tuple[str, list]:
        """Валидирует введенную команду и разбивает ее на части.

                Returns:
                    tuple[str, list]: Корректированная команда и ее части.

                Raises:
                    ValueError: Если команда пустая.
                """
        cmd = command.strip()
        if not cmd:
            raise ValueError("Ошибка: Введите команду")
        return cmd, cmd.split()

    def execute_action(action: str, parts: list) -> None:
        """Выполняет действие в зависимости от команды.

                Args:
                    action (str): Название команды.
                    parts (list): Разделенные части команды.
                """
        if action == "push":
            if len(parts) < 2:
                raise ValueError("Отсутствует значение для push")
            queue.push(parts[1])
            print("ok")
        elif action == "pop":
            print(queue.pop())
        elif action == "front":
            print(queue.front())
        elif action == "size":
            print(queue.size())
        elif action == "clear":
            queue.clear()
            print("ok")
        elif action == "exit":
            print("bye")
            exit(0)
        else:
            raise ValueError(f"Неизвестная команда: {action}")

    try:
        cmd, parts = validate_command()
        action = parts[0].lower()
        execute_action(action, parts)
    except IndexError as e:
        print(str(e))
    except ValueError as e:
        print(f"Ошибка: {e}")


def main() -> None:
    """Запускает интерактивный цикл обработки команд."""
    queue = Queue()

    def display_instructions() -> None:
        """Выводит инструкции для пользователя."""
        print("Добро пожаловать! Доступные команды:")
        print("  push <значение>   (добавить элемент)")
        print("  pop              (удалить первый элемент)")
        print("  front            (просмотреть первый элемент)")
        print("  size             (показать количество элементов)")
        print("  clear            (очистить очередь)")
        print("  exit             (завершить работу)")

    def get_user_input() -> str:
        """Получает ввод от пользователя."""
        return input("Введите следующую команду: ")

    display_instructions()
    while True:
        command = get_user_input()
        process_command(queue, command)


if __name__ == "__main__":
    main()
