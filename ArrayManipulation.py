import math
import os
import random
import re
import sys

# Complete the arrayManipulation function below.
def arrayManipulation(n, queries):
    addred = {}
    for s,e,k in queries:
        c_s = s
        c_e = e+1
        if not addred.get(c_s):
            addred[c_s] = 0
        if not addred.get(c_e):
            addred[c_e] = 0
        addred[c_s] += k
        addred[c_e] -= k
    max_v = 0
    sum_v = 0
    for idx in range(n+1):
        if not addred.get(idx+1):
            value = 0
        else:
            value = addred[idx+1]
        if value > 0:
            sum_v+= value
        else:
            if max_v < sum_v:
                max_v = sum_v
            sum_v+=value
    return max_v


if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nm = input().split()

    n = int(nm[0])

    m = int(nm[1])

    queries = []

    for _ in range(m):
        queries.append(list(map(int, input().rstrip().split())))

    result = arrayManipulation(n, queries)
    print(result)
    # fptr.write(str(result) + '\n')

    # fptr.close()