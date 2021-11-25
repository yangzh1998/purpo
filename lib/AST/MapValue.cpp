//
// Created by YANG Zehai on 2021/11/22.
//

#include "AST/MapValue.h"

using namespace pur;
using namespace pur::ast;

MapValue::MapValue(const pars::Location& location,
                   std::deque<std::unique_ptr<Pair>>& pairs):
Expr(ASTNodeType::kMapValue, location), mPairs(std::move(pairs)) {
  /* empty */
}

std::deque<std::unique_ptr<Pair>>& MapValue::GetPairs() {
  return mPairs;
}

void MapValue::Accept(Visitor& visitor) {
  visitor.VisitMapValue(*this);
}
