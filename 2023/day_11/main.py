"""Day 11 of advent of code 2023"""

from typing import NamedTuple


class Point(NamedTuple):
    
    row: int
    col: int


def min_max(a, b):
    return (a, b) if a < b else (b, a)

def sum_dists(
        no_gal_rows: set[int], no_gal_cols: set[int], 
        galaxies: list[Point], scale: int) -> int:
    """Finds the distance between each galaxy based on how much
    rows/cols without galaxies should be scaled. For each pair of
    galaxies, sees if there are any rows/cols that lack galaxies
    between the pair. Then adds the appropriate distance.
    """

    total_dist = 0
    for g1 in galaxies:
        for g2 in galaxies:
            min_row, max_row = min_max(g1.row, g2.row)
            min_col, max_col = min_max(g1.col, g2.col)

            rows = [r for r in no_gal_rows if r > min_row and r < max_row]
            cols = [c for c in no_gal_cols if c > min_col and c < max_col]

            total_dist += (max_row - min_row) + len(rows) * (scale - 1)
            total_dist += (max_col - min_col) + len(cols) * (scale - 1)

    return total_dist // 2


if __name__ == "__main__":
    with open("input.txt") as fp:
        lines = fp.readlines()

    gal_rows = set()
    gal_cols = set()
    galaxies = list[Point]()
    for i, row in enumerate(lines):
        for j, c in enumerate(row):
            if c == "#":
                gal_rows.add(i)
                gal_cols.add(j)
                galaxies.append(Point(i, j))
            
    no_gal_rows = set(range(len(lines))) - gal_rows
    no_gal_cols = set(range(len(lines[0]))) - gal_cols

    print("Part One:", sum_dists(no_gal_rows, no_gal_cols, galaxies, 2))
    print("Part Two:", sum_dists(no_gal_rows, no_gal_cols, galaxies, 1000000))
