"""Day six of Advent of Code 2023."""

from math import sqrt, floor, ceil


def get_margin(time, dist) -> tuple[int, int]:
    """Uses the quadratic formula to get the min and max time needed to
    beat the given distance, then returns the number of times possible.
    """
    
    min_t = floor(((time - sqrt(time**2 - 4*dist)) / 2) + 1)
    max_t = ceil(((time + sqrt(time**2 - 4*dist)) / 2) - 1)
    return max_t - min_t + 1

def part_one(times: list[int], distances: list[int]) -> int:
    """Finds the margin for each game and returns the product."""

    margin = 1
    for time, dist in list(zip(times, distances)):
        margin *= get_margin(time, dist)
    return margin

def part_two(times: list[int], distances: list[int]) -> int:
    """Finds the margin of one game."""
    
    time = int("".join([str(n) for n in times]))
    dist = int("".join([str(n) for n in distances]))
    
    return get_margin(time, dist)


if __name__ == "__main__":
    with open("input.txt") as fp:
        lines = [line[:-1] for line in fp]

    times, distances = [
        [int(n) for n in l.split(":")[1].split(" ") if n.isnumeric()]
        for l in lines
    ]

    print("Part One:", part_one(times, distances))
    print("Part Two:", part_two(times, distances))
