#include "Sema.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Support/raw_ostream.h"

namespace {
class DeclCheck : public ASTVisitor {
    private:
        llvm::StringSet<> Scope;    //The names are stored in this set
        bool HasError;
        enum ErrorType { Twice, Not };

        void error(ErrorType ET, llvm::StringRef V) {
            llvm::errs() << "Variable " << V << " "
                         << (ET == Twice ? "already" : "not")
                         << " declared\n";
            HasError = true;
        }

    public:
        DeclCheck() : HasError(false) {}
        bool hasError() { return HasError; }

        virtual void visit(Factor &Node) override {
            if(Node.getKind() == Factor::Ident) {
                if(Scope.find(Node.getVal()) == Scope.end())
                    error(Not, Node.getVal());
            }
        };

        virtual void visit(BinaryOp &Node) override {
            //Left node
            if(Node.getLeft())
                Node.getLeft()->accept(*this);
            else
                HasError = true;
            //Right node
            if(Node.getRight())
                Node.getRight()->accept(*this);
            else
                HasError = true;
        };

        virtual void visit(WithDecl &Node) override {
            for(auto I = Node.begin(), E = Node.end(); I != E; ++I) {
                //Check if variables was previously added to the set
                if(!Scope.insert(*I).second)
                    error(Twice, *I);
            }
            if(Node.getExpr())
                Node.getExpr()->accept(*this);
            else
                HasError = true;
        };
};
}

bool Sema::semantic(AST *Tree) {
    if(!Tree) return false;
    DeclCheck Check;
    Tree->accept(Check);
    return Check.hasError();

}