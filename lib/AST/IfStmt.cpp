//
// Created by YANG Zehai on 2021/11/18.
//

#include "AST/IfStmt.h"

using namespace pur;
using namespace pur::ast;

IfStmt::IfStmt(const pars::Location& location, Expr& cond, Block& block,
               Block* branch):
               Stmt(ASTNodeType::kIfStmt, location), mCondition(&cond),
               mBlock(&block), mBranch(branch) {
  /* empty */
}

Expr& IfStmt::GetCondition() {
  return *mCondition;
}

Block& IfStmt::GetBlock() {
  return *mBlock;
}

Block* IfStmt::GetBranch() {
  return mBranch.get();
}

void IfStmt::Accept(Visitor& visitor) {
  visitor.VisitIfStmt(*this);
}