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
void seq(); void seqtail();
void catseq(); void cattail(vector<string>& vec);
void opseq(); void optail();
void atom();

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
  seq();
  match(STOP);
  cout << "Parse OK" << endl;
  //perror("stmt (Not implemented yet!)");
}

void seq(){
  catseq();
  seqtail();
}

void seqtail(){
  switch(peek()) {
    case FOLD:
      match(FOLD);
      catseq();
      seqtail();//do the thing then call the funcs
      break;
    case RB: case STOP:
      break;
    default:
      perror("seqtail");
  }
}


void catseq(){
  opseq();
  cattail();//Call the next two
}

void cattail(){
  switch(peek()) {
    case COLON: case NAME: case REV: case SYM: case LB:
      opseq();
      cattail();
      break;
    case STOP: case RB: case FOLD:
      break;
    default:
      perror("cattail");
  }
}

void opseq(){
  atom();
  optail();
}

void optail(){
  switch(peek()) {
    case COLON:
      match(COLON);
      match(NAME);//FIXME? add these to return value??
      optail();
      break;
    case REV:
      match(REV);
      optail();
      break;
    case STOP: case RB: case NAME: case SYM: case FOLD: case LB:
      break;
    default:
      perror("optail");
  }
}

void atom(){
  switch(peek()) {
    case SYM:
      match(SYM);
      break;
    case NAME:
      match(NAME);
      break;
    case LB:
      match(LB);
      seq();
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
