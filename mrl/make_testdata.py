#!/usr/bin/env python

import math
import sys
import os

n = int(sys.argv[1])
print(n)

f = open("sin.data", "w")

f.write(str(n*2) + " " + str(n) + " " + str(n) + "\n")

scale = 0.1
for i in range(n * 2):
    samples = [math.sin((x + i) * scale) for x in range(n * 2)]
    for x in range(n):
        f.write(str(samples[x]) + " ")
    f.write("\n")
    
    for x in range(n, n * 2):
        f.write(str(samples[x]) + " ")
    f.write("\n")

f.close()
