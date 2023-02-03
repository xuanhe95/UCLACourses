import sys

result = {}
for line in sys.stdin:
# for line in inpput:
    wordlist = line.split()
    if len(wordlist) == 0:
        continue
    if wordlist[0] == 'Date:':
        if wordlist[-1] in result:
            result[wordlist[-1]] = result[wordlist[-1]] + 1
        else:
            result[wordlist[-1]] = 1
for value in sorted(result.keys(), key = lambda item: int(item)):
    output = value + "  "+ str(result[value])
    print(output)