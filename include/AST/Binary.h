//
// Created by YANG Zehai on 2021/11/22.
//

#ifndef PUR_AST_BINARY_H
#define PUR_AST_BINARY_H

#include <memory>
#include "AST/Expr.h"

namespace pur {

namespace ast {

enum class BinaryOp {
  kOr,
  kAnd,
  kAdd,
  kSub,
  kMul,
  kDiv,
  kMod,
  kEq,
  kNEq,
  kGt,
  kGEq,
  kLt,
  kLEq
}; // BinaryOp

class Binary : public Expr {
public:
  Binary(const pars::Location& location, Expr& left, Expr& right, BinaryOp op);
  Expr& GetLeft();
  Expr& GetRight();
  BinaryOp GetOp() const;
  virtual void Accept(Visitor&) override;

private:
  std::unique_ptr<Expr> mLeft;
  std::unique_ptr<Expr> mRight;
  BinaryOp mOp;
}; // Binary

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_BINARY_H
