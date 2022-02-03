#ifndef AST_H
#define AST_H

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

class AST;
class Expr;
class Factor;
class BinaryOp;
class WithDecl;

class ASTVisitor {
    public:
        virtual void visit(AST &) {};
        virtual void visit(Expr &) {};
        virtual void visit(Factor &) = 0;
        virtual void visit(BinaryOp &) = 0;
        virtual void visit(WithDecl &) = 0;
};

//The AST class is the root of the hierarchy
class AST {
    public:
        virtual ~AST() {}
        virtual void accept(ASTVisitor &V) = 0;
};

//Expr is the root for the AST classes related to expressions
class Expr : public AST {
    public:
        Expr() {}
};

//The Factor class stores a number or the name of a variable
class Factor : public Expr {
    public:
        enum ValueKind { Ident, Number };
    private:
        ValueKind Kind;
        llvm::StringRef Val;
    public:
        Factor(ValueKind Kind, llvm::StringRef Val) : Kind(Kind), Val(Val) {}
        ValueKind getKind() { return Kind; }
        llvm::StringRef getVal() { return Val; }
        virtual void accept(ASTVisitor &V) override { V.visit(*this); }
};

//The BinaryOp class holds the data that is needed to evaluate an expression
class BinaryOp : public Expr {
    public:
        enum Operator { Plus, Minus, Mul, Div };
    private:
        Expr *Left;
        Expr *Right;
        Operator Op;
    public:
        BinaryOp(Operator Op, Expr *L, Expr *R) : Op(Op), Left(L), Right(R) {}
        Expr *getLeft() { return Left; }
        Expr *getRight() { return Right; }
        Operator getOperator() { return Op; }
        virtual void accept(ASTVisitor &V) override { V.visit(*this); }
};

//The WithDecl class sotres the declared variables and the expression
class WithDecl : public AST {
    using VarVector = llvm::SmallVector<llvm::StringRef, 8>;
    VarVector Vars;
    Expr *E;

    public:
        WithDecl(llvm::SmallVector<llvm::StringRef, 8> Vars, Expr *E): Vars(Vars), E(E) {}
        VarVector::const_iterator begin() { return Vars.begin(); }
        VarVector::const_iterator end() { return Vars.end(); }
        Expr *getExpr() { return E; }
        virtual void accept(ASTVisitor &V) override { V.visit(*this); }
};
#endif