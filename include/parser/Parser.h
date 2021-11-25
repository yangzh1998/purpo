//
// Created by YANG Zehai on 2021/3/15.
//

#ifndef PUR_PARS_PARSER_H
#define PUR_PARS_PARSER_H

#include <memory>
#include <string>
#include <vector>
#include "parser/Scanner.h"
#include "parser/Token.h"
#include "parser/SemanticValue.h"
#include "AST/ASTRoot.h"

namespace pur {

namespace pars {

/**
 * Each file has its own Parser.
 */
class Parser {
public:
  explicit Parser(Scanner*&& scanner);
  ~Parser();
  Parser(const Parser&) = delete;
  Parser& operator=(const Parser&) = delete;
  void Init(const std::string& filePath);

  std::unique_ptr<ast::ASTRoot> Parse();

private:
  std::string mFilePath;
  std::unique_ptr<Scanner> mScanner;
  std::unique_ptr<Token> mAhead;

  void RaiseSyntaxError(const std::vector<int>& expectedTokens) const;
  std::unique_ptr<SemanticValue> MatchToken(int expected);
  std::unique_ptr<SemanticValue> Consume();

  std::unique_ptr<SemanticValue> ParseASTRoot();
  std::unique_ptr<SemanticValue> ParseDeclList();
  std::unique_ptr<SemanticValue> ParseDecl();
  std::unique_ptr<SemanticValue> ParseImportDecl();
  std::unique_ptr<SemanticValue> ParseIdentList();
  std::unique_ptr<SemanticValue> ParseDoubleColonIdentList();
  std::unique_ptr<SemanticValue> ParseGlobalVarDecl();
  std::unique_ptr<SemanticValue> ParseFuncDef();
  std::unique_ptr<SemanticValue> ParseParamList();
  std::unique_ptr<SemanticValue> ParseCommaIdentList();
  std::unique_ptr<SemanticValue> ParseBlock();
  std::unique_ptr<SemanticValue> ParseStmtList();
  std::unique_ptr<SemanticValue> ParseStmt();
  std::unique_ptr<SemanticValue> ParseForLoop();
  std::unique_ptr<SemanticValue> ParseWhileLoop();
  std::unique_ptr<SemanticValue> ParseIfStmt();
  std::unique_ptr<SemanticValue> ParseElseClause();
  std::unique_ptr<SemanticValue> ParseReturnStmt();
  std::unique_ptr<SemanticValue> ParseExeStmt();
  std::unique_ptr<SemanticValue> ParseExprList();
  std::unique_ptr<SemanticValue> ParseCommaExprList();

  std::unique_ptr<SemanticValue> ParseJsonValue();
  std::unique_ptr<SemanticValue> ParseJsonArray();
  std::unique_ptr<SemanticValue> ParseJsonObject();
  std::unique_ptr<SemanticValue> ParsePair();
  std::unique_ptr<SemanticValue> ParsePairList();
  std::unique_ptr<SemanticValue> ParseCommaPairList();

  std::unique_ptr<SemanticValue> ParseExpr();
  std::unique_ptr<SemanticValue> ParseExpr1();
  std::unique_ptr<SemanticValue> ParseExprT1();
  std::unique_ptr<SemanticValue> ParseExpr2();
  std::unique_ptr<SemanticValue> ParseExprT2();
  std::unique_ptr<SemanticValue> ParseExpr3();
  std::unique_ptr<SemanticValue> ParseExprT3();
  std::unique_ptr<SemanticValue> ParseExpr4();
  std::unique_ptr<SemanticValue> ParseExprT4();
  std::unique_ptr<SemanticValue> ParseExpr5();
  std::unique_ptr<SemanticValue> ParseExprT5();
  std::unique_ptr<SemanticValue> ParseExpr6();
  std::unique_ptr<SemanticValue> ParseExprT6();
  std::unique_ptr<SemanticValue> ParseExpr7();
  std::unique_ptr<SemanticValue> ParseExpr8();
  std::unique_ptr<SemanticValue> ParseExprT8();
  std::unique_ptr<SemanticValue> ParseExpr9();
}; // Parser

} // namespace pur::pars

} // namespace pur

#endif // PUR_PARS_PARSER_H
