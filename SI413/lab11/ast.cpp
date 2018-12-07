/* SI 413 Fall 2018
 * Lab 11
 * This file contains the implementations of longer methods in the
 * AST class hierarchy.
 * Brandon Sipes
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
string ArithOp::eval(Frame* ST, Context* con) {
  string l = left->eval(ST, con);
  string r = right->eval(ST, con);
  string dest = con->nextRegister();
  resout << "    " << dest << " = ";
  switch(op) {
    case ADD:
      resout << "add";
      break;
    case SUB:
      resout << "sub";
      break;
    case MUL:
      resout << "mul";
      break;
    case DIV:
      resout << "sdiv";
      break;
    default:
      // should never happen...
      errout << "Internal Error: Illegal arithmetic operator" << endl;
      exit(8);
  }
  resout << " i64 " << l << ", " << r << endl;
  return dest;
}

// Constructor for CompOp
CompOp::CompOp(Exp* l, Oper o, Exp* r) {
  op = o;
  left = l;
  right = r;
  ASTchild(left);
  ASTchild(right);
}

string CompOp::eval(Frame*ST, Context*con){
  string l = left->eval(ST, con);
  string r = right->eval(ST,con);
  string dest = con->nextRegister();
  resout << "    " << dest << " = icmp ";
  switch(op){
    case EQ:
      resout << "eq";
      break;
    case NE:
      resout << "ne";
      break;
    case LT:
      resout << "slt";
      break;
    case LE:
      resout << "sle";
      break;
    case GT:
      resout << "sgt";
      break;
    case GE:
      resout << "sge";
      break;
    default:
      //should never happen...
      errout << "Internal Error: Illegal Comparison operator" << endl;
      exit(9);
  }
  resout << " i64 " << l << ", " << r << endl;
  string dest2 = con->nextRegister();//May need to move this to the write
  resout << "    " << dest2 << " = zext i1 " << dest << " to i64" << endl;
  return dest2;
}


// Constructor for BoolOp
BoolOp::BoolOp(Exp* l, Oper o, Exp* r) {
  op = o;
  left = l;
  right = r;
  ASTchild(left);
  ASTchild(right);
}

string BoolOp::eval(Frame*ST, Context*con){
  string br = con->nextRegister();//branch for use in the phi
  resout << "    br label " << br << endl
    << "  " << br.replace(0,1,"") << ":" << endl;

  //do the left side,
  string l = left->eval(ST,con);
  string sc = con->nextRegister(); //short circuit
  string end = con->nextRegister();//end
  string other = con->nextRegister();//right side
  resout << "    " << sc << " = trunc i64 " << l << " to i1" << endl
    << "    br i1 " << sc << ", label ";
  //then branch operator dependant
  if(op == OR)
    resout << end << ", label " << other << endl;
  else 
    resout << other << ", label " << end << endl;

  //define right label
  resout << "  " << other.replace(0,1,"") << ":" << endl;
  string r = right->eval(ST,con);
  string rr = con->nextRegister(); //right result
  resout << "    " << rr << " = trunc i64 " << r << " to i1" << endl;
  resout << "    br label " << end << endl;

  //define end label
  string dest = con->nextRegister(); //result
  resout << "  " << end.replace(0,1,"") << ":" << endl
    << "    " << dest << " = phi i1 [ ";
  if(op == OR)
    resout << "true";
  else
    resout << "false";
  string dest2 = con->nextRegister(); //result
  resout << ", " << br.insert(0,"%") << " ], [ " << rr << ", " << other.insert(0,"%") << "]" << endl
    << "    " << dest2 << " = zext i1 " << dest << " to i64" << endl;
  return dest2;
}

// Constructor for IfStmt
IfStmt::IfStmt(Exp* e, Stmt* ib, Stmt* eb) {
  clause = e;
  ifblock = ib;
  elseblock = eb;
  ASTchild(clause);
  ASTchild(ifblock);
  ASTchild(elseblock);
}

// execute a write statement by calling printf
void Write::exec(Frame* ST, Context* con) {
  string r = val->eval(ST, con);
  resout << "    call i32(i8*,...) @printf("
    << "i8* getelementptr([5 x i8], [5 x i8]* @pfmt, i32 0, i32 0), "
    << "i64 " << r << ")" << endl;
  getNext()->exec(ST, con);
}

string Read::eval(Frame*ST, Context*con){
  string dest = con->nextRegister();
  resout << "    " << dest << " = alloca i64" << endl
    << "    call i32(i8*,...) @scanf("
    << "i8* getelementptr([3 x i8], [3 x i8]* @sfmt, i32 0, i32 0), "
    << "i64* " << dest << ")" << endl;
  string dest2 = con->nextRegister();
  resout << "    " << dest2 << " = load i64, i64* " << dest << endl;
  string dest3 = con->nextRegister();
  string dest4 = con->nextRegister();
  resout << "    " << dest3 << " = trunc i64 " << dest2 << " to i32" << endl
    << "    " << dest4 << " = sext i32 " << dest3 << " to i64" << endl;
  return dest4;
}
void NewStmt::exec(Frame* ST, Context* con){
  string l = lhs->getVal();
  string r = rhs->eval(ST, con);
  string dest = con->nextRegister();
  resout << "    " << dest << " = alloca i64" << endl
    << "    store i64 " << r << ", i64* " << dest << endl;//store value on stack at dest
  //add l to dest map to symbol table
  ST->bind(lhs->getVal(), dest);
  getNext()->exec(ST, con);
}

void Asn::exec(Frame* ST, Context* con){
  string l = lhs->getVal();
  string r = rhs->eval(ST, con);
  string name = ST->lookup(l);
  resout << "    store i64 " << r << ", i64* " << name << endl;//store value on stack at dest
  getNext()->exec(ST, con);
}

void IfStmt::exec(Frame* ST, Context* con){
  string test = clause->eval(ST,con); //Evaluate test
  string dest = con->nextRegister();
  string br1 = con->nextRegister();
  string br2 = con->nextRegister();
  string end = con->nextRegister();

  //truncate down to bool, then choose which label to go to
  resout << "    " << dest << " = trunc i64 " << test << " to i1" << endl
    << "    br i1 " << dest << ", label " << br1 << ", label " << br2 << endl
    << "  " << br1.replace(0,1,"") << ":" << endl;
  ifblock->exec(ST,con);
  resout << "    br label " << end << endl
    << "  " << br2.replace(0,1,"") << ":" << endl;
  elseblock->exec(ST,con);
  resout << "    br label " << end << endl
    << "  " << end.replace(0,1,"") << ":" << endl;
  getNext()->exec(ST,con);
}
void WhileStmt::exec(Frame* ST,Context*con){
  string dest = con->nextRegister();
  string wl = con->nextRegister(); //wl for while loop
  string wlTest = con->nextRegister();
  string end = con->nextRegister();
  resout << "    br label " << wlTest <<endl //Branch down to test
    << "  " << wl.replace(0,1,"") << ":" << endl;//while body
  wl.insert(0,"%");
  body->exec(ST,con); //body code
  resout << "    br label " << wlTest << endl //branch down to test
    << "  " << wlTest.replace(0,1,"") << ":" << endl; //test body

  string test = clause->eval(ST,con);//test code
  resout << "    " <<  dest << " = trunc i64 " << test << " to i1" << endl
    << "    br i1 " << dest << ", label " << wl << ", label " << end << endl
    << "  " << end.replace(0,1,"") << ":" << endl;

  getNext()->exec(ST,con);
}



