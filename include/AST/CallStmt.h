//
// Created by YANG Zehai on 2021/11/18.
//

#ifndef PUR_AST_CALL_STMT_H
#define PUR_AST_CALL_STMT_H

#include <memory>
#include "AST/Stmt.h"
#include "AST/Expr.h"

namespace pur {

namespace ast {

class CallStmt : public Stmt {
public:
  CallStmt(const pars::Location& location, Expr& call);
  Expr& GetCall();
  virtual void Accept(Visitor&) override;

private:
  std::unique_ptr<Expr> mCall;
}; // CallStmt

} // namespace pur::ast

} // namespace pur


#endif // PUR_AST_CALL_STMT_H
