
Simple compiler using LLVM 
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