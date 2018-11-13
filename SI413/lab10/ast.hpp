/* SI 413 Fall 2018
 * Lab 10
 * This is a C++ header file for the AST class hierarchy.
 */

#ifndef AST_HPP
#define AST_HPP

#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#include "colorout.hpp"
#include "value.hpp"
#include "frame.hpp"

// Declare the output streams to use everywhere
extern colorout resout;
extern colorout errout;

// Global variable to indicate if an error has occurred.
extern bool error;

// Global variable to indicate there is a human typing at a keyboard
extern bool showPrompt;

// This enum type gives codes to the different kinds of operators.
// Basically, each oper below such as DIV becomes an integer constant.
enum Oper {
  ADD, SUB,
  MUL, DIV,
  LT, GT, LE, GE,
  EQ, NE,
  AND, OR, NOT
};

// These are forward declarations for the classes defined below.
// They show the class hierarchy.
class AST;
  class Stmt;
    class NullStmt;
    class Block;
    class IfStmt;
    class WhileStmt;
    class NewStmt;
    class Asn;
    class Write;
    class ExpStmt;
  class Exp;
    class Id;
    class Num;
    class BoolExp;
    class ArithOp;
    class CompOp;
    class BoolOp;
    class NegOp;
    class NotOp;
    class Read;
    class Lambda;
    class Funcall;

/* The AST class is the super-class for abstract syntax trees.
 * Every type of AST (or AST node) has its own subclass.
 */
class AST {
  private:
  protected:
    // These two protected fields determine the structure of the AST.
    vector<AST*> children;

    // Inserts a new AST node as a child of this one.
    void ASTchild(AST* child) { children.push_back(child); }

  public:
    /* Makes a new "empty" AST node. */
    AST() { }

    /* Deallocates memory for this AST note and its children. */
    virtual ~AST() {
      for (AST* child : children) delete child;
      children.clear();
    }
};

/* Every AST node that is not a Stmt is an Exp.
 * These represent actual computations that return something
 * (in particular, a Value object).
 */
class Exp :public AST {
  public:
    /* This is the method that must be overridden by all subclasses.
     * It should perform the computation specified by this node, and
     * return the resulting value that gets computed. */
    virtual Value eval(Frame* ST) = 0;
};

/* An identifier, i.e. variable or function name. */
class Id :public Exp {
  private:
    string val;

  public:
    // Constructor from a C-style string
    Id(const char* v) {
      val = v;
    }

    // Returns a reference to the stored string value.
    string& getVal() { return val; }

    // Note the Frame class is responsible for error checking.
    Value eval(Frame* ST) override { return ST->lookup(val); }
};

/* A literal number in the program. */
class Num :public Exp {
  private:
    int val;

  public:
    Num(int v) {
      val = v;
    }

    // To evaluate, just return the number!
    Value eval(Frame* ST) override { return Value(val); }
};

/* A literal boolean value like "true" or "false" */
class BoolExp :public Exp {
  private:
    bool val;

  public:
    BoolExp(bool v) {
      val = v;
    }

    // To evaluate, just return the bool
    Value eval(Frame* ST) override { return Value(val); }
};

/* A binary opration for arithmetic, like + or *. */
class ArithOp :public Exp {
  private:
    Oper op;
    Exp* left;
    Exp* right;

  public:
    ArithOp(Exp* l, Oper o, Exp* r);

    Value eval(Frame* ST) override; // this is implemented in ast.cpp
};

/* A binary operation for comparison, like < or !=. */
class CompOp :public Exp {
  private:
    Oper op;
    Exp* left;
    Exp* right;

  public:
    CompOp(Exp* l, Oper o, Exp* r);

    Value eval(Frame* ST) override {
      int l = left->eval(ST).num();
      int r = right->eval(ST).num();
      if (l < r)      return Value(op == LT || op == LE || op == NE);
      else if (l > r) return Value(op == GT || op == GE || op == NE);
      else            return Value(op == LE || op == GE || op == EQ);
    }
};

/* A binary operation for boolean logic, like "and". */
class BoolOp :public Exp {
  private:
    Oper op;
    Exp* left;
    Exp* right;

  public:
    BoolOp(Exp* l, Oper o, Exp* r);

    Value eval(Frame* ST) override {
      bool first = left->eval(ST).tf();
      // short-circuit check
      if ((first && op == OR) || (!first && op == AND)) {
        return Value(first);
      }
      else {
        // can't short-circuit, so return the result of the second part.
        return right->eval(ST);
      }
    }
};

/* This class represents a unary negation operation. */
class NegOp :public Exp {
  private:
    Exp* right;

  public:
    NegOp(Exp* r) {
      right = r;
      ASTchild(right);
    }

    Value eval(Frame* ST) override {
      return Value(- right->eval(ST).num());
    }
};

/* This class represents a unary "not" operation. */
class NotOp :public Exp {
  private:
    Exp* right;

  public:
    NotOp(Exp* r) {
      right = r;
      ASTchild(right);
    }

    Value eval(Frame* ST) override {
      return Value(! right->eval(ST).tf());
    }
};

/* A read expression. */
class Read :public Exp {
  public:
    Read() { }

    Value eval(Frame* ST) override {
      if (showPrompt) cerr << "read> ";
      int v;
      if (cin >> v) return Value(v);
      if (!error) {
        error = true;
        errout << "ERROR in read" << endl;
      }
      return Value();
    }
};

/* A Stmt is anything that can be evaluated at the top level such
 * as I/O, assignments, and control structures.
 * The last child of any statement is the next statement in sequence.
 */
class Stmt :public AST {
  private:
    // Pointer to the next statement in sequence, default null.
    Stmt* next = nullptr;

  public:
    // Default constructor. Note that the setNext method must be
    // called by the parser at some point after construction.
    Stmt () { }

    // Getter and setter for the next statement in sequence.
    Stmt* getNext() { return next; }
    void setNext(Stmt* nextStmt) {
      if (next != nullptr) {
        errout << "Unexpected parser error: trying to set next, but next already set!" << endl;
        delete next;
        children.pop_back();
      }
      children.push_back(nextStmt);
      next = nextStmt;
    }

    /* This is the command that must be implemented everywhere to
     * execute this Stmt - that is, do whatever it is that this statement
     * says to do. */
    virtual void exec(Frame* ST) = 0;
};

/* This class is necessary to terminate a sequence of statements. */
class NullStmt :public Stmt {
  public:
    NullStmt() { }

    // Nothing to execute!
    void exec(Frame* ST) override { }
};

/* This is a statement for a block of code, i.e., code enclosed
 * in curly braces { and }.
 * Eventually, this is where scopes will begin and end.
 */
class Block :public Stmt {
  private:
    Stmt* body;

  public:
    Block(Stmt* b) {
      body = b;
      ASTchild(body);
    }

    void exec(Frame* ST) override {
      body->exec(new Frame(ST));
      getNext()->exec(ST);
    }
};

/* This class is for "if" AND "ifelse" statements. */
class IfStmt :public Stmt {
  private:
    Exp* clause;
    Stmt* ifblock;
    Stmt* elseblock;

  public:
    IfStmt(Exp* e, Stmt* ib, Stmt* eb) {
      clause = e;
      ifblock = ib;
      elseblock = eb;
      ASTchild(clause);
      ASTchild(ifblock);
      ASTchild(elseblock);
    }

    void exec(Frame* ST) override {
      if (clause->eval(ST).tf()) ifblock->exec(ST);
      else elseblock->exec(ST);
      getNext()->exec(ST);
    }
};

/* Class for while statements. */
class WhileStmt :public Stmt {
  private:
    Exp* clause;
    Stmt* body;

  public:
    WhileStmt(Exp* c, Stmt* b) {
      clause = c;
      body = b;
      ASTchild(clause);
      ASTchild(body);
    }

    void exec(Frame* ST) override {
      while (clause->eval(ST).tf()) {
        body->exec(ST);
      }
      getNext()->exec(ST);
    }
};

/* A "new" statement creates a new binding of the variable to the
 * stated value.  */
class NewStmt :public Stmt {
  private:
    Id* lhs;
    Exp* rhs;

  public:
    NewStmt(Id* l, Exp* r) {
      lhs = l;
      rhs = r;
      ASTchild(lhs);
      ASTchild(rhs);
    }

    void exec(Frame* ST) override {
      ST->bind(lhs->getVal(), rhs->eval(ST));
      getNext()->exec(ST);
    }
};

/* An assignment statement. This represents a RE-binding in the symbol table. */
class Asn :public Stmt {
  private:
    Id* lhs;
    Exp* rhs;

  public:
    Asn(Id* l, Exp* r) {
      lhs = l;
      rhs = r;
      ASTchild(lhs);
      ASTchild(rhs);
    }

    void exec(Frame* ST) override {
      ST->rebind(lhs->getVal(), rhs->eval(ST));
      getNext()->exec(ST);
    }
};

/* A write statement. */
class Write :public Stmt {
  private:
    Exp* val;

  public:
    Write(Exp* v) {
      val = v;
      ASTchild(val);
    }

    void exec(Frame* ST) override {
      Value res = val->eval(ST);
      if (!error) {
        res.writeTo(resout);
        resout << endl;
      }
      getNext()->exec(ST);
    }
};

/* A debugging statement embedded in the code. */
class Debug :public Stmt {
  private:
    string msg;

  public:
    Debug(const string& themsg) {
      msg = themsg;
    }

    void exec(Frame* ST) override {
      if (!error) {
        resout << msg << endl;
      }
      getNext()->exec(ST);
    }
};

/* A single expression as a statement. */
class ExpStmt :public Stmt {
  private:
    Exp* body;

  public:
    ExpStmt(Exp* b) {
      body = b;
      ASTchild(body);
    }

    void exec(Frame* ST) override {
      body->eval(ST);
      getNext()->exec(ST);
    }
};

/* A lambda expression consists of a parameter name and a body. */
class Lambda :public Exp, public FuncDef {
  private:
    Id* var;
    Stmt* body;

  public:
    Lambda(Id* v, Stmt* b) {
      var = v;
      body = b;
      ASTchild(var);
      ASTchild(body);
    }

    // These getter methods are necessary to support actually calling
    // the lambda sometime after it gets created.
    string getVar() { return var->getVal(); }
    Stmt* getBody() { return body; }

    Value eval(Frame* ST) override {
      return Value(this, ST);
    }
};

/* A function call consists of the function name, and the actual argument.
 * Note that all functions are unary. */
class Funcall :public Exp {
  private:
    Exp* funexp;
    Exp* arg;

  public:
    Funcall(Exp* f, Exp* a) {
      funexp = f;
      arg = a;
      ASTchild(funexp);
      ASTchild(arg);
    }

    Value eval(Frame* ST) override;
};

#endif //AST_HPP
