//
// Created by YANG Zehai on 2021/11/23.
//

#include "AST/NullExpr.h"

using namespace pur;
using namespace pur::ast;


NullExpr::NullExpr(const pars::Location& location):
Expr(ASTNodeType::kNullExpr, location) {
  /* empty */
}

void NullExpr::Accept(Visitor& visitor) {
  visitor.VisitNullExpr(*this);
}
