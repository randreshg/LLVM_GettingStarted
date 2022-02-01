#include "Lexer.h"

namespace charinfo {
    LLVM_READNONE inline bool isWhitespace(char c) {
        return c == ' ' || c == '\t' || c == '\f' || c == '\v' ||
               c == '\r' || c == '\n';
    }

    LLVM_READNONE inline bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    LLVM_READNONE inline bool isLetter(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }
}

void Lexer::next(Token &token) {
    while(*BufferPtr && charinfo::isWhitespace(*BufferPtr))
        ++BufferPtr;
    // No string
    if(!*BufferPtr) {
        token.Kind = Token::eoi;
        return;
    }
    //Letter
    if(charinfo::isLetter(*BufferPtr)) {
        const char *end = BufferPtr + 1;
        while(charinfo::isLetter(*end))
            ++end;
        llvm::StringRef Name(BufferPtr, end - BufferPtr);
        Token::TokenKind kind = Name == "with" ? Token::KW_with : Token::ident;
        formToken(token, end, kind);
        return;
    }
    //Digits
    else if(charinfo::isDigit(*BufferPtr)) {
        const char *end = BufferPtr + 1;
        while(charinfo::isDigit(*end))
            ++end;
        formToken(token, end, Token::number);
        return;
    }
    //Others
    else {
        switch (*BufferPtr) {
            #define CASE(ch, tok) case ch: formToken(token, BufferPtr + 1, tok); break;
            CASE('+', Token::plus);
            CASE('-', Token::minus);
            CASE('*', Token::star);
            CASE('/', Token::slash);
            CASE('(', Token::l_parent);
            CASE(')', Token::r_parent);
            CASE(':', Token::colon);
            CASE(',', Token::comma);
            #undef CASE
            default:
                formToken(token, BufferPtr + 1, Token::unknown);
        }
        return;
    }
}

void Lexer::formToken(Token &Tok, const char *TokEnd, Token::TokenKind Kind) {
    Tok.Kind = Kind;
    Tok.text = llvm::StringRef(BufferPtr, TokEnd - BufferPtr);
    BufferPtr = TokEnd;
}