/* SI413 Fall 2018
 * Lab 11
 * Global definitions for the compiler
 * Brandon Sipes
 */

#ifndef SPLC_HPP
#define SPLC_HPP

#include "colorout.hpp"
#include <map>
using namespace std;

// forward declarations
class Stmt;


// Global variables
extern colorout resout;
extern colorout errout;
extern Stmt* tree;

// This class holds the context for AST evaluation
// Right now, it just keeps track of register or label names to use
class Context {
  private:
    int regcount = 0;
    std::map<string,Stmt*> funcMap;

  public:
    // returns a series of unique register names like
    // "%v1", "%v2", etc.
    string nextRegister() {
      return "%v" + to_string(++regcount);
    }
    int x;
};

#endif // SPLC_HPP
