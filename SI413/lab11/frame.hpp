/* SI 413 Fall 2018
 * Lab 11
 * C++ header file for the Frame class
 * Brandon Sipes
 */

#ifndef ST_HPP
#define ST_HPP

#include <iostream>
#include <map>
#include <string>
#include <list>
#include "splc.hpp"

/* This class represents a simple global symbol table.
 * Later we will extend it to support dynamic scoping.
 */
class Frame {
  private:
    // The actual map. It is declared private, so it can only
    // be accessed via the public methods below.
    map<string,string> bindings;

    // Pointer to the parent Frame
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

    // Returns the Value bound to the given name.
    string lookup(string name) {
      Frame* found = find(name);
      if (found) return found->bindings[name];
      else {
        errout << "ERROR: No binding for variable " << name << endl;
        exit(5);
      }
    }

    // Creates a new name-value binding
    void bind(string name, string val) {
      if (bindings.count(name) == 0) bindings[name] = val;
      else {
        errout << "ERROR: Variable " << name << " already bound!" << endl;
        exit(5);
      }
    }
};

#endif // ST_HPP
