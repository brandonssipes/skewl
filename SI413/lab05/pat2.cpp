/* SI 413 Fall 2018
 * Lab 05
 * Recursive descent parser for pat language.
 * Brandon Sipes
 */

#include "pat.hpp"
#include <cstdlib>
using namespace std;

/*******************BEGIN NOTES FUNCTIONS**********************/
#include <map>
#include <vector>

// Prints out a vector of strings with spaces in between
// You can call this just like resout << some_vector << endl;
ostream& operator<< (ostream& out, const vector<string>& vec) {
  if (vec.empty()) return out;
  out << vec[0];
  for (unsigned long i=1; i<vec.size(); ++i)
    out << ' ' << vec[i];
  return out;
}

// Concatenates two vectors of strings
vector<string> concat(const vector<string> &A, const vector<string> &B) {
  vector<string> res;
  unsigned long int i;
  for(i = 0; i < A.size(); ++i) res.push_back(A[i]);
  for(i = 0; i < B.size(); ++i) res.push_back(B[i]);
  return res;
}

// Reverses a vector of strings
vector<string> rev(const vector<string> &A) {
  vector<string> res;
  long int i;
  for(i = A.size() - 1; i >= 0; --i) res.push_back(A[i]);
  return res;
}
/*******************END NOTES FUNCTIONS************************/

// These are the prototypes for your recursive descent function.
// Of course you need to implement these below!
void stmt();
void seq(vector<string>& vec); void seqtail(vector<string>& vec);
void catseq(vector<string>&vec); void cattail(vector<string>& vec);
void opseq(vector<string>&vec); void optail(vector<string>& vec);
void atom(vector<string>&vec);

int lookahead = -1; // store next token

map<string, vector<string> > symTable;

// These are the colored output streams to make things all pretty.
colorout resout(1, 'u');
colorout errout(2, 'r');

// --------- Helper Functions

// Gets called if we see an unexpected token
void perror(const char* funcname) {
  errout << "Parse error in " << funcname << endl;
  exit(1);
}

// Returns the next token without actually consuming it
int peek() {
  if (lookahead == -1) lookahead = yylex();
  return lookahead;
}

// Consumes the next token, and makes sure it matches the argument.
// If so, the semantic value of the token (a string) is returned.
string match(int tok) {
  if (tok == peek()) {
    lookahead = -1;
    return yylval;
  }
  else {
    errout << "Token match error" << endl;
    exit(1);
  }
}

// ---------------- Recursive descent functions

void stmt() {
  vector<string> vec;
  seq(vec);
  resout << vec << endl;
  match(STOP);
}

void seq(vector<string>&vec ){
  catseq(vec);
  seqtail(vec);
}

vector<string> fold(const vector<string> &A, const vector<string> &B){
  vector<string> res;
  unsigned long int i;
  for(i = 0; i < max(A.size(), B.size()); ++i){//go for the longest one
    if (i < A.size()) res.push_back(A[i]);//make sure we do not go over the buffer
    if (i < B.size()) res.push_back(B[i]);
  }
  return res;
}

void seqtail(vector<string>&vec){
  vector<string> helper;
  switch(peek()) {
    case FOLD: //FOLD: "*" mesh the strings
      match(FOLD);
      catseq(helper);//do everything for this side of the fold
      seqtail(helper);
      vec = fold(vec, helper);//then put them together

      break;
    case RB: case STOP:
      break;
    default:
      perror("seqtail");
  }
}


void catseq(vector<string>&vec){
  vector<string> A;//separate it out to avoid clobbering of calls
  vector<string> B;
  opseq(A);
  cattail(B);//Call the next two
  vec = concat(A,B);
}

void cattail(vector<string>&vec){
  switch(peek()) {
    case COLON: case NAME: case REV: case SYM: case LB:
      opseq(vec);
      cattail(vec);
      break;
    case STOP: case RB: case FOLD:
      break;
    default:
      perror("cattail");
  }
}

void opseq(vector<string>&vec){
  atom(vec);
  optail(vec);
}

void optail(vector<string>&vec){
  switch(peek()) {
    case COLON:
      match(COLON);
      //Store current vec into NAME
      symTable[match(NAME)] = vec;
      optail(vec);
      break;
    case REV:
      match(REV);
      //reverse the vector
      vec = rev(vec);
      optail(vec);
      break;
    case STOP: case RB: case NAME: case SYM: case FOLD: case LB:
      break;
    default:
      perror("optail");
  }
}

void atom(vector<string>&vec){
  string var;
  vector<string> cev;
  switch(peek()) {
    case SYM:
      vec.push_back(match(SYM));
      break;
    case NAME:
      var = match(NAME); //get the variable name
      if(symTable.count(var) <= 0) //check if the name exists
        exit(1);
      vec = concat(vec, symTable[var]);
      break;
    case LB:
      match(LB);
      seq(cev);
      vec = concat(vec, cev);
      match(RB);
      break;
    default:
      perror("atom");
  }
}

//-- Main method
int main(void) {
  // This checks whether the output is a terminal.
  bool tty = isatty(0) && isatty(2);

  while(true) {
    if (tty) cerr << "> " << flush;
    if (peek() == 0) break;
    stmt();
  }

  if (tty) cerr << "Goodbye" << endl;
  return 0;
}
