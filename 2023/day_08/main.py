"""Day eight of Advent of Code 2023."""

from functools import reduce
from itertools import cycle
from math import gcd


def steps_to_z(
        cur: str, instructions: str, 
        map: dict[str, tuple[str, str]]) -> int:
    """Returns the number of steps it takes to get to something ending
    in Z from the given location.
    """
    
    for steps, n in enumerate(cycle(instructions)):
        if cur[-1] == 'Z':
            return steps
        cur = map[cur][0] if n == 'L' else map[cur][1]
   

if __name__ == "__main__":
    with open("input.txt") as fp:
        instructions = fp.readline()[:-1]
        fp.readline() # Ignore empty line.

        map = {l[:3]: (l[7:10], l[12:15]) for l in fp}

    # Finds every starting position ending in A and computes the time
    # that it takes to get to something ending in Z.
    starts = [s for s in map.keys() if s[-1] == 'A']
    steps = {s: steps_to_z(s, instructions, map) for s in starts}

    # It turns out that the paths are perfectly cyclic, so it takes the
    # same amount of steps to get to something ending in Z again.
    # Because of this, we can just find the LCM of the number of steps
    # in all of the paths. I took the algorithm for finding the LCM of
    # items in a list from ananay-mital on stack overflow. 
    lcm = reduce(
        lambda lcm, s: lcm*s // gcd(lcm, s),
        steps.values()
    )

    print("Part One:", steps["AAA"])
    print("Part Two:", lcm)
