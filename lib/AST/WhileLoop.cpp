//
// Created by YANG Zehai on 2021/11/18.
//

#include "AST/WhileLoop.h"

using namespace pur;
using namespace pur::ast;

WhileLoop::WhileLoop(const pars::Location& location, Expr& cond, Block& block):
Stmt(ASTNodeType::kWhileLoop, location), mCondition(&cond), mBlock(&block) {
  /* empty */
}

Expr& WhileLoop::GetCondition() {
  return *mCondition;
}

Block& WhileLoop::GetBlock() {
  return *mBlock;
}

void WhileLoop::Accept(Visitor& visitor) {
  visitor.VisitWhileLoop(*this);
}
