"""Day seven of Advent of Code 2023."""

from functools import reduce


class Hand:
    """Class representing a hand of Camel Poker cards. Constructed with
    a string representing the cards, and a boolean representing whether
    or not jokers should be treated as wild. Supports comparison
    between instances."""

    __card_strengths = {
        "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8,
        "9": 9, "T": 10, "J": 11, "Q": 12, "K": 13, "A": 14
    }

    def __init__(self, s: str, wild=False):
        self.type = Hand.__get_type(s, wild)

        # Updates the strength of a joker if the hand is wild or not,
        # then translates each character in the string to an integer
        # value representing its relative weight.
        Hand.__card_strengths["J"] = 1 if wild else 11
        self.__card_strengths = [Hand.__card_strengths[c] for c in s]

    def __lt__(self, other: "Hand"):
        """Compares hands first based on their type, then on individual
        cards.
        """

        if self.type != other.type:
            return self.type < other.type
        
        for a, b in zip(self.__card_strengths, other.__card_strengths):
            if a != b:
                return a < b
        
        return False
    
    @staticmethod
    def __get_type(s: str, wild=False) -> int | float:
        """Returns the strength of the hand's type as a number, based on if
        it's wild or not, in a range from 1 (high card) to 5 (five of a kind).
        """
        
        # Counts cards in the hand.
        card_count = {c: 0 for c in s}
        for c in s:
            card_count[c] += 1

        # Returns a list with the largest number of cards first, then
        # the next largest, and so on. For example, for a full house,
        # the list will be [3, 2]. For a two pair it will be [2, 2, 1]
        # and so on. We exclude jokers at first, because we treat
        # ranking differently based on if the hand is wild.
        count_list = sorted(
            [v for k, v in card_count.items() if k != "J" and v > 0], 
            reverse=True
        )

        try:
            if wild:    
                # Add jokers to highest count.
                count_list[0] += card_count["J"]
            else:       
                # Add jokers back in and sort again.
                count_list.append(card_count["J"])
                count_list.sort(reverse=True)
        except IndexError:  # Wild and all jokers.
            return 5
        except KeyError:    # No jokers.
            pass

        # The hand is a two pair or a full house.
        if count_list[0] in (2, 3) and count_list[1] == 2:
            count_list[0] += 0.5

        return count_list[0]


def get_winnings(split_lines: list[tuple[str, str]], wild=False) -> int:
    """Gets the total winnings for a game based on whether the hands
    should be treated as wild or not.
    """

    hands_bids = sorted([(Hand(h, wild), int(b)) for h, b in split_lines])

    return reduce(
        lambda t, x: t + x,
        [(i + 1) * hb[1] for i, hb in enumerate(hands_bids)]
    )


if __name__ == "__main__":    
    with open("/home/jacob/git/adventofcode/2023/day_07/input.txt") as fp:
        split_lines = [line[:-1].split(" ") for line in fp]

    print("Part One:", get_winnings(split_lines))
    print("Part Two:", get_winnings(split_lines, wild=True))
