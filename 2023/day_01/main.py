"""Day one of Advent of Code 2023."""


def part_one(lines: list[str]) -> int:
    """For each line, concatenates the first and last digit, and
    computes the sum over all lines.
    """
    
    total = 0
    for line in lines:
        # Iterate over characters in line until we find the first digit.
        for c in line:
            if c.isdigit():
                num_str = c
                break

        # Do the same thing as before, backwards.    
        for c in reversed(line):
            if c.isdigit():
                num_str += c
                break

        total += int(num_str)
    
    return total

def part_two(lines: list[str]) -> int:
    
    # The possible values that could appear within each line.
    strings = [
        "1", "2", "3", "4", "5", "6", "7", "8", "9",
        "one", "two", "three", "four", "five", "six",
        "seven", "eight", "nine"
    ]

    # Used to map words to strings with a single digit.
    word_to_dec = {
        "one": "1", "two": "2", "three": "3", "four": "4", "five": "5",
        "six": "6", "seven": "7", "eight": "8", "nine": "9"
    }
    
    total = 0
    for line in lines:
        first = None
        last = None

        # In each iteration, s will be "one", "two", etc...
        for s in strings:
            
            # If the current s is found in the line, the index is
            # stored, and checked against the current stored index in
            # first. If it's lower, the tuple is updated to store the
            # new index, as well as the string that it corresponds to.
            if (index := line.find(s)) != -1:
                if not first or index < first[0]:
                    if s.isdigit():
                        first = (index, str(s))
                    else: # Need to map the word to a string w/ digit.
                        first = (index, word_to_dec[s])
                    
            # We need to search in reverse order too, because there may
            # be repeats of the number within the string.
            if (index := line.rfind(s)) != -1:
                if not last or index > last[0]:
                    if s.isdigit():
                        last = (index, str(s))
                    else:
                        last = (index, word_to_dec[s])
        
        # Concatenate the first and last digits and add to total.
        total += int(first[1] + last[1])
    
    return total


if __name__ == "__main__":
    with open("input.txt", "r") as fp:
        lines = [line for line in fp]

    print("Part One:", part_one(lines))
    print("Part Two:", part_two(lines))
