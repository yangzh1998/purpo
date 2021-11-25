//
// Created by YANG Zehai on 2021/11/18.
//

#include "AST/ReturnStmt.h"

using namespace pur;
using namespace pur::ast;

ReturnStmt::ReturnStmt(const pars::Location& location, Expr* expr):
Stmt(ASTNodeType::kReturnStmt, location), mExpr(expr) {
  /* empty */
}

Expr* ReturnStmt::GetExpr() {
  return mExpr.get();
}

void ReturnStmt::Accept(Visitor& visitor) {
  visitor.VisitReturnStmt(*this);
}