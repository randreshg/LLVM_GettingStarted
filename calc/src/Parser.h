#ifndef PARSER_H
#define PARSER_H

#include "AST.h"
#include "Lexer.h"
#include "llvm/Support/raw_ostream.h"

class Parser {
    Lexer &Lex;
    Token Tok;
    bool HasError;

    void error() {
        llvm::errs() << "Unexpected: " << Tok.getText() << "\n";
        HasError = true;
    }

    //Retrieves the next token
    void advance() { Lex.next(Tok); }

    //Test whether the look-ahead is of the expected kind
    bool expect(Token::TokenKind Kind) {
        if(Tok.is(Kind))
            return true;
        error();
        return false;
    }

    //Retrieves the next token if the look-ahead is of the expected kind
    bool consume(Token::TokenKind Kind) {
        if(expect(Kind)) {
            advance();
            return true;
        } 
        return false;
    }

    //For each non-terminal in the grammar, a method to
    //parse the rule is declared
    AST *parseCalc();
    Expr *parseExpr();
    Expr *parseTerm();
    Expr *parseFactor();

    //Public interface
    public:
        Parser(Lexer &Lex) : Lex(Lex), HasError(false) {
            advance();  //Retrieves first token
        }

        bool hasError() { return HasError; }

        AST *parse();

};


#endif