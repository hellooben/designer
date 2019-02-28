# CS 403
## Designer Programming Language Final Milestone: Evaluator

The final installment of our DPL is the Evaluator, which traverses the parse tree and actually executes the program.<br><br>

### BEAN: Language Specifics
#### A C-based language, with some small differences.
- File extension: `.bean`
- Everything is run through the main function
- End statements with a '!'
- Comments begin and end with a '?'
- Variable definition: dynamically typed; `var num = 123!`, `var string = "string"!`, `var another = 1.23!`
- Array definition: `var list[1, 2, 3, 4, 5, 10]!`, `var list[]!`, `var list["hi", "hello"]!`; all items in the array must be of the same type
- Function definition: `method MMM(?arguments?) {?block?}!`, where `MMM` is the name of the function being defined
- Function calls: `MMM(?arguments?)!`, where `MMM` is the name of the function being called
- If statements, For loops, and While loops all end with an '!' after the final closing brace
<br>

#### There are Built-In functions:
- `print(UNARY)`: takes a variable, string, integer, or real and prints it to the command line; if no argument is passed, prints a newline
- `printNewLine()`: takes no arguments; prints a newline
- `openFileForReading(STRING)`: takes a string argument that is the name of a file, opens it, and returns a FP (FILEPOINTER) type
- `readInteger(FP)`: takes an FP type, reads an integer from the file, and returns the integer
- `atFileEnd(FP)`: takes an FP type and returns a BOOLEAN yes/no whether or not the file is at EOF
- `closeFile(FP)`: takes an FP type and closes the file
- `getArgCount()`: takes no arguments, returns the number of command line arguments passed to the BEAN language script
- `getArg(INT)`: takes an integer argument that would be the index of the command line argument desired, returns a UNARY that was passed (if it exists)
<br>

#### Running Programs
A Makefile is provided with plenty of tests. They are outlined below.
- `make`: compiles the BEAN evaluator
- `error1`: prints the file e1.bean, demonstrates a syntax error (missing "!")
- `error1x`: demonstrates a syntax error(missing "!")
- `error2`: prints the file e2.bean, demonstrates a syntax error (unexpected character)
- `error2x`: demonstrates a syntax error (unexpected character)
- `error3`: prints the file e3.bean, demonstrates a syntax error (typed variable definition)
- `error3x`: demonstrates a syntax error (typed variable definition)
- `error4`: prints the file e4.bean
- `error4x`: demonstrates a semantic error (array access out of bounds)
- `error5`: prints the file e5.bean
- `error5x`: demonstrates a semantic error (array items are not all of the same type)
- `arrays`: prints the file arrays.bean
- `arraysx`: compiles and executes arrays.bean
- `conditionals`: prints the file conditionals.bean
- `conditionalsx`: compiles and executes conditionals.bean
- `functions`: prints the file function.bean
- `functionsx`: compiles and executes function.bean; examples include passing functions to function calls and also returning nested functions
- `recursion`: prints the file recursion.bean
- `recursionx`: compiles and executes recursion.bean
- `iteration`: prints the file iteration.bean
- `iterationx`: compiles and executes iteration.bean
- `lambda`: prints the file lambda.bean
- `lambdax`: compiles and executes lambda.bean
- `problem`: prints the file problem.bean
- `problemx`: compiles and executes problem.bean, which reads the file numbers.txt and prints the sum of all numbers found in the file<br>
If you want to run your own tests, you can! Simply write your program, run the `make` command to compile everything, and then run `run FFFF.bean <additional>`, where `FFFF` is the name of the .bean file, and `<additional>` are any additional command line arguments you wish to pass.
