/* SI 413 Fall 2018
 * Lab 10
 * C++ header file for the Frame class
 * Brandon Sipes
 */

#ifndef ST_HPP
#define ST_HPP

#include <iostream>
#include <map>
#include <string>
#include <list>
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
    static list<Frame*> allFrames;
    bool marked;

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
      allFrames.push_back(this);
      marked = false;
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

    static int len() {return allFrames.size();}

    void mark() {
      if(this->marked == true) return;//break if we find something that is marked
      this->marked = true; //otherwise mark it as true
      map<string,Value>::iterator iter = bindings.begin();
      while (iter != bindings.end()) {
        //test if value is a clousure 
        //if it is then get it's environment
        //look at that frame and if it is not marked then
        //mark it
        if (iter->second.getType() != FUN_T){//continue until clousure is found
          ++iter;
          continue;
        }
        Frame* cur = iter->second.func().env;//get the environment
        if(cur != nullptr)//as long as it is not null
          cur->mark();//mark it and everything it points to
        ++iter; // Increments the iterator to go to the next pair.
      }
    }

    static void sweep(){
      list<Frame*>::iterator iter = allFrames.begin();
      while(iter != allFrames.end()){
        Frame* cur = *iter;
        if (!(cur->marked)) {
          //delete cur;
          //cur = allFrames.erase(*cur);
        }else{
          cur->marked = false;
          //cur = iter.next();
        }
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
