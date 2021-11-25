//
// Created by YANG Zehai on 2021/11/24.
//

#include "AST/RangeVisit.h"

using namespace pur;
using namespace pur::ast;

RangeVisit::RangeVisit(const pars::Location& location, Expr& begin, Expr& end):
Expr(ASTNodeType::kRangeVisit, location), mBegin(&begin), mEnd(&end) {
  /* empty */
}

Expr& RangeVisit::GetOwner() {
  return *mOwner;
}

Expr& RangeVisit::GetBegin() {
  return *mBegin;
}

Expr& RangeVisit::GetEnd() {
  return *mEnd;
}

void RangeVisit::Accept(Visitor& visitor) {
  visitor.VisitRangeVisit(*this);
}

void RangeVisit::SetOwner(Expr& owner) {
  mOwner.reset(&owner);
}
