//
// Created by YANG Zehai on 2021/11/18.
//

#include "AST/CallStmt.h"

using namespace pur;
using namespace pur::ast;

CallStmt::CallStmt(const pars::Location& location, Expr& call):
Stmt(ASTNodeType::kCallStmt, location), mCall(&call) {
  /* empty */
}

Expr& CallStmt::GetCall() {
  return *mCall;
}

void CallStmt::Accept(Visitor& visitor) {
  visitor.VisitCallStmt(*this);
}

