//
// Created by YANG Zehai on 2021/11/11.
//

#include "AST/Continue.h"

using namespace pur;
using namespace pur::ast;

Continue::Continue(const pars::Location& loc):
Stmt(ASTNodeType::kContinue, loc) {
  /* empty */
}

void Continue::Accept(Visitor& visitor) {
  visitor.VisitContinue(*this);
}
