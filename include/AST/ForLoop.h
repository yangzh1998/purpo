//
// Created by YANG Zehai on 2021/11/18.
//

#ifndef PUR_AST_FOR_LOOP_H
#define PUR_AST_FOR_LOOP_H

#include <deque>
#include <string>
#include <memory>
#include "AST/Stmt.h"
#include "AST/Expr.h"
#include "AST/Block.h"

namespace pur {

namespace ast {

class ForLoop : public Stmt {
public:
  ForLoop(const pars::Location& location, std::deque<std::string>& paramNames,
          Expr& expr, Block& block);
  std::deque<std::string>& GetParamNames();
  Expr& GetExpr();
  Block& GetBlock();
  virtual void Accept(Visitor&) override;

private:
  std::deque<std::string> mParamNames;
  std::unique_ptr<Expr> mExpr;
  std::unique_ptr<Block> mBlock;
}; // ForLoop

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_FOR_LOOP_H
