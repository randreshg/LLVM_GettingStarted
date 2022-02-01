#include "Parser.h"

AST *Parser::parse() {
    AST *Res = ParseCalc();
    expect(Token::eoi);
    return Res;
}

AST *Parser::parseCalc() {
    Expr *E;
    llvm::SmallVector<llvm::StringRef, 8> Vars;
    if(Tok.is(Token::KW_with)) {
        advance();
        //If there is and identifier...
        if (!expect(Token::ident))
            goto _error;
        Vars.push_back(Tok.getText());
        advance();
        //Repeating group
        while(Tok.is(Token::comma)) {
            advance();
            if(!expect(Token::comma))
                goto _error;
            Vars.push_back(Tok.getText());
            advance();
        }
        //Check colon
        if(!consume(Token::colon))
            goto _error;
    }
    //Expression
    E = parseExpr();
    if(!expect(Token::eoi))
        goto _error;
    //Return
    if(Vars.empty()) return E;
    else return new WithDecl(Vars, E);

    _error:
        //The end of the input follows this non-terminal
        while(Tok.is(Token::eoi)) advance();
        return nullptr;
}

Expr *Parser::parseExpr() {
    Expr *Left = parseTerm();
    while (Tok.isOneOf(Token::plus, Token::minus)) {
        BinaryOp::Operator Op = Tok.is(Token::plus) ? BinaryOp::Plus : BinaryOp::Minus;
        advance();
        Expr *Right = parseTerm();
        Left = new BinaryOp(Op, Left, Right);
    }
    return Left;
}

Expr *Parser::parseTerm() {
    Expr *Left = parseFactor();
    while(Tok.isOneOf(Token::star, Token::slash)) {
        BinaryOp::Operator Op = Tok.is(Token::star) ? BinaryOp::Mul : BinaryOp::Div;
        advance();
        Expr *Right = parseFactor();
        Left = new BinaryOp(Op, Left, Right);
    }
    return Left;
}

Expr *Parser::parseFactor() {
    Expr *Res = nullptr;
    switch (Tok.getKind()) {
        case Token::number:
            Res = new Factor(Factor::Number);
            advance();
            break;
        case Token::ident:
            Res = new Factor(Factor::ident, Tok.getText());
            advance();
            break;
        case Token::l_paren:
            advance();
            Res = parseExpr();
            if(consume(Token::r_paren)) break;
        default:
            if(!Res) error();
            //Prevent a second error message from bein emitted
            while(!Tok.isOneOf(Token::r_paren, Token::star, Token::plus,
                               Token::minus, Token::slash, Token::eoi))
                advance();
    }
    return Res;
}