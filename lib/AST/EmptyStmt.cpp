//
// Created by YANG Zehai on 2021/11/11.
//

#include "AST/EmptyStmt.h"

using namespace pur;
using namespace pur::ast;

EmptyStmt::EmptyStmt(const pars::Location& loc):
Stmt(ASTNodeType::kEmptyStmt, loc) {
  /* empty */
}

void EmptyStmt::Accept(Visitor& visitor) {
  visitor.VisitEmptyStmt(*this);
}
