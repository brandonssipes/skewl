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
    Exp* funexp;
    Exp* arg;

  public:
    Sqrt(Exp* f, Exp*a) {
      funexp = f;
      arg = a;
      ASTchild(arg);
      ASTchild(funexp);
    }

    void exec(Frame*ST)override{
      //get the argument from ST
      //do the work
      int x = arg->eval(ST).num();
      x = std::sqrt(x);

      Value *ret = new Value(x);
      //use ST to set the return
      ST->rebind("ret",(*ret));
    }
};

class Rand :public Stmt {
  private:
    Exp* arg;

  public:
    Rand(Exp*a){
      arg = a;
      ASTchild(arg);
    }

    void exec(Frame*ST)override{
      int n = arg->eval(ST).num();
      int randomNum = 1 + std::rand()/((RAND_MAX + 1u)/n); //random number from 1 to n
      Value *ret = new Value(randomNum);
      ST->rebind("ret",(*ret));
    }
};

#endif // BUILTIN_HPP
