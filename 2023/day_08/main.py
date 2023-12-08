"""Day eight of Advent of Code 2023."""

from functools import reduce
from itertools import cycle
from math import gcd


Map = dict[str, tuple[str, str]]


def steps_to_z(cur: str, instructions: str, map: Map) -> int:
    """Returns the number of steps it takes to get to something ending
    in Z from the given start location.
    """
    
    for steps, n in enumerate(cycle(instructions)):
        if cur[-1] == 'Z':
            return steps
        cur = map[cur][0] if n == 'L' else map[cur][1]

def part_one(instructions: str, map: Map) -> int:
    """Returns the steps to get to something ending with Z from AAA. It
    just so happens to be ZZZ. Huh.
    """
    
    return steps_to_z("AAA", instructions, map)
   
def part_two(instructions: str, map: Map) -> int:
    """Finds every starting position ending in A and computes the time
    that it takes to get to something ending in Z. It turns out that
    its perfectly cyclic, so the next time it gets to something ending
    in Z takes the same number of steps. I determined this through code
    not shown here. Because of this, we can just find the LCM of these
    different numbers, and that's our answer.
    """

    starts = [s for s in map.keys() if s[-1] == "A"]
    steps = [steps_to_z(s, instructions, map) for s in starts]

    # Stole this from ananay-mital on stack overflow. 
    return reduce(
        lambda lcm, s: lcm*s // gcd(lcm, s),
        steps
    )


if __name__ == "__main__":
    with open("input.txt") as fp:
        instructions = fp.readline()[:-1]
        fp.readline() # Ignore empty line.

        map = {l[:3]: (l[7:10], l[12:15]) for l in fp}


    print("Part One:", part_one(instructions, map))
    print("Part Two:", part_two(instructions, map))
