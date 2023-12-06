"""Day five of Advent of Code 2023."""

import dataclasses


@dataclasses.dataclass
class Range:
    """Class that represents a range of numbers as simply two numbers
    rather than a list.
    """
    
    first: int
    last: int

    def intersection(self, other: "Range"):
        """Returns a Range that represents an intersection with
        another Range, or None if no intersection exists.
        """
        
        # No ranges to make intersections out of.
        if not self or not other:
            return None
        
        if other.first >= self.first and other.first <= self.last:
            return Range(other.first, min(self.last, other.last))
        if other.last >= self.first and other.last <= self.last:
            return Range(self.first, min(self.last, other.last))
        if self.first >= other.first and self.first <= other.last:
            return Range(self.first, self.last)
        
        # No overlap
        return None
    
    def __lt__(self, other: "Range"):
        """Returns if a range is less than another range or not, for
        use with sorting algorithms.
        """

        return self.first < other.first
    
    def __bool__(self):
        """To quickly check if a range is valid or not."""
        
        return self.first <= self.last


# Type definition so I don't have to keep typing it out.
Map = list[tuple[Range, Range]]


def translate(r: Range, map: Map) -> list[Range]:
    """Takes a Range and breaks it up into a list of ranges based on
    the Map passed to it.
    """
    
    ranges = list[Range]()
    r = dataclasses.replace(r)  # Copy so it doesnt fuck with list.

    # Since map is sorted by source range in increasing order, we can
    # iterate over it linearly.
    for source, dest in map:
        # Check if there's an intersection between the current source
        # Range and the r Range.
        if sex := source.intersection(r):
            sex_dest = dataclasses.replace(dest) # copy again

            if sex.first > r.first:
                # The map doesn't cover some of the range.
                new_range = Range(r.first, sex.first - 1)
                ranges.append(new_range)
            else:
                # The range starts after the map, we need to cut down
                # the destination accoordingly.
                sex_dest.first += sex.first - source.first
            
            if sex.last < r.last:
                # There's some left over, change r.
                r.first = sex.last + 1
            else:
                # There's range ends before the map ends. Need to cut
                # down destination range again, and make r invalid.
                sex_dest.last -= source.last - sex.last
                r.first = r.last + 1
            
            # Append the translated range to the list.
            ranges.append(sex_dest)
        elif r < source:
            break 

    # There's shit leftover.
    if r:
        ranges.append(r)

    return ranges   

def consolidate(ranges: list[Range]):    
    """Consolidates a list of sorted ranges by eliminating any overlap.
    """
    
    i = 1
    while i < len(ranges):
        if ranges[i - 1].intersection(ranges[i]):
            ranges[i].first = ranges[i - 1].first
            ranges.pop(0)
        else:
            i += 1


class Almanac():
    """Stores a list of maps in order to translate either a point or
    ranges through them.
    """

    def __init__(self, input: list[str]):
        self.maps = list[Map]()
    
        for line in input:
            if not line:    # Empty line. Don't do anything.
                continue
            elif not line[0].isdigit(): # New map.
                self.maps.append([])
            else:   # New range pair for last map.
                nums = [int(n) for n in line.split(" ") if n]
                
                dest_start = nums[0]
                source_start = nums[1]
                range_len = nums[2]

                source = Range(source_start, source_start + range_len - 1)
                dest = Range(dest_start, dest_start + range_len - 1)

                self.maps[-1].append((source, dest))
        
        # Sort each map by inreasing source range
        for map in self.maps:
            map.sort(key=lambda k: k[0])

    def translate(self, n: int) -> int:
        """Translates one number through the maps."""
        
        for map in self.maps:
            for source, dest in map:
                if n >= source.first and n <= source.last:
                    n = dest.first + n - source.first
                    break
        return n

    def translate_range(self, r: Range) -> list[Range]:
        """Takes a range, and translates it through the map, resulting
        in a list of one or more ranges in increasing order.
        """
        
        ranges = [dataclasses.replace(r)]
        for map in self.maps:
            new_ranges = []
            for r1 in ranges:
                [new_ranges.append(r2) for r2 in translate(r1, map)]
            new_ranges.sort()
            consolidate(new_ranges)
            ranges = new_ranges
        return ranges
   

def part_one(seeds: list[int], almanac: Almanac) -> int:
    """Translates every seed and returns the minimum."""
    
    return min([almanac.translate(s) for s in seeds])

def part_two(seeds: list[int], almanac: Almanac) -> int:
    """Instead of translating individual seeds, translates ranges of
    seeds, then returns the minimum from the resulting ranges.
    """
    
    min_loc = None
    while seeds:
        source = seeds.pop(0)
        length = seeds.pop(0)

        r = Range(source, source + length - 1)
        ranges = almanac.translate_range(r)

        if not min_loc:
            min_loc = ranges[0].first
        elif ranges[0].first < min_loc:
            min_loc = ranges[0].first

    return min_loc
        

if __name__ == "__main__":
    with open("2023/day_05/input.txt") as fp:
        lines = [line[:-1] for line in fp]

    seeds = [int(s) for s in lines[0].split(":")[1].split(" ") if s]
    almanac = Almanac(lines[2:])

    print("Part One:", part_one(seeds, almanac))
    print("Part Two:", part_two(seeds, almanac))
