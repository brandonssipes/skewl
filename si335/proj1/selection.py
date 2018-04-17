#!/usr/bin/python3

''' SI 335 Spring 2017 (from Dr. Roche)
    Project 1: OMA Service Selection

    This contains the "simple" algorithm to do the service selection,
    provided as example/starter code.
'''

import sys

# Check that the filename is given on command line
if len(sys.argv) < 2:
    print('usage: selection <filename>',file=sys.stderr)
    sys.exit(1)

# Open input file and complain if there's a problem
fin = open(sys.argv[1],"r")

# Read in the number of communities
k = int(fin.readline())

# Read in community names
communities = []
for i in range(k):
    communities.append(fin.readline().strip())

# Read in number of proles
n = int(fin.readline())

# Read in proles' names and rankings
# Rankings will be stored in a list of lists.
# Each list in the list will contain all k rankings for that prole.
proleNames = []
proleRanks = []

for i in range(n):
    lineparts = fin.readline().strip().split()
    proleNames.append(lineparts[0])
    ranks = []
    for j in range(1, k+1):
        ranks.append(int(lineparts[j]))
    proleRanks.append(ranks)

# This list will hold the names that are already picked
picked = []

# Now do the actual selection.
for i in range(n):
    comm = i % k # which community gets the next pick
    rank = 0 # start with the top-ranked pick
    found = False # set to true once we find the next pick

    while not found:
        rank = rank + 1

        for j in range(n):
            if proleRanks[j][comm] == rank:
                nextPick = proleNames[j]

        # Now nextPick is the name of the prole with rank "rank"
        # by community "comm". But are they already picked?

        found = True
        for j in range(len(picked)):
            if picked[j] == nextPick:
                found = False


    # Now we have the actual pick!
    # Print it and then add to the "picked" list.
    print(nextPick, communities[comm])
    picked.append(nextPick)
