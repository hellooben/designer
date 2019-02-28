# CS 403
## Designer Programming Language Final Milestone: Evaluator

The final installment of our DPL is the Evaluator, which traverses the parse tree and actually executes the program.<br><br>

### BEAN: Language Specifics
A C-based language, with some small differences.<br>
- Everything is run through the main function
- End statements with a '!'
- Comments begin and end with a '?'
- Variable definition: dynamically typed; `var num = 123!`, `var string = "string"!`, `var another = 1.23!`
- Array definition: `var list[1, 2, 3, 4, 5, 10]!`, `var list[]!`, `var list["hi", "hello"]!`; all items in the array must be of the same type
- Function definition: `method MMM(?arguments?) {?block?}!`, where `MMM` is the name of the function being defined
- Function calls: `MMM(?arguments?)!`, where `MMM` is the name of the function being called
- If statements, For loops, and While loops all end with an '!'
<br>

There are Built-In functions:<br>
- `print(UNARY)`: takes a variable, string, integer, or real and prints it to the command line; if no argument is passed, prints a newline
- `printNewLine()`: takes no arguments; prints a newline
- `openFileForReading(STRING)`: takes a string argument that is the name of a file, opens it, and returns a FP (FILEPOINTER) type
- `readInteger(FP)`: takes an FP type, reads an integer from the file, and returns the integer
- `atFileEnd(FP)`: takes an FP type and returns a BOOLEAN yes/no whether or not the file is at EOF
- `closeFile(FP)`: takes an FP type and closes the file
- `getArgCount()`: takes no arguments, returns the number of command line arguments passed to the BEAN language script
- `getArg(INT)`: takes an integer argument that would be the index of the command line argument desired, returns a UNARY that was passed (if it exists)
<br><br>
