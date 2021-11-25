//
// Created by YANG Zehai on 2021/11/23.
//

#include "AST/Binary.h"

using namespace pur;
using namespace pur::ast;

Binary::Binary(const pars::Location& location, Expr& left, Expr& right,
               BinaryOp op): Expr(ASTNodeType::kBinary, location),
               mLeft(&left), mRight(&right), mOp(op) {
  /* empty */
}

Expr& Binary::GetLeft() {
  return *mLeft;
}

Expr& Binary::GetRight() {
  return *mRight;
}

BinaryOp Binary::GetOp() const {
  return mOp;
}

void Binary::Accept(Visitor& visitor) {
  return visitor.VisitBinary(*this);
}


