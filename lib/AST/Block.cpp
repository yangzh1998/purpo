//
// Created by YANG Zehai on 2021/11/11.
//

#include <utility>
#include "AST/Block.h"

using namespace pur;
using namespace pur::ast;

Block::Block(const pars::Location& l, std::deque<std::unique_ptr<Stmt>>& s):
Stmt(ASTNodeType::kBlock, l), mStmts(std::move(s)) {
  /* empty */
}

std::deque<std::unique_ptr<Stmt>>& Block::GetStmts() {
  return mStmts;
}

void Block::Accept(Visitor& visitor) {
  visitor.VisitBlock(*this);
}

