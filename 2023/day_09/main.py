"""Day nine of Advent of Code 2023."""

from functools import reduce
from numpy import diff


def get_prediction(l: list[int], get_next=True):
    """First creates the list of diffs until it gets to the list with
    all 0s. Then accumulates either the sums of the last elements or the 
    differences of the previous elements in order to predict a value.
    """
    
    lists = [l.copy()]
    while not all(e == 0 for e in lists[-1]):
        lists.append(list(diff(lists[-1])))
 
    return reduce(
        lambda n, l: l[-1 if get_next else 0] + (n if get_next else -n),
        reversed(lists[:-1]),
        0
    )

def analyze_report(lists: list[int], get_next=True):
    """Analyze the report by finding the predicted previous or next
    values, then returning their sum.
    """

    predictions = [get_prediction(l, get_next) for l in lists]
    return sum(predictions)


if __name__ == "__main__":
    with open("input.txt") as fp:
        lists = [
            [int(n) for n in line.split() if n.lstrip('-').isnumeric()]
            for line in fp
        ]

    print("Part One:", analyze_report(lists))
    print("Part Two:", analyze_report(lists, False))
