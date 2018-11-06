/* SI 413 Fall 2018
 * Lab 9
 * This file contains the implementations of longer methods in the
 * AST class hierarchy.
 * YOUR NAME HERE
 */

#include "ast.hpp"

// ArithOp constructor
ArithOp::ArithOp(Exp* l, Oper o, Exp* r) {
  op = o;
  left = l;
  right = r;
  ASTchild(left);
  ASTchild(right);
}

// Evaluates an arithmetic operation
Value ArithOp::eval(Frame* ST) {
  int l = left->eval(ST).num();
  int r = right->eval(ST).num();
  switch(op) {
    case ADD: return Value(l + r);
    case SUB: return Value(l - r);
    case MUL: return Value(l * r);
    case DIV:
      if (r != 0) return Value(l / r);
      else if (!error) {
        error = true;
        errout << "ERROR: Divide by zero" << endl;
      }
      break;
    default:
      // should never happen...
      errout << "Internal Error: Illegal arithmetic operator" << endl;
  }
  return Value();
}

// Constructor for CompOp
CompOp::CompOp(Exp* l, Oper o, Exp* r) {
  op = o;
  left = l;
  right = r;
  ASTchild(left);
  ASTchild(right);
}

// Constructor for BoolOp
BoolOp::BoolOp(Exp* l, Oper o, Exp* r) {
  op = o;
  left = l;
  right = r;
  ASTchild(left);
  ASTchild(right);
}

Value Funcall::eval(Frame* ST) {
  Closure func = funexp->eval(ST).func();
  Frame* lamenv = new Frame(func.env);
  lamenv->bind("ret",Value());
  lamenv->bind(func.lam->getVar(), arg->eval(ST));
  func.lam->getBody()->exec(lamenv);
  return lamenv->lookup("ret");
}
