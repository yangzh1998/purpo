//
// Created by YANG Zehai on 2021/11/10.
//

#ifndef PUR_AST_BLOCK_H
#define PUR_AST_BLOCK_H

#include <memory>
#include <deque>
#include "AST/Stmt.h"

namespace pur {

namespace ast {

class Block : public Stmt {
public:
  Block(const pars::Location& loc, std::deque<std::unique_ptr<Stmt>>& stmts);
  std::deque<std::unique_ptr<Stmt>>& GetStmts();
  virtual void Accept(Visitor&) override;

private:
  std::deque<std::unique_ptr<Stmt>> mStmts;
}; // Block

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_BLOCK_H
