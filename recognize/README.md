# CS 403
## Designer Programming Language Milestone III: Recognizer

The third installment of our designer programming language is the recognizer, where the grammar module is implemented to determine if Lexemes are in the proper order.<br><br>
This module uses the scanner from milestone II, and builds upon it with the capability to recognize correct grammar constructs via a comprehensive set of functions translated from the grammar rules.<br><br>
The same `types` and `lexer` modules from milestone II are used here. Recognizer functionality can be found in `recognizer.c` and `recognizer.h`, and the driver is `parser.c`.<br><br>
This module comes supplied with a makefile for your convenience. Six test cases are provided, labeled `test1.txt`, `test2.txt`, and so on. To compile the lexical analyzer, simply run a `make` command. After doing so, the recognizer can be used in the form `recognizer <f>`, where `<f>` is the name of a file. If you want to run a specific test, run a `make testX` command, where `X` is the number of the test you wish to run.<br><br>Similarly, the `make run` command compiles and runs some random tests.<br><br>
Correct Test Results:
- test1: legal
- test2: legal
- test3: legal
- test4: illegal: incorrect array definition, line 17
- test5: illegal: incorrect tokens during a variable definition, line 9
- test6: illegal: if statement is not followed by an exclamation, error is caught on line 12 trying to match the return to the expected exclamation

<!--

The second installment of our designer programming language is the lexical analysis module. It follows the first module, grammar, in which we laid out specific rules for the structure of our language. <br><br>
For this module, I have written a scanner that, character by character, reads a file and correctly identifies each individual token. If you want a full list of each token that can be identified, check out `types.c` and `types.h` (there are a lot of tokens).<br><br>
This module comes supplied with a makefile for your convenience. Five test cases are provided, labeled `test1.txt`, `test2.txt`, and so on. To compile the lexical analyzer, simply run a `make` command. After doing so, the scanner can be used in the form `scanner <f>`, where `<f>` is the name of a file. If you want to run a specific test, run a `make testX` command, where `X` is the number of the test you wish to run. NOTE: test5, as per the project specifications, finds and returns an error. <br><br>Similarly, the `make run` command compiles and runs some random tests.<br><br>
A `make clean` command will remove all object and executable files. -->
