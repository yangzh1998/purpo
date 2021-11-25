//
// Created by YANG Zehai on 2021/11/18.
//

#include "AST/ForLoop.h"

using namespace pur;
using namespace pur::ast;

ForLoop::ForLoop(const pars::Location& location,
                 std::deque<std::string>& paramNames, Expr& expr,
                 Block& block):
                 Stmt(ASTNodeType::kForLoop, location), mParamNames(paramNames),
                 mExpr(&expr), mBlock(&block) {
  /* empty */
}

std::deque<std::string>& ForLoop::GetParamNames() {
  return mParamNames;
}

Expr& ForLoop::GetExpr() {
  return *mExpr;
}

Block& ForLoop::GetBlock() {
  return *mBlock;
}

void ForLoop::Accept(Visitor& visitor) {
  visitor.VisitForLoop(*this);
}
