//
// Created by YANG Zehai on 2021/11/11.
//

#include "AST/Break.h"

using namespace pur;
using namespace pur::ast;

Break::Break(const pars::Location& loc): Stmt(ASTNodeType::kBreak, loc) {
  /* empty */
}

void Break::Accept(Visitor& visitor) {
  visitor.VisitBreak(*this);
}
