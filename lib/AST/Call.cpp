//
// Created by YANG Zehai on 2021/11/24.
//

#include <utility>
#include "AST/Call.h"

using namespace pur;
using namespace pur::ast;

Call::Call(const pars::Location& location, std::deque<std::string>& funcPath,
           std::deque<std::unique_ptr<Expr>>& args):
Expr(ASTNodeType::kCall, location), mFuncPath(std::move(funcPath)),
mArgs(std::move(args)) {
  /* empty */
}

std::deque<std::string>& Call::GetFuncPath() {
  return mFuncPath;
}

std::deque<std::unique_ptr<Expr>>& Call::GetArgs() {
  return mArgs;
}

void Call::Accept(Visitor& visitor) {
  visitor.VisitCall(*this);
}
