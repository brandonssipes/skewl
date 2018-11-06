/* SI 413 Fall 2018
 * Lab 9
 * C++ header file for the Frame class
 */

#ifndef ST_HPP
#define ST_HPP

#include <iostream>
#include <map>
#include <string>
using namespace std;

#include "value.hpp"

// Global variable to indicate if an error has occurred.
extern bool error;

// Declare the output streams to use everywhere
extern colorout resout;
extern colorout errout;

/* This class represents a simple global symbol table.
 * Later we will extend it to support dynamic scoping.
 */
class Frame {
  private:
    // The actual map. It is declared private, so it can only
    // be accessed via the public methods below.
    map<string,Value> bindings;
    Frame* parent;

    // finds the closest frame with the given name, searching
    // parents frames as necessary.
    // Returns null if not found.
    Frame* find(string name) {
      Frame* cur = this;
      while (cur && cur->bindings.count(name) == 0) {
        cur = cur->parent;
      }
      return cur;
    }

  public:
    // Creates a new, empty symbol table
    Frame(Frame* par) {
      parent = par;
    }

    // Destructor for a Frame object
    virtual ~Frame () {
      // (nothing really to do here until later labs...)
      bindings.clear();
    }

    // Returns the Value bound to the given name.
    Value lookup(string name) {
      Frame* found = find(name);
      if (found) return found->bindings[name];
      else {
        if (!error) {
          error = true;
          errout << "ERROR: No binding for variable " << name << endl;
        }
        return Value();
      }
    }

    // Creates a new name-value binding
    void bind(string name, Value val = Value()) {
      if (bindings.count(name) == 0) bindings[name] = val;
      else {
        if (!error) {
          error = true;
          errout << "ERROR: Variable " << name << " already bound!" << endl;
        }
      }
    }

    // Re-defines the value bound to the given name.
    void rebind(string name, Value val) {
      Frame* found = find(name);
      if (found) found->bindings[name] = val;
      else {
        if (!error) {
          error = true;
          errout << "ERROR: Can't rebind " << name << "; not yet bound!" << endl;
        }
      }
    }
};

#endif // ST_HPP
