//
// Created by YANG Zehai on 2021/3/15.
//

#ifndef PUR_AST_AST_ROOT_H
#define PUR_AST_AST_ROOT_H

#include <string>
#include <deque>
#include <memory>
#include "AST/ASTNode.h"

namespace pur {

namespace ast {

class ASTRoot : public ASTNode {
public:
  ASTRoot(const pars::Location& loc, const std::string& filePath,
          std::deque<std::unique_ptr<ASTNode>>& declarations);
  const std::string& GetFilePath() const;
  std::deque<std::unique_ptr<ASTNode>>& GetDeclarations();
  virtual void Accept(Visitor&) override;

private:
  std::string mFilePath;
  std::deque<std::unique_ptr<ASTNode>> mDeclarations;
};

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_AST_ROOT_H
