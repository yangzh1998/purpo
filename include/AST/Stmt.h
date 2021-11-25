//
// Created by YANG Zehai on 2021/11/10.
//

#ifndef PUR_AST_STMT_H
#define PUR_AST_STMT_H

#include "AST/ASTNode.h"

#ifndef ABSTRACT
#define ABSTRACT
#endif // ABSTRACT

namespace pur {

namespace ast {

ABSTRACT class Stmt : public ASTNode {
public:
  Stmt(ASTNodeType ASTNodeType, const pars::Location& location);
}; // Stmt

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_STMT_H
