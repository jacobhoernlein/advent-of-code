"""Day nine of Advent of Code 2023."""

from functools import reduce
from numpy import diff


def get_predictions(l: list[int]):
    """First creates the list of diffs until it gets to the list with
    all 0s. Then accumulates either the sums of the last elements or the 
    differences of the previous elements in order to predict a value.
    """
    
    lists = [l.copy()]
    while not all(e == 0 for e in lists[-1]):
        lists.append(list(diff(lists[-1])))
    lists.reverse()

    p = reduce(lambda n, l: l[0] - n, lists, 0)
    n = reduce(lambda n, l: l[-1] + n, lists, 0)
    
    return p, n


if __name__ == "__main__":
    with open("input.txt") as fp:
        lists = [
            [int(n) for n in line.split() if n.lstrip('-').isnumeric()]
            for line in fp
        ]
        
    predictions = [get_predictions(l) for l in lists]
    prevs, nexts = zip(*predictions)

    print("Part One:", sum(nexts))
    print("Part Two:", sum(prevs))
