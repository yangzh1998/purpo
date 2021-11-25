//
// Created by YANG Zehai on 2021/3/15.
//

#include "AST/ASTNode.h"

using namespace pur;
using namespace pur::ast;

ASTNode::ASTNode(ASTNodeType ASTNodeType, const pars::Location& location):
mASTNodeType(ASTNodeType), mLocation(location) {
  /* empty */
}

ASTNode::~ASTNode() {
  /* empty */
}

ASTNodeType ASTNode::GetASTNodeType() const {
  return mASTNodeType;
}

const pars::Location& ASTNode::GetLocation() const {
  return mLocation;
}

#include "AST/Stmt.h"
Stmt::Stmt(ASTNodeType ASTNodeType, const pars::Location& location):
ASTNode(ASTNodeType, location) {
  /* empty */
}

#include "AST/Expr.h"
Expr::Expr(ASTNodeType ASTNodeType, const pars::Location& location):
ASTNode(ASTNodeType, location) {
  /* empty */
}
