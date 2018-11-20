/* SI 413 Fall 2018
 * Lab 11
 * This is a C++ header file for the AST class hierarchy.
 * YOUR NAME HERE
 */

#ifndef AST_HPP
#define AST_HPP

#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <typeinfo>
#include "splc.hpp"
#include "frame.hpp"

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
     * It should emit LLVM code to evaluate this expresion, and return
     * a string for the LLVM value that will hold the result.
     */
    virtual string eval(Frame* ST, Context* con) {
      errout << "ERROR: eval not yet implemented in class " << typeid(*this).name() << endl;
      exit(3);
    }
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
};

/* A literal number in the program. */
class Num :public Exp {
  private:
    int val;

  public:
    Num(int v) {
      val = v;
    }

    // to evaluate, we can return a literal string representation of the number
    string eval(Frame* ST, Context* con) override {
      return to_string(val);
    }
};

/* A literal boolean value like "true" or "false" */
class BoolExp :public Exp {
  private:
    bool val;

  public:
    BoolExp(bool v) {
      val = v;
    }

    //string eval(Frame*ST, Context*con) override {
    //}

};

/* A binary opration for arithmetic, like + or *. */
class ArithOp :public Exp {
  private:
    Oper op;
    Exp* left;
    Exp* right;

  public:
    ArithOp(Exp* l, Oper o, Exp* r);

    string eval(Frame* ST, Context* con) override; // this is implemented in ast.cpp
};

/* A binary operation for comparison, like < or !=. */
class CompOp :public Exp {
  private:
    Oper op;
    Exp* left;
    Exp* right;

  public:
    CompOp(Exp* l, Oper o, Exp* r);

    string eval(Frame* ST, Context* con) override;
};

/* A binary operation for boolean logic, like "and". */
class BoolOp :public Exp {
  private:
    Oper op;
    Exp* left;
    Exp* right;

  public:
    BoolOp(Exp* l, Oper o, Exp* r);

    string eval(Frame* ST, Context* con) override;
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
    
    string eval(Frame*ST,Context*con) override {
      string r = right->eval(ST,con);
      string dest = con->nextRegister();
      resout << "    " << dest << " = ";
      resout << " sub i64 0, " << r << endl;
      return dest;
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

    string eval(Frame*ST,Context*con) override {
      string r = right->eval(ST,con);
      string dest = con->nextRegister();
      resout << "    " << dest << " NOT DONE" << endl;//FIXME
      return dest;
    }
};

/* A read expression. */
class Read :public Exp {
  public:
    Read() { }

    string eval(Frame* ST, Context* con) override;

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
     * write the LLVM code to execute this Stmt.
     */
    virtual void exec(Frame* ST, Context* con) {
      errout << "ERROR: exec not yet implemented in class " << typeid(*this).name() << endl;
      exit(3);
    }
};

/* This class is necessary to terminate a sequence of statements. */
class NullStmt :public Stmt {
  public:
    NullStmt() { }

    // Nothing to execute!
    void exec(Frame* ST, Context* con) override { }
};

/* This is a statement for a block of code, i.e., code enclosed
 * in curly braces { and }.
 */
class Block :public Stmt {
  private:
    Stmt* body;

  public:
    Block(Stmt* b) {
      body = b;
      ASTchild(body);
    }

    //void exec(Frame*ST,Context*con){//FIXME
    //  body->exec(new Frame(ST));
    //  getNext()->exec(ST,con);
    //}
};

/* This class is for "if" AND "ifelse" statements. */
class IfStmt :public Stmt {
  private:
    Exp* clause;
    Stmt* ifblock;
    Stmt* elseblock;

  public:
    IfStmt(Exp* e, Stmt* ib, Stmt* eb);
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

    void exec(Frame* ST, Context* con) override; // implemented in ast.cpp
};

/* A debugging statement embedded in the code. */
class Debug :public Stmt {
  private:
    string msg;

  public:
    Debug(const string& themsg) {
      msg = themsg;
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
};

/* A lambda expression consists of a parameter name and a body. */
class Lambda :public Exp {
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
};

#endif //AST_HPP
