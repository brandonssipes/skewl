/* SI 413 Fall 2013
 * Lab 9
 * Machinery for making built-in functions
 * Brandon Sipes
 */

#ifndef BUILTIN_HPP
#define BUILTIN_HPP

#include <cmath>
#include "ast.hpp"

// YOUR CODE HERE
class Sqrt :public Stmt {
  private:
  Exp* arg;

  public:
    Sqrt() {

    }

    void exec(Frame*ST)override{
      //Funcall gets the function


      int x;
      x = std::sqrt(x);
      //how do I return?

    }
};

#endif // BUILTIN_HPP
