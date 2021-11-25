//
// Created by YANG Zehai on 2021/11/22.
//

#ifndef PUR_AST_UNARY_H
#define PUR_AST_UNARY_H

#include <memory>
#include "AST/Expr.h"

namespace pur {

namespace ast {

enum class UnaryOp {
  kNot,
  kNeg
}; // UnaryOp

class Unary : public Expr {
public:
  Unary(const pars::Location& location, Expr& expr, UnaryOp op);
  Expr& GetExpr();
  UnaryOp GetOp() const;
  virtual void Accept(Visitor&) override;

private:
  std::unique_ptr<Expr> mExpr;
  UnaryOp mOp;
}; // Unary

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_UNARY_H
