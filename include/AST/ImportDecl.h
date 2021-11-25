//
// Created by YANG Zehai on 2021/3/18.
//

#ifndef PUR_AST_IMPORT_DECL_H
#define PUR_AST_IMPORT_DECL_H

#include <deque>
#include <string>
#include "AST/ASTNode.h"

namespace pur {

namespace ast {

class ImportDecl : public ASTNode {
public:
  ImportDecl(const pars::Location& loc, std::deque<std::string>& identList,
             const std::string& alias);
  std::deque<std::string>& GetModuleName();
  const std::string& GetAlias() const;
  virtual void Accept(Visitor&) override;

private:
  std::deque<std::string> mModuleName;
  std::string mAlias;
}; // ImportDecl

} // namespace ast

} // namespace pur



#endif // PUR_AST_IMPORT_DECL_H
