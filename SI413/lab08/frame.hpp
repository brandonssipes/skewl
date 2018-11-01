/* SI 413 Fall 2018
 * Lab 7
 * C++ header file for the Frame class
 * Brandon Sipes
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

    Frame*parent;

  public:
    // Creates a new, empty symbol table
    Frame() { }

    // Create a new symbol table with a frame set
    Frame(Frame*ST){
      parent = ST;
    }


    // Destructor for a SymbolTable object
    virtual ~Frame () {
      // (nothing really to do here until later labs...)
      bindings.clear();
    }

    // Returns the Value bound to the given name.
    Value lookup(string name) {
      for(Frame*curr = this; curr != nullptr; curr = curr->parent){
        if (curr->bindings.count(name) > 0) return curr->bindings[name];
      }
      if (!error) {
        error = true;
        errout << "ERROR: No binding for variable " << name << endl;
      }
      return Value();
    }

    // Creates a new name-value binding
    void bind(string name, Value val = Value()) {
      if(this->bindings.count(name) > 0)
        if(!error){
          error = true;
          errout << "ERROR: Variable " << name << " already bound!" << endl;
        }
      this->bindings[name] = val;
      /*for(Frame*curr=this; curr != nullptr; curr= curr->parent){
        if(curr->bindings.count(name) > 0)
          if(!error){
            error = true;
            errout << "ERROR: Variable " << name << " already bound!" << endl;
          }
        curr->bindings[name] = val;
      }*/
    }

    // Re-defines the value bound to the given name.
    void rebind(string name, Value val) {
      bool found = false; //look for the variable first
      for(Frame*curr=this; curr != nullptr; curr = curr->parent){
        if(curr->bindings.count(name) != 0){
          curr->bindings[name] = val;
          found = true;
          break;//stop at the first one found
        }
      }
      if(!found) //if we cannot find it in any frame then throw error
        if(!error){
          error = true;
          errout << "ERROR: Can't rebind " << name << "; not yet bound!" << endl;
        }
    }
};

#endif // ST_HPP
