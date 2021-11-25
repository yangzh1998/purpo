//
// Created by YANG Zehai on 2021/11/24.
//

#ifndef PUR_AST_INDEX_VISIT_H
#define PUR_AST_INDEX_VISIT_H

#include <memory>
#include "AST/Expr.h"

namespace pur {

namespace ast {

class IndexVisit : public Expr {
public:
  IndexVisit(const pars::Location& location, Expr& index);
  void SetOwner(Expr& owner);
  Expr& GetOwner();
  Expr& GetIndex();
  virtual void Accept(Visitor&) override;

private:
  std::unique_ptr<Expr> mOwner;
  std::unique_ptr<Expr> mIndex;
}; // IndexVisit

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_INDEX_VISIT_H
