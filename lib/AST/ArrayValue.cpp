//
// Created by YANG Zehai on 2021/11/22.
//

#include "AST/ArrayValue.h"

using namespace pur;
using namespace pur::ast;

ArrayValue::ArrayValue(const pars::Location& location,
                       std::deque<std::unique_ptr<Expr>>& elements):
Expr(ASTNodeType::kArrayValue, location), mElements(std::move(elements)){
  /* empty */
}

std::deque<std::unique_ptr<Expr>>& ArrayValue::GetElements() {
  return mElements;
}

void ArrayValue::Accept(Visitor& visitor) {
  visitor.VisitArrayValue(*this);
}
