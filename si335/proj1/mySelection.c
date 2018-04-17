/* SI335 Spring 2018 (from Dr. Sipes)
 * Project 1: OMA Service Selection
 *
 * This contains the "advanced" algorithm to do the service
 * selection, provided as ultimate code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>

int main(int argc, char **argv) {
  // Check that the filename is given on command line
  if (argc < 2) {
    fprintf(2, "usage: selection <filename> \n");
    exit(1);
  }

  // Open input file and complain if there's a problem
  FILE fd;
  fd = fopen(argv[1], "r");
  if (fd == NULL) {//check how fctl returns
    fprintf(2, "Error: file \"%s\" could not be opened!\n", argv[1]); 
    exit(2);
  }

  int k, n;

  // Read in the number of communities
  fscanf(fd, "%d", &k);

  // Read in the community names
  size_t len = 0;
  char* communities[k];
  for (int i=0; i<k; ++i) {
    getline(&communities[i], &len, fd);
  }

  // Read in the number of proles
  fscanf(fd, "%d", &n);
  
  // Read in the proles' names and rankings
  // Rankings will be stored in an array of arrays.
  // Each array in the array will contain all k rankings for that prole.
  char* proleNames[n];
  int* proleRanks[n];
  for (int i=0; i<n; ++i) {
    fscanf(fd, "%512s", proleNames[i]);

    // Read in the rankings
    proleRanks[i] = new int[k];//is this allowed
    for (int j=0; j<k; ++j) {
      fscanf(fd, "%d", proleRanks[i][j]);
    }
  }

  // This list will hold the names that are already picked
  char* picked[n];

  // Now do the actual selection
  for (int i = 0; i < n; ++i) {
    int comm = i % k; // Which community gets this pick
    int rank = 0; // start with the top-ranked pick
    bool found = false;
    string nextPick;

    while(! found) { 
      rank = rank + 1;

      for (int j = 0; j < n; ++j) {
        if (proleRanks[j][comm] == rank) {
          nextPick = proleNames[j];
        }
      }

      // Now nextPick is the name of the prole with rank "rank"
      // by community "comm". But are they already picked?

      found = true;
      for (int j = 0; j < i; ++j) {
        if (picked[j] == nextPick) found = false;
      }
    }

    // Now we have the actual pick!
    // Print it and then add to the "picked" list.
    cout << nextPick << ' ' << communities[comm] << endl;
    picked[i] = nextPick;
  }

  // De-allocate the dynamic memory we got
  delete [] picked;
  for (int i=0; i<n; ++i) delete [] proleRanks[i];
  delete [] proleRanks;
  delete [] proleNames;
  delete [] communities;

  return 0;
}
