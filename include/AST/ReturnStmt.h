//
// Created by YANG Zehai on 2021/11/18.
//

#ifndef PUR_AST_RETURN_STMT_H
#define PUR_AST_RETURN_STMT_H

#include <memory>
#include "AST/Stmt.h"
#include "AST/Expr.h"

namespace pur {

namespace ast {

class ReturnStmt : public Stmt {
public:
  ReturnStmt(const pars::Location& location, Expr* expr);
  Expr* GetExpr();
  virtual void Accept(Visitor&) override;

private:
  std::unique_ptr<Expr> mExpr;
}; // ReturnStmt

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_RETURN_STMT_H
