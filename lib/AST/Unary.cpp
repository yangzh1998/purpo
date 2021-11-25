//
// Created by YANG Zehai on 2021/11/23.
//

#include "AST/Unary.h"

using namespace pur;
using namespace pur::ast;

Unary::Unary(const pars::Location& location, Expr& expr, UnaryOp op):
Expr(ASTNodeType::kUnary, location), mExpr(&expr), mOp(op) {
  /* empty */
}

Expr& Unary::GetExpr() {
  return *mExpr;
}

UnaryOp Unary::GetOp() const {
  return mOp;
}

void Unary::Accept(Visitor& visitor) {
  return visitor.VisitUnary(*this);
}