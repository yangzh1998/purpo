//
// Created by YANG Zehai on 2021/11/15.
//

#ifndef PUR_AST_PRINTER_H
#define PUR_AST_PRINTER_H

#include "AST/Visitor.h"
#include "util/IndentPrintWriter.h"

namespace pur {

namespace ast {

class Printer : public Visitor {
public:
  explicit Printer(std::ostream& os = std::cout);
  virtual void VisitASTRoot(ASTRoot&) override;
  virtual void VisitImportDecl(ImportDecl&) override;
  virtual void VisitGlobalVarDecl(GlobalVarDecl&) override;
  virtual void VisitFuncDef(FuncDef&) override;
  virtual void VisitBlock(Block&) override;
  virtual void VisitBreak(Break&) override;
  virtual void VisitContinue(Continue&) override;
  virtual void VisitEmptyStmt(EmptyStmt&) override;
  virtual void VisitForLoop(ForLoop&) override;
  virtual void VisitWhileLoop(WhileLoop&) override;
  virtual void VisitIfStmt(IfStmt&) override;
  virtual void VisitReturnStmt(ReturnStmt&) override;
  virtual void VisitAssignStmt(AssignStmt&) override;
  virtual void VisitCallStmt(CallStmt&) override;
  virtual void VisitLiteral(Expr&) override;
  virtual void VisitNullExpr(NullExpr&) override;
  virtual void VisitArrayValue(ArrayValue&) override;
  virtual void VisitMapValue(MapValue&) override;
  virtual void VisitBinary(Binary&) override;
  virtual void VisitUnary(Unary&) override;
  virtual void VisitIndexVisit(IndexVisit&) override;
  virtual void VisitRangeVisit(RangeVisit&) override;
  virtual void VisitCall(Call&) override;
  virtual void VisitVariable(Variable&) override;

private:
  ut::IndentPrintWriter mWriter;
}; // Printer

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_PRINTER_H
