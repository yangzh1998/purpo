//
// Created by YANG Zehai on 2021/3/15.
//

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "parser/Parser.h"
#include "parser/Token.h"
#include "AST/includes.h"

using namespace pur;
using namespace pur::pars;

Parser::Parser(Scanner*&& scanner): mScanner(scanner) {
  /* empty */
}

Parser::~Parser() {
  /* empty */
}

void Parser::Init(const std::string& filePath) {
  mFilePath = filePath;
  mScanner->Init(mFilePath);
  mAhead = mScanner->GetNextToken();
}

void Parser::RaiseSyntaxError(const std::vector<int>& expectedTokens) const {
  std::printf("ERROR: %s: %d:%d, syntax error. Expected tokens: ",
              mFilePath.c_str(), mAhead->mSemanticValue->mLocation.mLine,
              mAhead->mSemanticValue->mLocation.mColumn);
  for (int token : expectedTokens) {
    std::printf("\"%s\" ", Token::gTokenToString[token].c_str());
  }
  std::printf("\n");
  std::exit(0);
}

std::unique_ptr<SemanticValue> Parser::MatchToken(int expected) {
  if (mAhead->mCode != expected) {
    RaiseSyntaxError(std::vector<int>({expected}));
  }
  std::unique_ptr<SemanticValue> ret(std::move(mAhead->mSemanticValue));
  mAhead = mScanner->GetNextToken();
  return std::unique_ptr<SemanticValue>(std::move(ret));
}

std::unique_ptr<SemanticValue> Parser::Consume() {
  std::unique_ptr<SemanticValue> ret(std::move(mAhead->mSemanticValue));
  mAhead = mScanner->GetNextToken();
  return std::unique_ptr<SemanticValue>(std::move(ret));
}

std::unique_ptr<ast::ASTRoot> Parser::Parse() {
  std::unique_ptr<SemanticValue> semValue = ParseASTRoot();
  return std::unique_ptr<ast::ASTRoot>(semValue->mASTRoot);
}

std::unique_ptr<SemanticValue> Parser::ParseASTRoot() {
  std::unique_ptr<SemanticValue> params[2];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = ParseDeclList();
  params[0]->mASTRoot = new ast::ASTRoot(params[1]->mLocation, mFilePath,
                                         *(params[1]->mDeclarations));
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseDeclList() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  static std::vector<int> expectedTokens = {kImport, kIdentifier, kFunc, EOF};
  switch (mAhead->mCode) {
    case EOF:
      params[0]->mDeclarations = new std::deque<std::unique_ptr<ast::ASTNode>>();
      break;
    case kImport:
    case kIdentifier:
    case kFunc:
      params[1] = ParseDecl();
      params[2] = ParseDeclList();
      params[0]->mDeclarations = params[2]->mDeclarations;
      params[0]->mDeclarations->emplace_front(params[1]->mDeclaration);
      params[0]->mLocation = params[1]->mLocation;
      break;
    default:
      RaiseSyntaxError(expectedTokens);
      break;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseDecl() {
  std::unique_ptr<SemanticValue> params[2];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  static std::vector<int> expectedTokens = {kImport, kIdentifier, kFunc};
  switch (mAhead->mCode) {
    case kImport:
      params[1] = ParseImportDecl();
      break;
    case kIdentifier:
      params[1] = ParseGlobalVarDecl();
      break;
    case kFunc:
      params[1] = ParseFuncDef();
      break;
    default:
      RaiseSyntaxError(expectedTokens);
      break;
  }
  params[0]->mDeclaration = params[1]->mDeclaration;
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseImportDecl() {
  std::unique_ptr<SemanticValue> params[6];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = MatchToken(kImport);
  params[2] = ParseIdentList();
  params[3] = MatchToken(kAs);
  params[4] = MatchToken(kIdentifier);
  params[5] = MatchToken(';');
  params[0]->mDeclaration = new ast::ImportDecl(params[2]->mLocation,
                                                *(params[2]->mIdentList),
                                                params[4]->mIdentifier);
  params[0]->mLocation = params[2]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseIdentList() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = MatchToken(kIdentifier);
  params[2] = ParseDoubleColonIdentList();
  params[0]->mIdentList = params[2]->mIdentList;
  params[0]->mIdentList->push_front(params[1]->mIdentifier);
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseDoubleColonIdentList() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  switch (mAhead->mCode) {
    case kField:
      params[1] = MatchToken(kField);
      params[2] = MatchToken(kIdentifier);
      params[3] = ParseDoubleColonIdentList();
      params[0]->mIdentList = params[3]->mIdentList;
      params[0]->mIdentList->push_front(params[2]->mIdentifier);
      params[0]->mLocation = params[2]->mLocation;
      break;
    default:
      params[0]->mIdentList = new std::deque<std::string>();
      params[0]->mLocation = mAhead->mSemanticValue->mLocation;
      break;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseGlobalVarDecl() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = MatchToken(kIdentifier);
  params[2] = MatchToken(';');
  params[0]->mDeclaration = new ast::GlobalVarDecl(params[1]->mLocation,
                                                   params[1]->mIdentifier);
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseFuncDef() {
  std::unique_ptr<SemanticValue> params[7];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = MatchToken(kFunc);
  params[2] = MatchToken(kIdentifier);
  params[3] = MatchToken('(');
  params[4] = ParseParamList();
  params[5] = MatchToken(')');
  params[6] = ParseBlock();
  params[0]->mDeclaration = new ast::FuncDef(params[2]->mLocation,
                                             params[2]->mIdentifier,
                                             *(params[4]->mIdentList),
                                             *(ast::Block*)(params[6]->mStmt));
  params[0]->mLocation = params[2]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseParamList() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  switch (mAhead->mCode) {
    case kIdentifier:
      params[1] = MatchToken(kIdentifier);
      params[2] = ParseCommaIdentList();
      params[0]->mIdentList = params[2]->mIdentList;
      params[0]->mIdentList->push_front(params[1]->mIdentifier);
      params[0]->mLocation = params[1]->mLocation;
      break;
    default:
      params[0]->mIdentList = new std::deque<std::string>();
      params[0]->mLocation = mAhead->mSemanticValue->mLocation;
      break;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseCommaIdentList() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  switch (mAhead->mCode) {
    case ',':
      params[1] = MatchToken(',');
      params[2] = MatchToken(kIdentifier);
      params[3] = ParseCommaIdentList();
      params[0]->mIdentList = params[3]->mIdentList;
      params[0]->mIdentList->push_front(params[2]->mIdentifier);
      params[0]->mLocation = params[2]->mLocation;
      break;
    default:
      params[0]->mIdentList = new std::deque<std::string>();
      params[0]->mLocation = mAhead->mSemanticValue->mLocation;
      break;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseBlock() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = MatchToken('{');
  params[2] = ParseStmtList();
  params[3] = MatchToken('}');
  params[0]->mStmt = new ast::Block(params[2]->mLocation,
                                    *(params[2]->mStmtList));
  params[0]->mLocation = params[2]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseStmtList() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  switch (mAhead->mCode) {
    case '}':
      params[0]->mStmtList = new std::deque<std::unique_ptr<ast::Stmt>>();
      params[0]->mLocation = mAhead->mSemanticValue->mLocation;
      break;
    default:
      params[1] = ParseStmt();
      params[2] = ParseStmtList();
      params[0]->mStmtList = params[2]->mStmtList;
      params[0]->mStmtList->emplace_front(params[1]->mStmt);
      params[0]->mLocation = params[1]->mLocation;
      break;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseStmt() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  switch (mAhead->mCode) {
    case kFor:
      params[1] = ParseForLoop();
      params[0]->mStmt = params[1]->mStmt;
      break;
    case kWhile:
      params[1] = ParseWhileLoop();
      params[0]->mStmt = params[1]->mStmt;
      break;
    case kIf:
      params[1] = ParseIfStmt();
      params[0]->mStmt = params[1]->mStmt;
      break;
    case kBreak:
      params[1] = MatchToken(kBreak);
      params[2] = MatchToken(';');
      params[0]->mStmt = new ast::Break(params[1]->mLocation);
      break;
    case kContinue:
      params[1] = MatchToken(kContinue);
      params[2] = MatchToken(';');
      params[0]->mStmt = new ast::Continue(params[1]->mLocation);
      break;
    case kReturn:
      params[1] = ParseReturnStmt();
      params[0]->mStmt = params[1]->mStmt;
      break;
    case '{':
      params[1] = ParseBlock();
      params[0]->mStmt = params[1]->mStmt;
      break;
    case ';':
      params[1] = MatchToken(';');
      params[0]->mStmt = new ast::EmptyStmt(params[1]->mLocation);
      break;
    default:
      params[1] = ParseExeStmt();
      params[0]->mStmt = params[1]->mStmt;
      break;
  }
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseForLoop() {
  std::unique_ptr<SemanticValue> params[8];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = MatchToken(kFor);
  params[2] = MatchToken('(');
  params[3] = ParseParamList();
  params[4] = MatchToken(kIn);
  params[5] = ParseExpr();
  params[6] = MatchToken(')');
  params[7] = ParseBlock();
  params[0]->mStmt = new ast::ForLoop(params[1]->mLocation,
                                      *(params[3]->mIdentList),
                                      *(params[5]->mExpr),
                                      *(ast::Block*)(params[7]->mStmt));
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseWhileLoop() {
  std::unique_ptr<SemanticValue> params[6];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = MatchToken(kWhile);
  params[2] = MatchToken('(');
  params[3] = ParseExpr();
  params[4] = MatchToken(')');
  params[5] = ParseBlock();
  params[0]->mStmt = new ast::WhileLoop(params[1]->mLocation,
                                        *(params[3]->mExpr),
                                        *(ast::Block*)(params[5]->mStmt));
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseIfStmt() {
  std::unique_ptr<SemanticValue> params[7];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = MatchToken(kIf);
  params[2] = MatchToken('(');
  params[3] = ParseExpr();
  params[4] = MatchToken(')');
  params[5] = ParseBlock();
  params[6] = ParseElseClause();
  params[0]->mStmt = new ast::IfStmt(params[1]->mLocation,
                                     *(params[3]->mExpr),
                                     *(ast::Block*)(params[5]->mStmt),
                                     (ast::Block*)(params[6]->mStmt));
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseElseClause() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  if (mAhead->mCode == kElse) {
    params[1] = MatchToken(kElse);
    params[2] = ParseBlock();
    params[0]->mStmt = params[2]->mStmt;
    params[0]->mLocation = params[2]->mLocation;
  } else {
    params[0]->mStmt = nullptr;
    params[0]->mLocation = mAhead->mSemanticValue->mLocation;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseReturnStmt() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = MatchToken(kReturn);
  if (mAhead->mCode == ';') {
    params[2] = MatchToken(';');
    params[0]->mStmt = new ast::ReturnStmt(params[1]->mLocation, nullptr);
  } else {
    params[2] = ParseExpr();
    params[3] = MatchToken(';');
    params[0]->mStmt = new ast::ReturnStmt(params[1]->mLocation,
                                           params[2]->mExpr);
  }
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExeStmt() {
  std::unique_ptr<SemanticValue> params[5];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  static std::vector<int> expectedTokens = {kAddAssign, kSubAssign, kMulAssign,
                                            kDivAssign, kModAssign, '=', ';'};
  params[1] = ParseExpr();
  switch (mAhead->mCode) {
    case ';':
      params[2] = MatchToken(';');
      params[0]->mStmt = new ast::CallStmt(params[1]->mLocation,
                                           *(params[1]->mExpr));
      params[0]->mLocation = params[1]->mLocation;
      break;
    case kAddAssign:
    case kSubAssign:
    case kMulAssign:
    case kDivAssign:
    case kModAssign:
    case '=': {
      int op = mAhead->mCode;
      params[2] = Consume();
      params[3] = ParseExpr();
      params[4] = MatchToken(';');
      params[0]->mStmt = new ast::AssignStmt(params[2]->mLocation,
                                             *(params[1]->mExpr), op,
                                             *(params[3]->mExpr));
      params[0]->mLocation = params[2]->mLocation;
      break;
    }
    default:
      RaiseSyntaxError(expectedTokens);
      break;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExprList() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  switch (mAhead->mCode) {
    case ')':
    case ']':
      params[0]->mExprList = new std::deque<std::unique_ptr<ast::Expr>>();
      params[0]->mLocation = mAhead->mSemanticValue->mLocation;
      break;
    default:
      params[1] = ParseExpr();
      params[2] = ParseCommaExprList();
      params[0]->mExprList = params[2]->mExprList;
      params[0]->mExprList->emplace_front(params[1]->mExpr);
      params[0]->mLocation = params[1]->mLocation;
      break;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseCommaExprList() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  switch (mAhead->mCode) {
    case ',':
      params[1] = MatchToken(',');
      params[2] = ParseExpr();
      params[3] = ParseCommaExprList();
      params[0]->mExprList = params[3]->mExprList;
      params[0]->mExprList->emplace_front(params[2]->mExpr);
      params[0]->mLocation = params[2]->mLocation;
      break;
    default:
      params[0]->mExprList = new std::deque<std::unique_ptr<ast::Expr>>();
      params[0]->mLocation = mAhead->mSemanticValue->mLocation;
      break;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseJsonValue() {
  std::unique_ptr<SemanticValue> params[2];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  static std::vector<int> expectedTokens = {kTrue, kFalse, kI61Const, kF61Const,
                                            kStrConst, kNull, '[', '{'};
  switch (mAhead->mCode) {
    case kTrue:
      params[1] = MatchToken(kTrue);
      params[0]->mExpr = new ast::BoolLiteral(params[1]->mLocation, true);
      break;
    case kFalse:
      params[1] = MatchToken(kFalse);
      params[0]->mExpr = new ast::BoolLiteral(params[1]->mLocation, false);
      break;
    case kI61Const:
      params[1] = MatchToken(kI61Const);
      params[0]->mExpr = new ast::I61Literal(params[1]->mLocation,
                                             params[1]->mI61Const);
      break;
    case kF61Const:
      params[1] = MatchToken(kF61Const);
      params[0]->mExpr = new ast::F61Literal(params[1]->mLocation,
                                             params[1]->mF61Const);
      break;
    case kStrConst:
      params[1] = MatchToken(kStrConst);
      params[0]->mExpr = new ast::StrLiteral(params[1]->mLocation,
                                             params[1]->mStrConst);
      break;
    case kNull:
      params[1] = MatchToken(kNull);
      params[0]->mExpr = new ast::NullExpr(params[1]->mLocation);
      break;
    case '[':
      params[1] = ParseJsonArray();
      params[0]->mExpr = params[1]->mExpr;
      break;
    case '{':
      params[1] = ParseJsonObject();
      params[0]->mExpr = params[1]->mExpr;
      break;
    default:
      RaiseSyntaxError(expectedTokens);
      break;
  }
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseJsonArray() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = MatchToken('[');
  params[2] = ParseExprList();
  params[3] = MatchToken(']');
  params[0]->mExpr = new ast::ArrayValue(params[1]->mLocation,
                                         *(params[2]->mExprList));
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseJsonObject() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = MatchToken('{');
  params[2] = ParsePairList();
  params[3] = MatchToken('}');
  params[0]->mExpr = new ast::MapValue(params[1]->mLocation,
                                       *(params[2]->mPairList));
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParsePair() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = ParseExpr();
  params[2] = MatchToken(':');
  params[3] = ParseExpr();
  params[0]->mPair = new ast::Pair(std::unique_ptr<ast::Expr>(params[1]->mExpr),
                                   std::unique_ptr<ast::Expr>(params[3]->mExpr));
  params[0]->mLocation = params[2]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParsePairList() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  switch (mAhead->mCode) {
    case '}':
      params[0]->mPairList = new std::deque<std::unique_ptr<ast::Pair>>();
      params[0]->mLocation = mAhead->mSemanticValue->mLocation;
      break;
    default:
      params[1] = ParsePair();
      params[2] = ParseCommaPairList();
      params[0]->mPairList = params[2]->mPairList;
      params[0]->mPairList->emplace_front(params[1]->mPair);
      params[0]->mLocation = params[1]->mLocation;
      break;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseCommaPairList() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  switch (mAhead->mCode) {
    case ',':
      params[1] = MatchToken(',');
      params[2] = ParsePair();
      params[3] = ParseCommaPairList();
      params[0]->mPairList = params[3]->mPairList;
      params[0]->mPairList->emplace_front(params[2]->mPair);
      params[0]->mLocation = params[2]->mLocation;
      break;
    default:
      params[0]->mPairList = new std::deque<std::unique_ptr<ast::Pair>>();
      params[0]->mLocation = mAhead->mSemanticValue->mLocation;
      break;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExpr() {
  return std::unique_ptr<SemanticValue>(ParseExpr1());
}

std::unique_ptr<SemanticValue> Parser::ParseExpr1() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = ParseExpr2();
  params[2] = ParseExprT1();
  params[0]->mExpr = params[1]->mExpr;
  for (int i = 0; i < params[2]->mExprList->size(); i ++) {
    params[0]->mExpr = new ast::Binary(params[2]->mLocList->at(i),
                                       *(params[0]->mExpr),
                                       *(params[2]->mExprList->at(i)),
                                       ast::BinaryOp::kOr);
  }
  params[0]->mLocation = params[2]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExprT1() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  if (mAhead->mCode == kOr) {
    params[1] = MatchToken(kOr);
    params[2] = ParseExpr2();
    params[3] = ParseExprT1();
    params[0]->mExprList = params[3]->mExprList;
    params[0]->mLocList = params[3]->mLocList;
    params[0]->mExprList->emplace_front(params[2]->mExpr);
    params[0]->mLocList->emplace_front(params[1]->mLocation);
    params[0]->mLocation = params[1]->mLocation;
  } else {
    params[0]->mExprList = new std::deque<std::unique_ptr<ast::Expr>>();
    params[0]->mLocList = new std::deque<Location>();
    params[0]->mLocation = mAhead->mSemanticValue->mLocation;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExpr2() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = ParseExpr3();
  params[2] = ParseExprT2();
  params[0]->mExpr = params[1]->mExpr;
  for (int i = 0; i < params[2]->mExprList->size(); i ++) {
    params[0]->mExpr = new ast::Binary(params[2]->mLocList->at(i),
                                       *(params[0]->mExpr),
                                       *(params[2]->mExprList->at(i)),
                                       ast::BinaryOp::kAnd);
  }
  params[0]->mLocation = params[2]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExprT2() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  if (mAhead->mCode == kAnd) {
    params[1] = MatchToken(kAnd);
    params[2] = ParseExpr3();
    params[3] = ParseExprT2();
    params[0]->mExprList = params[3]->mExprList;
    params[0]->mLocList = params[3]->mLocList;
    params[0]->mExprList->emplace_front(params[2]->mExpr);
    params[0]->mLocList->emplace_front(params[1]->mLocation);
    params[0]->mLocation = params[1]->mLocation;
  } else {
    params[0]->mExprList = new std::deque<std::unique_ptr<ast::Expr>>();
    params[0]->mLocList = new std::deque<Location>();
    params[0]->mLocation = mAhead->mSemanticValue->mLocation;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExpr3() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = ParseExpr4();
  params[2] = ParseExprT3();
  params[0]->mExpr = params[1]->mExpr;
  for (int i = 0; i < params[2]->mExprList->size(); i ++) {
    params[0]->mExpr = new ast::Binary(params[2]->mLocList->at(i),
                                       *(params[0]->mExpr),
                                       *(params[2]->mExprList->at(i)),
                                       params[2]->mBinaryOps->at(i));
  }
  params[0]->mLocation = params[2]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExprT3() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  int code = mAhead->mCode;
  if (code == kEq || code == kNotEq) {
    params[1] = Consume();
    params[2] = ParseExpr4();
    params[3] = ParseExprT3();
    params[0]->mExprList = params[3]->mExprList;
    params[0]->mLocList = params[3]->mLocList;
    params[0]->mBinaryOps = params[3]->mBinaryOps;
    params[0]->mExprList->emplace_front(params[2]->mExpr);
    params[0]->mLocList->emplace_front(params[1]->mLocation);
    params[0]->mLocation = params[1]->mLocation;
    if (code == kEq) {
      params[0]->mBinaryOps->emplace_front(ast::BinaryOp::kEq);
    } else {
      params[0]->mBinaryOps->emplace_front(ast::BinaryOp::kNEq);
    }
  } else {
    params[0]->mExprList = new std::deque<std::unique_ptr<ast::Expr>>();
    params[0]->mLocList = new std::deque<Location>();
    params[0]->mBinaryOps = new std::deque<ast::BinaryOp>();
    params[0]->mLocation = mAhead->mSemanticValue->mLocation;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExpr4() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = ParseExpr5();
  params[2] = ParseExprT4();
  params[0]->mExpr = params[1]->mExpr;
  for (int i = 0; i < params[2]->mExprList->size(); i ++) {
    params[0]->mExpr = new ast::Binary(params[2]->mLocList->at(i),
                                       *(params[0]->mExpr),
                                       *(params[2]->mExprList->at(i)),
                                       params[2]->mBinaryOps->at(i));
  }
  params[0]->mLocation = params[2]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExprT4() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  int code = mAhead->mCode;
  if (code == kGE || code == '>' || code == kLE || code == '<') {
    params[1] = Consume();
    params[2] = ParseExpr5();
    params[3] = ParseExprT4();
    params[0]->mExprList = params[3]->mExprList;
    params[0]->mLocList = params[3]->mLocList;
    params[0]->mBinaryOps = params[3]->mBinaryOps;
    params[0]->mExprList->emplace_front(params[2]->mExpr);
    params[0]->mLocList->emplace_front(params[1]->mLocation);
    params[0]->mLocation = params[1]->mLocation;
    switch (code) {
      case kGE:
        params[0]->mBinaryOps->emplace_front(ast::BinaryOp::kGEq);
        break;
      case '>':
        params[0]->mBinaryOps->emplace_front(ast::BinaryOp::kGt);
        break;
      case kLE:
        params[0]->mBinaryOps->emplace_front(ast::BinaryOp::kLEq);
        break;
      case '<':
        params[0]->mBinaryOps->emplace_front(ast::BinaryOp::kLt);
        break;
    }
  } else {
    params[0]->mExprList = new std::deque<std::unique_ptr<ast::Expr>>();
    params[0]->mLocList = new std::deque<Location>();
    params[0]->mBinaryOps = new std::deque<ast::BinaryOp>();
    params[0]->mLocation = mAhead->mSemanticValue->mLocation;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExpr5() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = ParseExpr6();
  params[2] = ParseExprT5();
  params[0]->mExpr = params[1]->mExpr;
  for (int i = 0; i < params[2]->mExprList->size(); i ++) {
    params[0]->mExpr = new ast::Binary(params[2]->mLocList->at(i),
                                       *(params[0]->mExpr),
                                       *(params[2]->mExprList->at(i)),
                                       params[2]->mBinaryOps->at(i));
  }
  params[0]->mLocation = params[2]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExprT5() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  int code = mAhead->mCode;
  if (code == '+' || code == '-') {
    params[1] = Consume();
    params[2] = ParseExpr6();
    params[3] = ParseExprT5();
    params[0]->mExprList = params[3]->mExprList;
    params[0]->mLocList = params[3]->mLocList;
    params[0]->mBinaryOps = params[3]->mBinaryOps;
    params[0]->mExprList->emplace_front(params[2]->mExpr);
    params[0]->mLocList->emplace_front(params[1]->mLocation);
    params[0]->mLocation = params[1]->mLocation;
    switch (code) {
      case '+':
        params[0]->mBinaryOps->emplace_front(ast::BinaryOp::kAdd);
        break;
      case '-':
        params[0]->mBinaryOps->emplace_front(ast::BinaryOp::kSub);
        break;
    }
  } else {
    params[0]->mExprList = new std::deque<std::unique_ptr<ast::Expr>>();
    params[0]->mLocList = new std::deque<Location>();
    params[0]->mBinaryOps = new std::deque<ast::BinaryOp>();
    params[0]->mLocation = mAhead->mSemanticValue->mLocation;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExpr6() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = ParseExpr7();
  params[2] = ParseExprT6();
  params[0]->mExpr = params[1]->mExpr;
  for (int i = 0; i < params[2]->mExprList->size(); i ++) {
    params[0]->mExpr = new ast::Binary(params[2]->mLocList->at(i),
                                       *(params[0]->mExpr),
                                       *(params[2]->mExprList->at(i)),
                                       params[2]->mBinaryOps->at(i));
  }
  params[0]->mLocation = params[2]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExprT6() {
  std::unique_ptr<SemanticValue> params[4];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  int code = mAhead->mCode;
  if (code == '*' || code == '/' || code == '%') {
    params[1] = Consume();
    params[2] = ParseExpr7();
    params[3] = ParseExprT6();
    params[0]->mExprList = params[3]->mExprList;
    params[0]->mLocList = params[3]->mLocList;
    params[0]->mBinaryOps = params[3]->mBinaryOps;
    params[0]->mExprList->emplace_front(params[2]->mExpr);
    params[0]->mLocList->emplace_front(params[1]->mLocation);
    params[0]->mLocation = params[1]->mLocation;
    switch (code) {
      case '*':
        params[0]->mBinaryOps->emplace_front(ast::BinaryOp::kMul);
        break;
      case '/':
        params[0]->mBinaryOps->emplace_front(ast::BinaryOp::kDiv);
        break;
      case '%':
        params[0]->mBinaryOps->emplace_front(ast::BinaryOp::kMod);
        break;
    }
  } else {
    params[0]->mExprList = new std::deque<std::unique_ptr<ast::Expr>>();
    params[0]->mLocList = new std::deque<Location>();
    params[0]->mBinaryOps = new std::deque<ast::BinaryOp>();
    params[0]->mLocation = mAhead->mSemanticValue->mLocation;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExpr7() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  switch (mAhead->mCode) {
    case '!':
      params[1] = MatchToken('!');
      params[2] = ParseExpr8();
      params[0]->mExpr = new ast::Unary(params[1]->mLocation,
                                        *(params[2]->mExpr),
                                        ast::UnaryOp::kNot);
      break;
    case '-':
      params[1] = MatchToken('-');
      params[2] = ParseExpr8();
      params[0]->mExpr = new ast::Unary(params[1]->mLocation,
                                        *(params[2]->mExpr),
                                        ast::UnaryOp::kNeg);
      break;
    default:
      params[1] = ParseExpr8();
      params[0]->mExpr = params[1]->mExpr;
      break;
  }
  params[0]->mLocation = params[1]->mLocation;
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExpr8() {
  std::unique_ptr<SemanticValue> params[3];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  params[1] = ParseExpr9();
  params[2] = ParseExprT8();
  params[0]->mExpr = params[1]->mExpr;
  for (auto& expr : *(params[2]->mExprList)) {
    switch (expr->GetASTNodeType()) {
      case ast::ASTNodeType::kIndexVisit:
        ((ast::IndexVisit*)(expr.get()))->SetOwner(*(params[0]->mExpr));
        params[0]->mExpr = expr.get();
        params[0]->mLocation = expr->GetLocation();
        break;
      case ast::ASTNodeType::kRangeVisit:
        ((ast::RangeVisit*)(expr.get()))->SetOwner(*(params[0]->mExpr));
        params[0]->mExpr = expr.get();
        params[0]->mLocation = expr->GetLocation();
        break;
      case ast::ASTNodeType::kCall:
        ((ast::Call*)(expr.get()))->GetArgs().emplace_front(params[0]->mExpr);
        params[0]->mExpr = expr.get();
        params[0]->mLocation = expr->GetLocation();
        break;
      default:
        assert(false);
        break;
    }

  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExprT8() {
  std::unique_ptr<SemanticValue> params[7];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  switch (mAhead->mCode) {
    case '[':
      params[1] = MatchToken('[');
      params[2] = ParseExpr();
      switch (mAhead->mCode) {
        case ']':
          params[3] = MatchToken(']');
          params[4] = ParseExprT8();
          params[0]->mExprList = params[4]->mExprList;
          params[0]->mExprList->emplace_front(
              new ast::IndexVisit(params[1]->mLocation, *(params[2]->mExpr))
              );
          params[0]->mLocation = params[1]->mLocation;
          break;
        case ':':
          params[3] = MatchToken(':');
          params[4] = ParseExpr();
          params[5] = MatchToken(']');
          params[6] = ParseExprT8();
          params[0]->mExprList = params[6]->mExprList;
          params[0]->mExprList->emplace_front(
              new ast::RangeVisit(params[3]->mLocation,
                                  *(params[2]->mExpr),
                                  *(params[4]->mExpr))
          );
          params[0]->mLocation = params[3]->mLocation;
          break;
        default:
          RaiseSyntaxError({']', ':'});
          break;
      }
      break;
    case '.':
      params[1] = MatchToken('.');
      params[2] = ParseIdentList();
      params[3] = MatchToken('(');
      params[4] = ParseExprList();

      params[5] = MatchToken(')');
      params[6] = ParseExprT8();
      params[0]->mExprList = params[6]->mExprList;
      params[0]->mExprList->emplace_front(
          new ast::Call(params[2]->mLocation,
                        *(params[2]->mIdentList),
                        *(params[4]->mExprList))
          );
      params[0]->mLocation = params[2]->mLocation;
      break;
    default:
      params[0]->mExprList = new std::deque<std::unique_ptr<ast::Expr>>();
      params[0]->mLocation = mAhead->mSemanticValue->mLocation;
      break;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}

std::unique_ptr<SemanticValue> Parser::ParseExpr9() {
  std::unique_ptr<SemanticValue> params[5];
  params[0] = std::unique_ptr<SemanticValue>(new SemanticValue());
  static std::vector<int> expectedTokens = {'(', kIdentifier, kTrue, kFalse,
                                            kI61Const, kF61Const, kNull,
                                            kStrConst, '[', '{'};
  switch (mAhead->mCode) {
    case '(':
      params[1] = MatchToken('(');
      params[2] = ParseExpr();
      params[3] = MatchToken(')');
      params[0]->mExpr = params[2]->mExpr;
      params[0]->mLocation = params[2]->mLocation;
      break;
    case kIdentifier:
      params[1] = ParseIdentList();
      if (mAhead->mCode == '(') {
        params[2] = MatchToken('(');
        params[3] = ParseExprList();
        params[4] = MatchToken(')');
        params[0]->mExpr = new ast::Call(params[1]->mLocation,
                                         *(params[1]->mIdentList),
                                         *(params[3]->mExprList));
      } else {
        params[0]->mExpr = new ast::Variable(params[1]->mLocation,
                                             *(params[1]->mIdentList));
      }
      params[0]->mLocation = params[1]->mLocation;
      break;
    case kTrue:
    case kFalse:
    case kI61Const:
    case kF61Const:
    case kNull:
    case kStrConst:
    case '[':
    case '{':
      params[1] = ParseJsonValue();
      params[0]->mExpr = params[1]->mExpr;
      params[0]->mLocation = params[1]->mLocation;
      break;
    default:
      RaiseSyntaxError(expectedTokens);
      break;
  }
  return std::unique_ptr<SemanticValue>(std::move(params[0]));
}
