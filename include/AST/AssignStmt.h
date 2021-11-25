//
// Created by YANG Zehai on 2021/11/18.
//

#ifndef PUR_AST_EXE_STMT_H
#define PUR_AST_EXE_STMT_H

#include <memory>
#include "AST/Stmt.h"
#include "AST/Expr.h"

namespace pur {

namespace ast {

enum class AssignOp {
  kDefault,
  kAdd,
  kSub,
  kMul,
  kDiv,
  kMod
}; // AssignOp

class AssignStmt : public Stmt {
public:
  AssignStmt(const pars::Location& location, Expr& left, int op, Expr& right);
  Expr& GetLeft();
  Expr& GetRight();
  AssignOp GetAssignOp() const;
  virtual void Accept(Visitor&) override;

private:
  std::unique_ptr<Expr> mLeft;
  std::unique_ptr<Expr> mRight;
  AssignOp mAssignOp;
}; // AssignStmt

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_EXE_STMT_H
