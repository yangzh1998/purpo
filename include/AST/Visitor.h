//
// Created by YANG Zehai on 2021/11/12.
//

#ifndef PUR_AST_VISITOR_H
#define PUR_AST_VISITOR_H

#ifndef ABSTRACT
#define ABSTRACT
#endif // ABSTRACT

namespace pur {

namespace ast {

class ASTRoot;
class ImportDecl;
class GlobalVarDecl;
class FuncDef;
class Block;
class Break;
class Continue;
class EmptyStmt;
class ForLoop;
class WhileLoop;
class IfStmt;
class ReturnStmt;
class AssignStmt;
class CallStmt;
class Expr;
class ArrayValue;
class MapValue;
class Binary;
class Unary;
class NullExpr;
class IndexVisit;
class RangeVisit;
class Call;
class Variable;

ABSTRACT class Visitor {
public:
  virtual ~Visitor() = default;
  virtual void VisitASTRoot(ASTRoot&) = 0;
  virtual void VisitImportDecl(ImportDecl&) = 0;
  virtual void VisitGlobalVarDecl(GlobalVarDecl&) = 0;
  virtual void VisitFuncDef(FuncDef&) = 0;
  virtual void VisitBlock(Block&) = 0;
  virtual void VisitBreak(Break&) = 0;
  virtual void VisitContinue(Continue&) = 0;
  virtual void VisitEmptyStmt(EmptyStmt&) = 0;
  virtual void VisitForLoop(ForLoop&) = 0;
  virtual void VisitWhileLoop(WhileLoop&) = 0;
  virtual void VisitIfStmt(IfStmt&) = 0;
  virtual void VisitReturnStmt(ReturnStmt&) = 0;
  virtual void VisitAssignStmt(AssignStmt&) = 0;
  virtual void VisitCallStmt(CallStmt&) = 0;
  virtual void VisitLiteral(Expr&) = 0;
  virtual void VisitNullExpr(NullExpr&) = 0;
  virtual void VisitArrayValue(ArrayValue&) = 0;
  virtual void VisitMapValue(MapValue&) = 0;
  virtual void VisitBinary(Binary&) = 0;
  virtual void VisitUnary(Unary&) = 0;
  virtual void VisitIndexVisit(IndexVisit&) = 0;
  virtual void VisitRangeVisit(RangeVisit&) = 0;
  virtual void VisitCall(Call&) = 0;
  virtual void VisitVariable(Variable&) = 0;
}; // Visitor

} // namespace pur::ast

} // namespace pur

#endif // PUR_AST_VISITOR_H
