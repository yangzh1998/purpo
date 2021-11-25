//
// Created by YANG Zehai on 2021/11/11.
//

#ifndef PUR_AST_EMPTY_STMT_H
#define PUR_AST_EMPTY_STMT_H

#include "AST/Stmt.h"

namespace pur {

namespace ast {

class EmptyStmt : public Stmt {
public:
  explicit EmptyStmt(const pars::Location& loc);
  virtual void Accept(Visitor&) override;
}; // EmptyStmt

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_EMPTY_STMT_H
