"""Day two of Advent of Code 2023."""


def part_one(lines: list[str]) -> int:
    """Computes the sum of the IDs of games that are possible based on
    the given maximum number of cubes.
    """
    
    maxes = {"red": 12, "green": 13, "blue": 14}
    
    total = 0
    for line in lines:
        valid = True # We will only add the ID if the line is valid.

        # Break up the string by the colon and semicolon into the ID
        # and the different handfuls.
        id, handfuls = line.split(":")
        id = int(id[5:])
        handfuls = handfuls[:-1].split(";")
        
        for hand in handfuls:
            # This list is now of the form ["1", "red, ", "2", "blue"]
            blocks = hand.split(" ")[1:]
            
            # Loop while there's still elements in the list and the
            # game is still valid.
            while blocks and valid:
                # Remove the first two elements, which correspond to a
                # block's color and count. 
                num = int(blocks.pop(0))
                color = blocks.pop(0).strip(",")
                
                if num > maxes[color]:
                    valid = False
                    break
            
            if not valid:
                break

        if valid:
            total += id
    
    return total          

def part_two(lines: list[str]) -> int:
    """Similar to part one, but instead for each game we find the
    product of the minimum number of each color block in order to
    complete the game. Then, we find the sum of each of those products.
    """
    
    total = 0
    for line in lines:
        maxes = {"red": 0, "green": 0, "blue": 0}
        handfuls = line.split(":")[1][:-1].split(";") # Beautiful 😘
        
        for hand in handfuls:
            blocks = hand.split(" ")[1:]
            
            while blocks:
                num = int(blocks.pop(0))
                color = blocks.pop(0).strip(",")
                maxes[color] = max(maxes[color], num)

        total += maxes["red"] * maxes["green"] * maxes["blue"]
                
    return total 


if __name__ == "__main__":
    with open("input.txt", "r") as fp:
        lines = [line for line in fp]

    print("Part One:", part_one(lines))
    print("Part Two:", part_two(lines))
