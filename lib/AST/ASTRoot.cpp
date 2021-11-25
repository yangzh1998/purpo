//
// Created by YANG Zehai on 2021/3/15.
//

#include <utility>
#include "AST/ASTRoot.h"

using namespace pur;
using namespace pur::ast;

ASTRoot::ASTRoot(const pars::Location& loc, const std::string& filePath,
                 std::deque<std::unique_ptr<ASTNode>>& declarations):
ASTNode(ASTNodeType::kASTRoot, loc), mFilePath(filePath),
mDeclarations(std::move(declarations)) {
  /* empty */
}

const std::string& ASTRoot::GetFilePath() const {
  return mFilePath;
}

std::deque<std::unique_ptr<ASTNode>>& ASTRoot::GetDeclarations() {
  return mDeclarations;
}

void ASTRoot::Accept(Visitor& visitor) {
  visitor.VisitASTRoot(*this);
}
