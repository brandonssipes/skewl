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
  EXP* funexp;//the function 
  Exp* arg;

  public:
    Sqrt() {

    }

    void exec(Frame*ST)override{//This is an exec not an eval,  different?
      //Funcall gets the function
      Closure func = ST.func();//funexp ->eval(ST).func();//get the closure

      Frame* lamenv = new Frame(func.env);
      lamenv->bind("ret",Value());
      lamenv->bind(func.lam->getVar(), arg->eval(ST));
      func.lam->getBody()->exec(lamenv);//This is what I'm doing
      //return lamenv->lookup("ret");//Don't need this
      //use ST to get the argument
      //
      //set the return value
      int x = arg->eval(ST);
      int x = func.lam->getVar();
      x = std::sqrt(x);
      //how do I return?
      lamenv->rebind("ret",Value(x));

    }
};

#endif // BUILTIN_HPP
