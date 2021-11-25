//
// Created by YANG Zehai on 2021/3/1.
//

#ifndef PUR_PARS_SEMANTIC_VALUE_H
#define PUR_PARS_SEMANTIC_VALUE_H

#include <cstdint>
#include <string>
#include <deque>
#include <memory>
#include <utility>
#include "parser/Location.h"
#include "AST/ASTRoot.h"
#include "AST/Stmt.h"
#include "AST/Expr.h"
#include "AST/Pair.h"
#include "AST/Binary.h"

namespace pur {

namespace pars {

struct SemanticValue {
  Location mLocation;
  std::string mIdentifier;
  std::string mStrConst;
  std::int64_t mI61Const;
  double mF61Const;

  ast::ASTRoot* mASTRoot;
  std::deque<std::unique_ptr<ast::ASTNode>>* mDeclarations;
  ast::ASTNode* mDeclaration;
  std::deque<std::string>* mIdentList;
  ast::Stmt* mStmt;
  std::deque<std::unique_ptr<ast::Stmt>>* mStmtList;
  ast::Expr* mExpr;
  std::deque<std::unique_ptr<ast::Expr>>* mExprList;
  ast::Pair* mPair;
  std::deque<std::unique_ptr<ast::Pair>>* mPairList;
  std::deque<Location>* mLocList;
  std::deque<ast::BinaryOp>* mBinaryOps;
}; // SemanticValue

} // namespace pur::pars

} // namespace pur

#endif // PUR_PARS_SEMANTIC_VALUE_H
