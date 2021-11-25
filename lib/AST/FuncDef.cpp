//
// Created by YANG Zehai on 2021/11/11.
//

#include "AST/FuncDef.h"

using namespace pur;
using namespace pur::ast;

FuncDef::FuncDef(const pars::Location& loc, const std::string& funcName,
                 std::deque<std::string>& paramNames, Block& block):
                 ASTNode(ASTNodeType::kFuncDef, loc), mFuncName(funcName),
                 mParamNames(paramNames), mBlock(&block) {
  /* empty */
}

const std::string& FuncDef::GetFuncName() const {
  return mFuncName;
}

std::deque<std::string>& FuncDef::GetParamNames() {
  return mParamNames;
}

Block& FuncDef::GetBlock() {
  return *mBlock;
}

void FuncDef::Accept(Visitor& visitor) {
  visitor.VisitFuncDef(*this);
}
