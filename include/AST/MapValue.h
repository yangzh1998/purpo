//
// Created by YANG Zehai on 2021/11/22.
//

#ifndef PUR_AST_MAP_VALUE_H
#define PUR_AST_MAP_VALUE_H

#include <deque>
#include <memory>
#include "AST/Expr.h"
#include "AST/Pair.h"

namespace pur {

namespace ast {

class MapValue : public Expr {
public:
  MapValue(const pars::Location& location,
           std::deque<std::unique_ptr<Pair>>& pairs);
  std::deque<std::unique_ptr<Pair>>& GetPairs();
  virtual void Accept(Visitor&) override;

private:
  std::deque<std::unique_ptr<Pair>> mPairs;
}; // MapValue

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_MAP_VALUE_H
