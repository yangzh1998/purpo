//
// Created by YANG Zehai on 2021/11/23.
//

#ifndef PUR_AST_NULL_EXPR_H
#define PUR_AST_NULL_EXPR_H

#include "AST/Expr.h"

namespace pur {

namespace ast {

class NullExpr : public Expr {
public:
  NullExpr(const pars::Location& location);
  virtual void Accept(Visitor&) override;

};

// NullExpr

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_NULL_EXPR_H
