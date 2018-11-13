/* SI 413 Fall 2013
 * Lab 10
 * Machinery for making built-in functions
 * Brandon Sipes
 */

#ifndef BUILTIN_HPP
#define BUILTIN_HPP

#include <cmath>
#include <random>
#include <ctime>
#include "ast.hpp"

/* Base class to provide built-in functions.
 * Note that it inherits from FuncDef (like Lambda)
 * and from Stmt, so that we can get the function definition
 * and the functionality both in the same place.
 */
class Builtin :public FuncDef, public Stmt {
  public:
    // methods inherited from FuncDef
    string getVar() override { return "arg"; }
    Stmt* getBody() override { return this; }

    // method inherited from Stmt
    void exec(Frame* ST) override {
      Value argument = ST->lookup(getVar());
      Value result = run(argument);
      ST->rebind("ret", result);
    }

    // this is the only method subclasses need to implement
    virtual Value run(Value arg) = 0;
};

/* Computes the square root of a given number, rounded down. */
class Sqrt :public Builtin {
  public:
    Value run(Value arg) {
      int x = arg.num();
      if (x < 0) {
        if (!error) {
          errout << "ERROR: No imaginary numbers in SPL" << endl;
          error = true;
        }
        return Value();
      }
      return Value(int(sqrt(x)));
    }
};

/* Given n, computes a random number from 1 up to n.
 * The generator is seeded once, randomly, when the builtin
 * is first declared.
 */
class Rand :public Builtin {
  private:
    // minstd_rand is provided by the C++ <random> library.
    // It's a simple and very fast pseudo-random number generator.
    minstd_rand gen;

  public:
    Rand() {
      // This seeds the random generator with a true-random number.
      random_device rd;
      gen.seed(rd());
    }

    Value run(Value arg) {
      int max = arg.num();
      if (max < 1) {
        if (!error) {
          errout << "ERROR: argument to rand must be a positive integer." << endl;
          error = true;
        }
        return Value(0);
      }
      // uniform_int_distribution is provided by the C++ <random> library.
      uniform_int_distribution<int> dist(1, max);
      return Value(dist(gen));
    }
};


/* This builtin returns the current time since the SI413 epoch, which is
 * August 20 at 0755.
 * If an integer argument is given, the difference from that time until
 * now is returned.
 */
class Time :public Builtin {
  private:
    time_t epoch;

  public:
    Time() {
      time_t curtime;
      time(&curtime);
      struct tm tmstr;
      localtime_r(&curtime, &tmstr);
      tmstr.tm_sec = 0;
      tmstr.tm_min = 55;
      tmstr.tm_hour = 7;
      tmstr.tm_mday = 1;
      tmstr.tm_mon = 7;
      tmstr.tm_isdst = 1;
      epoch = mktime(&tmstr);
    }

    Value run(Value arg) {
      time_t curtime;
      time(&curtime);
      int offset = 0;
      if (arg.getType() == NUM_T)
        offset = arg.num();
      int diff = static_cast<int>(difftime(curtime, epoch+offset));
      return Value(diff);
    }
};

/* A class of builtin functions to check whether a given value
 * has a certain type.
 */
class IsType :public Builtin {
  private:
    VType type;

  public:
    IsType(VType t) { type = t; }

    Value run(Value arg) {
      return Value(arg.getType() == type);
    }
};

/* Builtin function to display a list.
 * This is intricately tied to the specific implementations of car, cdr, cons in list.spl.
 */
class Display :public Builtin {
  private:
    const int ISCONS = 1000;
    const int GETCAR = 2001;
    const int GETCDR = 2002;

    // have to simulate the function call to do car, cdr, and cons!
    Value call(Value x, int msg) {
      Closure clos = x.func();
      Frame f(clos.env);
      f.bind(clos.lam->getVar(), Value(msg));
      f.bind("ret", Value());
      clos.lam->getBody()->exec(&f);
      return f.lookup("ret");
    }

  public:
    Value run(Value arg) {
      resout << "[";
      bool first = true;
      Value cur = arg;
      while (call(cur, ISCONS).tf()) {
        if (!first) resout << " ";
        call(cur, GETCAR).writeTo(resout);
        first = false;
        cur = call(cur, GETCDR);
      }
      resout << "]" << endl;
      return Value();
    }
};

class Frames :public Builtin {
  public:
    Value run(Value arg){
      //int size = Frame::len();
      //printf("%d\n", size);
      return Value(int(Frame::len()));
    }
};

#endif // BUILTIN_HPP
