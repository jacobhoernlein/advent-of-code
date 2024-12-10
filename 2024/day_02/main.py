def report_ok_1(report: list[int]) -> bool:
    diffs = [report[i] - report[i - 1] for i in range(1, len(report))]
    
    abs_diffs = list(map(abs, diffs))
    if min(abs_diffs) < 1 or max(abs_diffs) > 3:
        return False
    
    dec = len(list(filter(lambda x: x < 0, diffs)))
    return dec == 0 or dec == len(diffs)

def report_ok(report: list[int]) -> bool:
    for i in range(len(report)):
        r = report.copy()
        r.pop(i)
        if report_ok_1(r):
            return True
    return False


if __name__ == "__main__":
    with open("input.txt") as fp:
        input = [
            list(map(int, l.split(" ")))
            for l in fp.readlines()
        ]

    print(len(list(filter(report_ok, input))))
