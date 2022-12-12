from dataclasses import dataclass
from typing import Callable

# i may have cheated

@dataclass
class Monkey:

    items: list[int]
    operation: Callable[[int], int]
    test_divisor: int
    true_index: int
    false_index: int
    items_looked_at: int = 0

    def __lt__(self, other: "Monkey"):
        return self.items_looked_at < other.items_looked_at


def sim_monkeys(monkeys: list[Monkey]):
    for monkey in monkeys:
        while monkey.items:
            item = monkey.items.pop(0)
            item = monkey.operation(item) % 9699690
            if item % monkey.test_divisor == 0:
                monkeys[monkey.true_index].items.append(item)
            else:
                monkeys[monkey.false_index].items.append(item)
            monkey.items_looked_at += 1
    

if __name__ == "__main__":
    monkeys = [
        Monkey([52, 60, 85, 69, 75, 75], lambda old: old * 17, 13, 6, 7),
        Monkey([96, 82, 61, 99, 82, 84, 85], lambda old: old + 8, 7, 0, 7),
        Monkey([95, 79], lambda old: old + 6, 19, 5, 3),
        Monkey([88, 50, 82, 65, 77], lambda old: old * 19, 2, 4, 1),
        Monkey([66, 90, 59, 90, 87, 63, 53, 88], lambda old: old + 7, 5, 1, 0),
        Monkey([92, 75, 62], lambda old: old * old, 3, 3, 4),
        Monkey([94, 86, 76, 67], lambda old: old + 1, 11, 5, 2),
        Monkey([57], lambda old: old + 2, 17, 6, 2)
    ]

    for i in range(10000):
        sim_monkeys(monkeys)

    monkeys.sort()
    print(monkeys[-1].items_looked_at * monkeys[-2].items_looked_at)
