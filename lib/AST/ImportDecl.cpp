//
// Created by YANG Zehai on 2021/3/18.
//

#include "AST/ImportDecl.h"

using namespace pur;
using namespace pur::ast;

ImportDecl::ImportDecl(const pars::Location& loc,
                       std::deque<std::string>& identList,
                       const std::string& alias):
ASTNode(ASTNodeType::kImportDecl, loc), mModuleName(std::move(identList)),
mAlias(alias) {
  /* empty */
}

std::deque<std::string>& ImportDecl::GetModuleName() {
  return mModuleName;
}

const std::string& ImportDecl::GetAlias() const {
  return mAlias;
}

void ImportDecl::Accept(Visitor& visitor) {
  visitor.VisitImportDecl(*this);
}
