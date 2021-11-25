//
// Created by YANG Zehai on 2021/11/15.
//

#include <cassert>
#include "AST/includes.h"

using namespace pur;
using namespace pur::ast;

Printer::Printer(std::ostream& os): mWriter(os) {
  /* empty */
}

void Printer::VisitASTRoot(ASTRoot& astRoot) {
  mWriter.PrintLn("<start>");
  mWriter.IncIndent();
  for (auto& decl : astRoot.GetDeclarations()) {
    decl->Accept(*this);
  }
  mWriter.DecIndent();
}

void Printer::VisitImportDecl(ImportDecl& importDecl) {
  mWriter.PrintLn("<import>");
  mWriter.IncIndent();
  mWriter.Print("<module> ");
  for (std::string& ident : importDecl.GetModuleName()) {
    mWriter.Print(ident).Print(" ");
  }
  mWriter.PrintLn();
  mWriter.Print("<alias> ").PrintLn(importDecl.GetAlias());
  mWriter.DecIndent();
}

void Printer::VisitGlobalVarDecl(GlobalVarDecl& globalVarDecl) {
  mWriter.Print("<gbl decl> ").PrintLn(globalVarDecl.GetVarName());
}

void Printer::VisitFuncDef(FuncDef& funcDef) {
  mWriter.Print("<func> ").PrintLn(funcDef.GetFuncName());
  mWriter.IncIndent();
  mWriter.Print("<params> ");
  for (std::string& param : funcDef.GetParamNames()) {
    mWriter.Print(param).Print(" ");
  }
  mWriter.PrintLn();
  funcDef.GetBlock().Accept(*this);
  mWriter.DecIndent();
}

void Printer::VisitBlock(Block& block) {
  mWriter.PrintLn("<block>");
  mWriter.IncIndent();
  for (auto& stmt : block.GetStmts()) {
    stmt->Accept(*this);
  }
  mWriter.DecIndent();
}

void Printer::VisitBreak(Break& brake) {
  mWriter.PrintLn("<break>");
}

void Printer::VisitContinue(Continue& cont) {
  mWriter.PrintLn("<continue>");
}

void Printer::VisitEmptyStmt(EmptyStmt& emptyStmt) {
  mWriter.PrintLn("<skip>");
}

void Printer::VisitForLoop(ForLoop& forLoop) {
  mWriter.PrintLn("<for>");
  mWriter.IncIndent();
  mWriter.Print("<params> ");
  for (std::string& param : forLoop.GetParamNames()) {
    mWriter.Print(param).Print(" ");
  }
  mWriter.PrintLn();
  mWriter.PrintLn("<iter>");
  mWriter.IncIndent();
  forLoop.GetExpr().Accept(*this);
  mWriter.DecIndent();
  forLoop.GetBlock().Accept(*this);
  mWriter.DecIndent();
}

void Printer::VisitWhileLoop(WhileLoop& whileLoop) {
  mWriter.PrintLn("<while>");
  mWriter.IncIndent();
  mWriter.PrintLn("<condition>");
  mWriter.IncIndent();
  whileLoop.GetCondition().Accept(*this);
  mWriter.DecIndent();
  whileLoop.GetBlock().Accept(*this);
  mWriter.DecIndent();
}

void Printer::VisitIfStmt(IfStmt& ifStmt) {
  mWriter.PrintLn("<if>");
  mWriter.IncIndent();
  mWriter.PrintLn("<condition>");
  mWriter.IncIndent();
  ifStmt.GetCondition().Accept(*this);
  mWriter.DecIndent();
  ifStmt.GetBlock().Accept(*this);
  mWriter.DecIndent();
  if (ifStmt.GetBranch() != nullptr) {
    mWriter.PrintLn("<branch>");
    mWriter.IncIndent();
    ifStmt.GetBranch()->Accept(*this);
    mWriter.DecIndent();
  }
}

void Printer::VisitReturnStmt(ReturnStmt& returnStmt) {
  mWriter.PrintLn("<return>");
  if (returnStmt.GetExpr() != nullptr) {
    mWriter.IncIndent();
    returnStmt.GetExpr()->Accept(*this);
    mWriter.DecIndent();
  }
}

void Printer::VisitAssignStmt(AssignStmt& assignStmt) {
  mWriter.PrintLn("<assign>");
  mWriter.IncIndent();
  mWriter.PrintLn("<left>");
  mWriter.IncIndent();
  assignStmt.GetLeft().Accept(*this);
  mWriter.DecIndent();
  switch (assignStmt.GetAssignOp()) {
    case AssignOp::kDefault:
      mWriter.PrintLn("=");
      break;
    case AssignOp::kAdd:
      mWriter.PrintLn("+=");
      break;
    case AssignOp::kSub:
      mWriter.PrintLn("-=");
      break;
    case AssignOp::kMul:
      mWriter.PrintLn("*=");
      break;
    case AssignOp::kDiv:
      mWriter.PrintLn("/=");
      break;
    case AssignOp::kMod:
      mWriter.PrintLn("%=");
      break;
  }
  mWriter.PrintLn("<right>");
  mWriter.IncIndent();
  assignStmt.GetRight().Accept(*this);
  mWriter.DecIndent();
  mWriter.DecIndent();
}

void Printer::VisitCallStmt(CallStmt& callStmt) {
  mWriter.PrintLn("<call>");
  mWriter.IncIndent();
  callStmt.GetCall().Accept(*this);
  mWriter.DecIndent();
}

void Printer::VisitLiteral(Expr& expr) {
  switch (expr.GetASTNodeType()) {
    case ASTNodeType::kI61Literal: {
      I61Literal literal = (I61Literal&)expr;
      mWriter.Print("<I61 Lit> ").PrintLn(std::to_string(literal.GetData()));
      break;
    }
    case ASTNodeType::kF61Literal: {
      F61Literal literal = (F61Literal&)expr;
      mWriter.Print("<F61 Lit> ").PrintLn(std::to_string(literal.GetData()));
      break;
    }
    case ASTNodeType::kBoolLiteral: {
      BoolLiteral literal = (BoolLiteral&)expr;
      mWriter.Print("<bool Lit> ");
      if (literal.GetData()) {
        mWriter.PrintLn("true");
      } else {
        mWriter.PrintLn("false");
      }
      break;
    }
    case ASTNodeType::kStrLiteral: {
      StrLiteral literal = (StrLiteral&)expr;
      mWriter.Print("<Str Lit> ").PrintLn(literal.GetData());
      break;
    }
    default:
      assert(false);
      break;
  }
}

void Printer::VisitNullExpr(NullExpr& nullExpr) {
  mWriter.PrintLn("<null>");
}

void Printer::VisitArrayValue(ArrayValue& arrayValue) {
  mWriter.PrintLn("<arr>");
  mWriter.IncIndent();
  for (auto& element : arrayValue.GetElements()) {
    element->Accept(*this);
  }
  mWriter.DecIndent();
}

void Printer::VisitMapValue(MapValue& mapValue) {
  mWriter.PrintLn("<map>");
  mWriter.IncIndent();
  for (auto& pair : mapValue.GetPairs()) {
    mWriter.PrintLn("<pair>");
    mWriter.IncIndent();
    pair->first->Accept(*this);
    pair->second->Accept(*this);
    mWriter.DecIndent();
  }
  mWriter.DecIndent();
}

void Printer::VisitBinary(Binary& binary) {
  mWriter.Print("<Binary> ");
  switch (binary.GetOp()) {
    case BinaryOp::kOr:
      mWriter.PrintLn("or");
      break;
    case BinaryOp::kAnd:
      mWriter.PrintLn("and");
      break;
    case BinaryOp::kAdd:
      mWriter.PrintLn("+");
      break;
    case BinaryOp::kSub:
      mWriter.PrintLn("-");
      break;
    case BinaryOp::kMul:
      mWriter.PrintLn("*");
      break;
    case BinaryOp::kDiv:
      mWriter.PrintLn("/");
      break;
    case BinaryOp::kMod:
      mWriter.PrintLn("%");
      break;
    case BinaryOp::kEq:
      mWriter.PrintLn("==");
      break;
    case BinaryOp::kNEq:
      mWriter.PrintLn("!=");
      break;
    case BinaryOp::kGt:
      mWriter.PrintLn(">");
      break;
    case BinaryOp::kGEq:
      mWriter.PrintLn(">=");
      break;
    case BinaryOp::kLt:
      mWriter.PrintLn("<");
      break;
    case BinaryOp::kLEq:
      mWriter.PrintLn("<=");
      break;
  }
  mWriter.IncIndent();
  binary.GetLeft().Accept(*this);
  binary.GetRight().Accept(*this);
  mWriter.DecIndent();

}

void Printer::VisitUnary(Unary& unary) {
  switch (unary.GetOp()) {
    case UnaryOp::kNot:
      mWriter.PrintLn("<not>");
      break;
    case UnaryOp::kNeg:
      mWriter.PrintLn("<neg>");
      break;
  }
  mWriter.IncIndent();
  unary.GetExpr().Accept(*this);
  mWriter.DecIndent();
}

void Printer::VisitIndexVisit(IndexVisit& indexVisit) {
  mWriter.PrintLn("<index ref>");
  mWriter.IncIndent();
  indexVisit.GetOwner().Accept(*this);
  indexVisit.GetIndex().Accept(*this);
  mWriter.DecIndent();
}

void Printer::VisitRangeVisit(RangeVisit& rangeVisit) {
  mWriter.PrintLn("<range ref>");
  mWriter.IncIndent();
  rangeVisit.GetOwner().Accept(*this);
  rangeVisit.GetBegin().Accept(*this);
  rangeVisit.GetEnd().Accept(*this);
  mWriter.DecIndent();
}

void Printer::VisitCall(Call& call) {
  mWriter.PrintLn("<call>");
  mWriter.IncIndent();
  mWriter.PrintLn("<fn ref>");
  mWriter.IncIndent();
  for (auto& str : call.GetFuncPath()) {
    mWriter.PrintLn(str);
  }
  mWriter.DecIndent();
  mWriter.PrintLn("<args>");
  mWriter.IncIndent();
  for (auto& arg : call.GetArgs()) {
    arg->Accept(*this);
  }
  mWriter.DecIndent();
  mWriter.DecIndent();
}

void Printer::VisitVariable(Variable& variable) {
  mWriter.PrintLn("<var ref>");
  mWriter.IncIndent();
  for (auto& str : variable.GetVarPath()) {
    mWriter.PrintLn(str);
  }
  mWriter.DecIndent();
}

