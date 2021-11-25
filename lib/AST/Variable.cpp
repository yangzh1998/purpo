//
// Created by YANG Zehai on 2021/11/24.
//

#include <utility>
#include "AST/Variable.h"

using namespace pur;
using namespace pur::ast;

Variable::Variable(const pars::Location& location,
                   std::deque<std::string>& varPath):
Expr(ASTNodeType::kVariable, location), mVarPath(std::move(varPath)) {
  /* empty */
}

std::deque<std::string>& Variable::GetVarPath() {
  return mVarPath;
}

void Variable::Accept(Visitor& visitor) {
  visitor.VisitVariable(*this);
}

