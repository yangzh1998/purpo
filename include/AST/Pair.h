//
// Created by YANG Zehai on 2021/11/20.
//

#ifndef PUR_AST_PAIR_H
#define PUR_AST_PAIR_H

#include <utility>
#include <memory>
#include "AST/Expr.h"

namespace pur {

namespace ast {

using Pair = std::pair<std::unique_ptr<ast::Expr>, std::unique_ptr<ast::Expr>>;

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_PAIR_H
