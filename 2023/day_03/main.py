"""Day three of Advent of Code 2023."""


def is_symbol(c: str) -> bool:
    """Returns true if the string is a symbol."""
    
    return c != "." and not c.isalnum() 

def get_next_num_str(chars: list[str], i: int) -> tuple[str, int]:
    """Scans through the list and builds a string out of the first set
    of characters that make a number. Returns that string and the index
    following it.
    """
    
    num_str = ""

    # Ignores leading periods and symbols.
    while i < len(chars) and not chars[i].isdigit():
        i += 1

    # Builds string and stops when it's over.
    while i < len(chars) and chars[i].isdigit():
        num_str += chars[i]
        i += 1

    return num_str, i

def check_perimeter(lines: list[str], row: int, start: int, end: int) -> bool:
    """Checks the positions around the substring on the given row with
    given start and end indexes for a symbol. If one is found, return
    True. Else, False.
    """
    
    # Make sure indexes are in bounds.
    if start > 0:
        start -= 1
    if end < len(lines[row]) - 1:
        end += 1
    
    # Check the row above, if it exists.
    if row > 0:
        for c in lines[row - 1][start:end + 1]:
            if is_symbol(c):
                return True
            
    # Check below, if it exists.
    if row < len(lines) - 1:
        for c in lines[row + 1][start:end + 1]:
            if is_symbol(c):
                return True
            
    # Check to the left and right.
    if is_symbol(lines[row][start]) or is_symbol(lines[row][end]):
        return True
    
    return False

def num_str_locations(lines: list[str]) -> dict[int, dict[int, str]]:
    """Returns a dictionary that maps a row and column to a number
    string at that location. If no number string exists at that
    location, then the dictionary will throw a KeyError.
    """
    
    locations = dict[int, dict[int, str]]()
    
    for line_num, line in enumerate(lines):
        chars = list(line)
        i = 0

        # Need to add empty dictionary before we dereference by column.
        locations[line_num] = {}

        while True:
            num_str, i = get_next_num_str(chars, i)
            if not num_str:
                break
            j = i - len(num_str)
            if check_perimeter(lines, line_num, j, i - 1):
                # Add every location covered by string into dictionary.
                while j < i:
                    locations[line_num][j] = num_str
                    j += 1

    return locations

def gear_locations(lines: list[str]) -> list[tuple[int, int]]:
    """Returns a list of tuples with coordinated for every asterisk."""
    
    gears = list[tuple[int, int]]()
    for row_num, line in enumerate(lines):
        i = 0
        # Find every asterisk in the line and add postion to list.
        while (i := line.find("*", i)) != -1:
            gears.append((row_num, i))
            i += 1
    
    return gears

def part_one(lines: list[str]) -> int:
    """Goes line by line, getting each number string. Then, for each
    string, checks the positions around it for a symbol. If one exists,
    add the value to the total.
    """

    total = 0
    for line_num, line in enumerate(lines):
        chars = list(line)
        i = 0

        while True:
            num_str, i = get_next_num_str(chars, i)
            if not num_str:
                break
            if check_perimeter(lines, line_num, i - len(num_str), i - 1):
                total += int(num_str)
    return total

def part_two(lines: list[str]) -> int:
    """Finds a list of every asterisk in the file. Then, for each one,
    checks if there are exactly two numbers surrounding it. If so,
    multiplies them and adds to the total.
    """
    
    gears = gear_locations(lines)
    num_strs = num_str_locations(lines)
    total = 0

    for gear in gears:
        # We use a set to get rid of duplicates automatically.
        nums = set[str]()

        left = gear[1] - 1
        right = left + 2
        
        i = left
        while i <= right:
            
            # Check above.
            try:
                n = num_strs[gear[0] - 1][i]
            except KeyError:
                pass
            else:
                nums.add(n)

            # Check below.
            try:
                n = num_strs[gear[0] + 1][i]
            except KeyError:
                pass
            else:
                nums.add(n)
            
            i += 1
        
        # Check to the left.
        try:
            n = num_strs[gear[0]][left]
        except KeyError:
            pass
        else:
            nums.add(n)

        # Check to the right.
        try:
            n = num_strs[gear[0]][right]
        except KeyError:
            pass
        else:
            nums.add(n)

        # Convert to a list and check if there's two elements.
        l = list(nums)
        if len(l) == 2:
            total += int(l[0]) * int(l[1])

    return total
            

if __name__ == "__main__":
    with open("input.txt") as fp:
        lines = [line[:-1] for line in fp]

    print("Part One:", part_one(lines))
    print("Part Two:", part_two(lines))
