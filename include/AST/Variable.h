//
// Created by YANG Zehai on 2021/11/24.
//

#ifndef PUR_AST_VARIABLE_H
#define PUR_AST_VARIABLE_H

#include <string>
#include <deque>
#include "AST/Expr.h"

namespace pur {

namespace ast {

class Variable : public Expr {
public:
  Variable(const pars::Location& location, std::deque<std::string>& varPath);
  std::deque<std::string>& GetVarPath();
  virtual void Accept(Visitor&) override;

private:
  std::deque<std::string> mVarPath;
}; // Variable

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_VARIABLE_H
