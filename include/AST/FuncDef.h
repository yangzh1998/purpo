//
// Created by YANG Zehai on 2021/11/10.
//

#ifndef PUR_AST_FUNC_DEF_H
#define PUR_AST_FUNC_DEF_H

#include <string>
#include <memory>
#include <deque>
#include "AST/ASTNode.h"
#include "AST/Block.h"

namespace pur {

namespace ast {

class FuncDef : public ASTNode {
public:
  FuncDef(const pars::Location& loc, const std::string& funcName,
          std::deque<std::string>& paramNames, Block& block);

  const std::string& GetFuncName() const;
  std::deque<std::string>& GetParamNames();
  Block& GetBlock();
  virtual void Accept(Visitor&) override;

private:
  std::string mFuncName;
  std::deque<std::string> mParamNames;
  std::unique_ptr<Block> mBlock;
}; // FuncDef

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_FUNC_DEF_H
