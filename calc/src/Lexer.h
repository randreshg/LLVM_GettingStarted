#ifndef LEXER_H
#define LEXER_H

// The llvm:StringRef.h class encasulates a pointer to to a 
// C string and its length
#include "llvm/ADT/StringRef.h"
// The llvm:MemoryBuffer provides read-only access to a block 
// of memory, filled with the content og the file
#include "llvm/Support/MemoryBuffer.h"

class Lexer;


class Token {
    friend class Lexer;
    public:
        // Definition of the enumeration for the unique token numbers
        enum TokenKind :unsigned short {
            eoi, unknown, ident, number, comma, colon, plus,
            minus, star, slash, l_parent, r_parent, KW_with
        };
    private:
        TokenKind Kind;
        llvm::StringRef Text;
    public:
        TokenKind getKind() const { return Kind; }
        llvm::StringRef getText() const { return Text; }

        // The is() and isOneOf() methods are used to test if the token is
        // of a certain kind
        bool is(TokenKind K) const { return Kind == K; }
        bool isOneOf(TokenKind K1, TokenKind K2) const {
            return is(K1) || is(K2);
        }
        template <typename... Ts>
        bool isOneOf(TokenKind K1, TokenKind K2, Ts... Ks) const {
            return is(K1) || isOneOf(K2, Ks...);
        }
};

class Lexer {
    const char *BufferStart;    // Pointer to beginning of the input
    const char *BufferPtr;      // Pointer to the next avaliable token
    public:
        Lexer(const llvm::StringRef &Buffer) {
            BufferStart = Buffer.begin();
            BufferPtr = BufferStart;
        }
        // Advance to the next avaliable token, skip spaces
        void next(Token &token);

    private:
        void formToken(Token &Result, const char *TokEnd, Token::TokenKind Kind);

}
#endif