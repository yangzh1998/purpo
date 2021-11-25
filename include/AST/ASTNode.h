//
// Created by YANG Zehai on 2021/3/15.
//

#ifndef PUR_AST_AST_NODE_H
#define PUR_AST_AST_NODE_H

#include "parser/Location.h"
#include "AST/Visitor.h"

#ifndef ABSTRACT
#define ABSTRACT
#endif // ABSTRACT

namespace pur {

namespace ast {

enum class ASTNodeType {
  kASTRoot,
  kImportDecl,
  kGlobalVarDecl,
  kFuncDef,
  kBlock,
  kForLoop,
  kWhileLoop,
  kIfStmt,
  kBreak,
  kContinue,
  kReturnStmt,
  kEmptyStmt,
  kAssignStmt,
  kCallStmt,
  kI61Literal,
  kF61Literal,
  kStrLiteral,
  kBoolLiteral,
  kArrayValue,
  kMapValue,
  kNullExpr,
  kBinary,
  kUnary,
  kIndexVisit,
  kRangeVisit,
  kCall,
  kVariable
};

ABSTRACT class ASTNode {
public:
  ASTNode(ASTNodeType ASTNodeType, const pars::Location& location);
  virtual ~ASTNode(); // ensure all destructor of ASTNode virtual
  ASTNodeType GetASTNodeType() const;
  const pars::Location& GetLocation() const;
  virtual void Accept(Visitor&) = 0;

private:
  ASTNodeType mASTNodeType;
  pars::Location mLocation;
}; // ASTNode

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_AST_NODE_H
