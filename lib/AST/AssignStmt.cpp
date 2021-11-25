//
// Created by YANG Zehai on 2021/11/18.
//

#include <cassert>
#include "AST/AssignStmt.h"
#include "parser/Token.h"

using namespace pur;
using namespace pur::ast;

AssignStmt::AssignStmt(const pars::Location& location, Expr& left, int op,
                       Expr& right):
Stmt(ASTNodeType::kAssignStmt, location), mLeft(&left), mRight(&right) {
  switch (op) {
    case '=':
      mAssignOp = AssignOp::kDefault;
      break;
    case pars::kAddAssign:
      mAssignOp = AssignOp::kAdd;
      break;
    case pars::kSubAssign:
      mAssignOp = AssignOp::kSub;
      break;
    case pars::kMulAssign:
      mAssignOp = AssignOp::kMul;
      break;
    case pars::kDivAssign:
      mAssignOp = AssignOp::kDiv;
      break;
    case pars::kModAssign:
      mAssignOp = AssignOp::kMod;
      break;
    default:
      assert(false);
  }
}

Expr& AssignStmt::GetLeft() {
  return *mLeft;
}

Expr& AssignStmt::GetRight() {
  return *mRight;
}

AssignOp AssignStmt::GetAssignOp() const {
  return mAssignOp;
}

void AssignStmt::Accept(Visitor& visitor) {
  visitor.VisitAssignStmt(*this);
}
