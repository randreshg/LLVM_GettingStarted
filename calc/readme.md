### CALC ###
The frontend and backend have specified structrures. The frontend usually performs the following tasks:
1. The lexer reads the source file and produces a token stream.
2. The parser creates an AST from the token stream.
3. The semantic analyzer adds semantic information to the AST.
4. The code generator produces an intermediate represantion (IR) from the AST.

The intermediate representation is the interface of the backend. The backend does the following tasks:
1. The backend perform target-independent optimization on the IR.
2. It then selects instructions for the IR code.
3. After, it performs target-dependent optimizations on the instructions.
4. Finally, it emits assembler code or an object file.

## An arithmetic expression language ##
# Extended Backus-Naur form (EBNF) #
```
calc : ("with" ident ("," ident)* ":")? expr ;
expr : term (( "+" | "-" ) term)* ;
term : factor (( "*" | "/") factor)* ;
factor : ident | number | "(" expr ")" ;
ident : ([a-zAZ])+ ;
number : ([0-9])+ ;
```
---------------------------
```
cd src
./calc "with a: a*3" | llc -filetype=obj -o=expr.o
clang -o expr expr.o ../../rtcalc.c
./expr
```
---------------------------

Tutorial by: https://github.com/PacktPublishing/Learn-LLVM-12