#!/usr/bin/env python3

import sys
import os

DECIMAL_PLACES = 2
THRESHOLD = 0.01

# Parsing the input arguments to make sure they're valid.
# It's udgly but there's no need to use argparse for a script so simple

if len(sys.argv) != 4:
    print("Expects 3 arguments, the input file name, the number samples per input, and the output filename")
    sys.exit(1)

if not os.path.isfile(sys.argv[1]):
    print("File: " + str(sys.argv[1]) + " not found")
    sys.exit(1)

if os.path.isfile(sys.argv[3]):
    print("File " + str(sys.argv[3]) + "exists on the system already. Exitting")
    sys.exit(1)

try:
    if int(sys.argv[2]) <= 0:
        print("Second argument must be greater than or equal to 0")
        sys.exit(1)
except:
    print("Second argument must be an integer")
    sys.exit(1)

# Putting the data together in lines such fenn will real each set of n data points
# as input and the next n set of data points as output
numSPerLine = int(sys.argv[2])
lineBuffer = []
firstTime = True
with open(str(sys.argv[1]),"r") as infile:
    with open(str(sys.argv[3]),"a") as outfile:
        outfile.write(str(numSPerLine) + " " + str(numSPerLine) + " " + str(numSPerLine) + "\n")
        for line in infile:
            # The highest number that will occur in the data is 32767
            # Everything else must be scaled so it fits between -1 and 1
            # for fenn
            line = str(round(int(line.split("\n")[0])/32767,DECIMAL_PLACES))
            if len(lineBuffer) == numSPerLine:
                aboveThreshold = True
                for item in lineBuffer:
                    if abs(float(item)) < THRESHOLD:
                        aboveThreshold = False
                if aboveThreshold:
                    outfile.write(" ".join(lineBuffer) + "\n")
                    if not firstTime:
                        outfile.write(" ".join(lineBuffer) + "\n")
                    else:
                        firstTime = False
                lineBuffer = []
            lineBuffer.append(line)
        outfile.close()
    infile.close()
