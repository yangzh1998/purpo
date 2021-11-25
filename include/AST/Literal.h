//
// Created by YANG Zehai on 2021/11/21.
//

#ifndef PUR_AST_LITERAL_H
#define PUR_AST_LITERAL_H

#include <cstdint>
#include <string>
#include "AST/Expr.h"

namespace pur {

namespace ast {

template <typename DataType, ASTNodeType type>
class Literal : public Expr {
public:
  Literal(const pars::Location& location, DataType data);
  DataType GetData() const;
  virtual void Accept(Visitor&) override;

private:
  DataType mData;

}; // Literal

using I61Literal = Literal<int64_t, ASTNodeType::kI61Literal>;
using F61Literal = Literal<double, ASTNodeType::kF61Literal>;
using BoolLiteral = Literal<bool, ASTNodeType::kBoolLiteral>;
using StrLiteral = Literal<std::string, ASTNodeType::kStrLiteral>;

template <typename DataType, ASTNodeType type>
Literal<DataType, type>::Literal(const pars::Location& location, DataType data):
Expr(type, location), mData(data) {
  /* empty */
}

template <typename DataType, ASTNodeType type>
DataType Literal<DataType, type>::GetData() const {
  return mData;
}

template <typename DataType, ASTNodeType type>
void Literal<DataType, type>::Accept(Visitor& visitor) {
  visitor.VisitLiteral(*this);
}

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_LITERAL_H
