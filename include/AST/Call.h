//
// Created by YANG Zehai on 2021/11/24.
//

#ifndef PUR_AST_CALL_H
#define PUR_AST_CALL_H

#include <string>
#include <deque>
#include <memory>
#include "AST/Expr.h"

namespace pur {

namespace ast {

class Call : public Expr {
public:
  Call(const pars::Location& location, std::deque<std::string>& funcPath,
       std::deque<std::unique_ptr<Expr>>& args);
  std::deque<std::string>& GetFuncPath();
  std::deque<std::unique_ptr<Expr>>& GetArgs();
  virtual void Accept(Visitor&) override;

private:
  std::deque<std::string> mFuncPath;
  std::deque<std::unique_ptr<Expr>> mArgs;
}; // Call

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_CALL_H
