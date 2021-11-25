//
// Created by YANG Zehai on 2021/11/18.
//

#ifndef PUR_AST_IF_STMT_H
#define PUR_AST_IF_STMT_H

#include <memory>
#include "AST/Stmt.h"
#include "AST/Expr.h"
#include "AST/Block.h"

namespace pur {

namespace ast {

class IfStmt : public Stmt {
public:
  IfStmt(const pars::Location& location, Expr& cond, Block& block,
         Block* branch);
  Expr& GetCondition();
  Block& GetBlock();
  Block* GetBranch();
  virtual void Accept(Visitor&) override;

private:
  std::unique_ptr<Expr> mCondition;
  std::unique_ptr<Block> mBlock;
  std::unique_ptr<Block> mBranch;
}; // IfStmt

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_IF_STMT_H
