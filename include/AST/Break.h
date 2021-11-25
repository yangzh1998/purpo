//
// Created by YANG Zehai on 2021/11/11.
//

#ifndef PUR_AST_BREAK_H
#define PUR_AST_BREAK_H

#include "AST/Stmt.h"

namespace pur {

namespace ast {

class Break : public Stmt {
public:
  explicit Break(const pars::Location& loc);
  virtual void Accept(Visitor&) override;
}; // Break

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_BREAK_H
