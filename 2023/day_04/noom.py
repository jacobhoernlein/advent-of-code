"""program that my friend wrote for today."""


xddfunnyfile = open("input.txt",'r')
themlines = xddfunnyfile.readlines()
part1,linecount = 0,0

def findmatchingnumbers(line):
    dumptruckvariable, line = line.split(":")
    leftside, rightside = line.split("|")
    matches = set(leftside.split()) & set(rightside.split())
    return(len(matches))

for lines in themlines:
    linecount +=1
totalcards = [1]*linecount

for card, line in enumerate(themlines):
    numbersmatching = findmatchingnumbers(line)
    part1 += int(2**(numbersmatching-1))
    for i in range(numbersmatching):
        totalcards[i+card+1] += totalcards[card]
print(part1, sum(totalcards))
