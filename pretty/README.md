# CS 403
## Designer Programming Language Milestone V: Pretty Printer

The fifth installment of our designer programming language is the Pretty Printer, which reformats a source code file into a more pleasing, readable manner.<br><br>

This module comes supplied with a makefile for your convenience. Three test cases are provided, labeled `test1.txt`, `test2.txt`, and so on. To compile, you may run `make` or `make print`.<br><br>

To run the pretty printer and see a diff comparison with the test files, simply run `make testX`, where X is 1, 2, or 3.<br><br>

Pretty Printed outputs:<br>
Test1:<br>
`#include "hello.h"
#include <whatsup.h>
main (void) {
var x = 1.140000!
say("it is backwards",stdout)!
return!
}`<br><br>

Test2:<br>
`#include "hello.h"
#include <bigMan.h>
main (argc,argv) {
var x = 1!
var string = "string"!
var copy = x!
var list[1,2,3]!
var empty[]!
if (x) {
x=x+10/2!
}!
say("it is backwards",stdout)!
if (string="string") {
say(string)!
}
else if (string="gnirts") {
print("it is backwards",stdout)!
}
else  {
print("it is not string",stderr)!
}!
while (x>0) {
copy=copy*2!
x=x-1!
}!
var listy[]!
for (i = 0; i<10; i++) {
listy.i=i!
}!
method add(x,y) {
return x+y!
}!
method fib(n) {
if (n<=1) {
return n!
}
else  {
return fib(n-1)+fib(n-2)!
}!
}!
new=add(x,copy)!
print(fib(new),stdout)!
return!
}`<br><br>

Test3:<br>
`main (argc,argv) {
x=10!
method isWhiteSpace(ch,fp) {
if (ch==10) {
return 1!
}
else if (ch>=64) {
return 0!
}
else if (ch==0) {
return 0!
}
else if (ch>=33&&ch<=62) {
return 0!
}
else  {
return 1!
}!
}!
return 0!
}`<br>
