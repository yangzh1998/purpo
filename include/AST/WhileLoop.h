//
// Created by YANG Zehai on 2021/11/18.
//

#ifndef PUR_AST_WHILE_LOOP_H
#define PUR_AST_WHILE_LOOP_H

#include <memory>
#include "AST/Stmt.h"
#include "AST/Expr.h"
#include "AST/Block.h"

namespace pur {

namespace ast {

class WhileLoop : public Stmt {
public:
  WhileLoop(const pars::Location& location, Expr& cond, Block& block);
  Expr& GetCondition();
  Block& GetBlock();
  virtual void Accept(Visitor&) override;

private:
  std::unique_ptr<Expr> mCondition;
  std::unique_ptr<Block> mBlock;
}; // WhileLoop

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_WHILE_LOOP_H
