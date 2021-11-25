//
// Created by YANG Zehai on 2021/11/11.
//

#ifndef PUR_AST_CONTINUE_H
#define PUR_AST_CONTINUE_H

#include "AST/Stmt.h"

namespace pur {

namespace ast {

class Continue : public Stmt {
public:
  explicit Continue(const pars::Location& loc);
  virtual void Accept(Visitor&) override;
}; // Continue

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_CONTINUE_H
