"""Day six of Advent of Code 2023."""

from math import sqrt, floor, ceil


def get_num_ways(time: int, dist: int) -> int:
    """Uses the quadratic formula to get the min and max time needed to
    beat the given distance, then returns the number of times possible.
    """
    
    min_t = floor(((time - sqrt(time**2 - 4*dist)) / 2) + 1)
    max_t = ceil(((time + sqrt(time**2 - 4*dist)) / 2) - 1)
    
    return max_t - min_t + 1

def part_one(times: list[int], distances: list[int]) -> int:
    """Finds the number of ways each game can be beat and returns the
    product.
    """

    margin = 1

    for time, dist in list(zip(times, distances)):
        margin *= get_num_ways(time, dist)
    
    return margin

def part_two(times: list[int], distances: list[int]) -> int:
    """Finds the number of ways the one game can be won."""
    
    time = int("".join([str(n) for n in times]))
    dist = int("".join([str(n) for n in distances]))
    
    return get_num_ways(time, dist)


if __name__ == "__main__":
    with open("input.txt") as fp:
        times, distances = [
            [int(n) for n in line[:-1].split(":")[1].split(" ") if n.isnumeric()]
            for line in fp
        ]

    print("Part One:", part_one(times, distances))
    print("Part Two:", part_two(times, distances))
