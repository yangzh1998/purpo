//
// Created by YANG Zehai on 2021/11/24.
//

#ifndef PUR_AST_RANGE_VISIT_H
#define PUR_AST_RANGE_VISIT_H

#include <memory>
#include "AST/Expr.h"

namespace pur {

namespace ast {

class RangeVisit : public Expr {
public:
  RangeVisit(const pars::Location& location, Expr& begin, Expr& end);
  void SetOwner(Expr& owner);
  Expr& GetOwner();
  Expr& GetBegin();
  Expr& GetEnd();
  virtual void Accept(Visitor&) override;

private:
  std::unique_ptr<Expr> mOwner;
  std::unique_ptr<Expr> mBegin;
  std::unique_ptr<Expr> mEnd;
}; // RangeVisit

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_RANGE_VISIT_H

