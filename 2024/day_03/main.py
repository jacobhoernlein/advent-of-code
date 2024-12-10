import re

def part_one(t):
    return sum(int(a)*int(b) for a,b in re.findall(r'mul\((\d+),(\d+)\)', t))

if __name__ == "__main__":
    with open("input.txt") as fp:
        text = fp.read()

    print("Part One:", part_one(text))
    print("Part Two:", sum(part_one(t) for t in re.findall(r"(?:^|do\(\)).*?(?:$|don't\(\))", text, flags=re.DOTALL)))
    