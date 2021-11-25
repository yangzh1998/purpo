//
// Created by YANG Zehai on 2021/3/19.
//

#include "AST/GlobalVarDecl.h"

using namespace pur;
using namespace pur::ast;

GlobalVarDecl::GlobalVarDecl(const pars::Location& loc,
                             const std::string& name):
ASTNode(ASTNodeType::kGlobalVarDecl, loc), mVarName(name) {
  /* empty */
}

const std::string& GlobalVarDecl::GetVarName() const {
  return mVarName;
}

void GlobalVarDecl::Accept(Visitor& visitor) {
  visitor.VisitGlobalVarDecl(*this);
}
