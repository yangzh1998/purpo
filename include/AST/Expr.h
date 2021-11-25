//
// Created by YANG Zehai on 2021/11/18.
//

#ifndef PUR_AST_EXPR_H
#define PUR_AST_EXPR_H

#include "AST/ASTNode.h"

#ifndef ABSTRACT
#define ABSTRACT
#endif // ABSTRACT

namespace pur {

namespace ast {

ABSTRACT class Expr : public ASTNode {
public:
  Expr(ASTNodeType ASTNodeType, const pars::Location& location);
}; // Expr

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_EXPR_H
