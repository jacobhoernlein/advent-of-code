"""Day four of Advent of Code 2023. I completed part two using 2
different methods: recursion and dynamic programming. My first instinct
was to use DP, but I was curious to see if recursion would work too.
It does, but DP is much, much faster.
"""

from time import perf_counter_ns


def get_num_won(lines: list[str]) -> list[int]:
    """Returns a list that contains the number of winning numbers for
    each card.
    """

    num_won = []
    for line in lines:
        # Create lists of winning numbers and my nums.
        winning_nums, my_nums = line.split(":")[1].split("|")
        winning_nums = [int(w) for w in winning_nums.split(" ") if w]
        my_nums = [int(n) for n in my_nums.split(" ") if n]

        # Cound the winning numbers for the current line and append.
        num_won.append(len([n for n in my_nums if n in winning_nums]))
    
    return num_won
        
def part_one(lines: list[str]) -> int:
    """Computes the sum of the points won for each card."""
    
    return sum([2**(n - 1) for n in get_num_won(lines) if n > 0])

def part_two(lines: list[str]) -> int:
    """Uses dynamic programming (bottom up) to compute the number of
    cards that each card spawns, then sums those all together.
    """
    
    cards_spawned = [0] * len(lines)

    # We need to start at the bottom and work up or the function will
    # take literally forever. Shoutout to Dr. Dixon.
    iter = reversed(list(enumerate(get_num_won(lines))))
    for card_num, num_won in iter:
        num_spawned = 0

        i = 1
        while i <= num_won:
            # Total number spawned for each card is equal to the number
            # of cards directly spawned, and the number of cards each
            # of those spawn.
            num_spawned += 1 + cards_spawned[card_num + i]
            i += 1

        cards_spawned[card_num] = num_spawned

    return len(lines) + sum(cards_spawned)
            
def get_cards_spawned(num_won: list[int], i: int):
    """Recursive function to get the total number of cards spawned by
    each card.
    """
    
    num_spawned = 0
    if num_won[i] > 0:
        j = 1
        while j <= num_won[i]:
            num_spawned += 1 + get_cards_spawned(num_won, i + j)
            j += 1
    return num_spawned

def part_two_dumb(lines: list[str]) -> int:
    """Does part two the dumb way (recursively) to see if it ever
    finishes. Turns out it does. But the DP method is like 400x faster.
    """

    total = 0
    num_won = get_num_won(lines)
    for card_num in range(len(lines)):
        total += 1 + get_cards_spawned(num_won, card_num)

    return total

def main():
    with open("input.txt") as fp:
        lines = [line[:-1] for line in fp]

    print("Part One:", part_one(lines))

    start = perf_counter_ns()
    dp = part_two(lines)
    time_dp = perf_counter_ns() - start

    start = perf_counter_ns()
    dumb = part_two_dumb(lines)
    time_dumb = perf_counter_ns() - start

    assert dp == dumb
    speedup = time_dumb / time_dp

    print(f"Part Two: {dp} (DP was {speedup:.1f} times faster)")


if __name__ == "__main__":
    main()
