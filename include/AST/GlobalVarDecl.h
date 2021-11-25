//
// Created by YANG Zehai on 2021/3/19.
//

#ifndef PUR_AST_GLOBAL_VAR_DECL_H
#define PUR_AST_GLOBAL_VAR_DECL_H

#include <string>
#include "AST/ASTNode.h"

namespace pur {

namespace ast {

class GlobalVarDecl : public ASTNode {
public:
  GlobalVarDecl(const pars::Location& loc, const std::string& name);
  const std::string& GetVarName() const;
  virtual void Accept(Visitor&) override;

private:
  std::string mVarName;

}; // GlobalVarDecl

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_GLOBAL_VAR_DECL_H
