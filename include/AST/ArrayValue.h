//
// Created by YANG Zehai on 2021/11/22.
//

#ifndef PUR_AST_ARRAY_VALUE_H
#define PUR_AST_ARRAY_VALUE_H

#include <deque>
#include <memory>
#include "AST/Expr.h"

namespace pur {

namespace ast {

class ArrayValue : public Expr {
public:
  ArrayValue(const pars::Location& location,
             std::deque<std::unique_ptr<Expr>>& elements);
  std::deque<std::unique_ptr<Expr>>& GetElements();
  virtual void Accept(Visitor&) override;

private:
  std::deque<std::unique_ptr<Expr>> mElements;
}; // ArrayValue

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_ARRAY_VALUE_H
