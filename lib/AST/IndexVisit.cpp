//
// Created by YANG Zehai on 2021/11/24.
//

#include "AST/IndexVisit.h"

using namespace pur;
using namespace pur::ast;

IndexVisit::IndexVisit(const pars::Location& location, Expr& index):
Expr(ASTNodeType::kIndexVisit, location), mIndex(&index) {
  /* empty */
}

Expr& IndexVisit::GetOwner() {
  return *mOwner;
}

Expr& IndexVisit::GetIndex() {
  return *mIndex;
}

void IndexVisit::Accept(Visitor& visitor) {
  visitor.VisitIndexVisit(*this);
}

void IndexVisit::SetOwner(Expr& owner) {
  mOwner.reset(&owner);
}
