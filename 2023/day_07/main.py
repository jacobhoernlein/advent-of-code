"""Day seven of Advent of Code 2023."""


class Hand:
    """Class representing a hand of Camel Poker cards. Constructed with
    a string representing the cards, and a boolean representing whether
    or not jokers should be treated as wild. Supports comparison
    between instances."""

    __card_strengths = {
        "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8,
        "9": 9, "T": 10, "J": 11, "Q": 12, "K": 13, "A": 14
    }

    def __init__(self, s: str, bid=0, wild=False):
        self.type = Hand.__get_type(s, wild)
        self.s = s
        self.bid = bid

        # Updates the strength of a joker if the hand is wild or not,
        # then translates each character in the string to an integer
        # value representing its relative weight.
        Hand.__card_strengths["J"] = 1 if wild else 11
        self.__card_strengths = [Hand.__card_strengths[c] for c in s]

    def __repr__(self):        
        return f'Hand("{self.s}")'

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

        # Makes a list with the largest number of cards first, then the
        # next largest, and so on. For example, for a full house, the 
        # list will be [3, 2]. For a two pair it will be [2, 2, 1] and
        # so on. We exclude jokers at first, because we treat ranking 
        # differently based on if the hand is wild.
        count_list = [v for k, v in card_count.items() if k != "J" and v > 0]
        count_list.sort(reverse=True)

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


def get_winnings(lines: list[str], wild=False) -> int:
    """Gets the total winnings for a game based on whether the hands
    should be treated as wild or not.
    """

    hands = [Hand(line[:5], int(line[6:]), wild) for line in lines]
    hands.sort()

    winnings = [(i + 1) * hand.bid for i, hand in enumerate(hands)]
    return sum(winnings)


if __name__ == "__main__":    
    with open("input.txt") as fp:
        lines = fp.readlines()

    print("Part One:", get_winnings(lines))
    print("Part Two:", get_winnings(lines, wild=True))
