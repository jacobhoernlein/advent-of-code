"""Day six of Advent of Code 2023."""

from math import sqrt, floor, ceil


def get_num_ways(time: int, dist: int) -> int:
    """Uses the quadratic formula to get the min and max time needed to
    beat the given distance, then returns the range of those times.

    Based on the fact that the equation for distance traveled is
        d = t(T-t)
    Where T is the length of the race and t is the time spent winding
    the boat. 
    
    Thus, the times t for which the boat travels the record distance D
    can be found by using the quadratic formula on the following:
        t^2 - Tt + D = 0
    """
    
    try:
        sqrt_disc = sqrt(time**2 - 4*dist)
    except ValueError:  # Not enough time for given distance.
        return 0

    # We use floor/ceil and add/subtract one because we need the next
    # largest/smallest integer for the given solution of t.
    min_t = floor((time - sqrt_disc)/2 + 1)
    max_t = ceil((time + sqrt_disc)/2 - 1)
    
    return max_t - min_t + 1 if max_t >= min_t else 0

def part_one(times: list[int], distances: list[int]) -> int:
    """Finds the number of ways each game can be beat and returns the
    product.
    """

    margin = 1
    for time, dist in zip(times, distances):
        margin *= get_num_ways(time, dist)
    
    return margin

def part_two(times: list[int], distances: list[int]) -> int:
    """Finds the number of ways the one game can be won."""
    
    # Quick function that concatenates integers in a list.
    merge = lambda it: int("".join([str(n) for n in it]))
    
    return get_num_ways(merge(times), merge(distances))


if __name__ == "__main__":    
    with open("input.txt") as fp:
        times, distances = [
            # Ugly list comprehension, but all it does is parse input.
            [int(n) for n in line[:-1].split(":")[1].split(" ") if n]
            for line in fp
        ]

    print("Part One:", part_one(times, distances))
    print("Part Two:", part_two(times, distances))
