/* SI335 Spring 2018 (from Dr. Sipes)
 * Project 1: OMA Service Selection
 *
 * This contains the "Sublimely Magnificent Algorithm" algorithm to do the service
 * selection, provided as example/starter code.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdlib>
using namespace std;

struct Person {
  string name;
  unsigned int chosen:1;
};


struct jobChoice {
  int* candid;
  int pos;
};

int main(int argc, char **argv) {
  // Check that the filename is given on command line
  if (argc < 2) {
    cerr << "usage: selection <filename>" << endl;
    exit(1);
  }

  // Open input file and complain if there's a problem
  ifstream fin(argv[1]);
  if (!fin) {
    cerr << "Error: file \"" << argv[1] << "\" could not be opened!" << endl;
    exit(2);
  }

  int k, n;

  // Read in the number of communities
  fin >> k;
  fin.ignore(1024,'\n');

  // Read in the community names
  string* communities = new string[k];
  for (int i=0; i<k; ++i) {
    getline(fin, communities[i]);
  }

  // Read in the number of proles
  fin >> n;



  
  // Read in the proles' names and rankings
  // Rankings will be stored in an array of arrays.
  // Each array in the array will contain all k rankings for that prole.

  struct Person* people = new struct Person[n];//struct of names of people and if they have been chosen or not
  struct jobChoice* jobs = new struct jobChoice[k];//array of candidates based upon their order read in and the position in that array

  for (int j=0; j<k; ++j){//initialize all the arrays
    jobs[j].candid = new int[n];//each job gets an array of n size for each person
    jobs[j].pos = 0;//start at the head of each array
  }
  for (int i=0; i<n; ++i) {
    fin >> people[i].name;//read in the name
    people[i].chosen = 0;//default no one is chosen

    // Read in the rankings
    for (int j=0; j<k; ++j) {
      int rank;
      fin >> rank;
      jobs[j].candid[rank-1] = i;//position the person in the job array based on their rank from that job
    }
  }


  // Now do the actual selection
  // da way:
  for(int i = 0, j = 0; i < n;){
    //break up the lookup so that it is readable
    struct jobChoice curJob = jobs[j];//which job we are looking at
    int* who = curJob.candid;//pull the array of candidates
    int where = curJob.pos; //where that candidate is in the person array
    int peoplePos = who[where];//where that person is
    if (people[peoplePos].chosen == 0){
      people[peoplePos].chosen = 1;//they are now chosen
      cout << people[peoplePos].name <<  ' ' << communities[j] << '\n';//print it out
      jobs[j].pos++;//move to the next position
      j = (j+1)%k;//next job cyclic
      i++;
    }
    else {
      jobs[j].pos++;//next position in that array
    }
  }

  // De-allocate the dynamic memory we got
  delete [] communities;
  delete [] people;
  for (int j = 0; j < k; ++j) delete [] jobs[j].candid;
  delete [] jobs;

  return 0;
}
