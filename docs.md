q1:why i chose to write the code in cpp out of every other language?
C++ gives low-level memory control, which is very useful in compiler or interpreter development because you often need to manage tokens, syntax trees, symbol tables, stacks, and scopes efficiently.

It supports both procedural and object-oriented programming, so you can structure components like lexer, parser, AST nodes, and interpreter classes in a clean way.

The Standard Template Library in C++ provides ready-to-use data structures such as vectors, maps, stacks, queues, and sets, which are heavily used in compiler design.

C++ is faster than many high-level languages because it is compiled and gives direct control over memory allocation. This matters when interpreting or compiling larger programs.

Recursive algorithms, tree traversal, graph structures, and parsing logic are easier to implement efficiently in C++.

Since compilers and interpreters involve many interconnected components, the class system in C++ helps organize code better than plain C.

It has strong type checking, which reduces bugs when building large systems with many classes, tokens, node types, and parser rules.

Many real compiler tools and infrastructures are built using C++, such as LLVM, Clang, and parts of GCC, so learning compiler construction in C++ matches industry practices.

C++ lets you balance performance with abstraction. You can write very low-level optimized code when needed, but still use high-level OOP patterns for maintainability.

It is widely used in systems programming, game engines, compilers, operating systems, embedded systems, and high-performance backend applications, so the skills you gain from such a project are transferable to many technical domains.
(Also it is the language i generally do my DSA so i was kinda comfortable in the medium)


steps that i will follow this entire procedure:->
1.build the lexer or tokeniser which will read raw source code character by character and breaks in tokens (lexer breaks code into pieces like keywords,numbers,operators,identifier,strings)
2.create the parser 
takes token from the lexer and checks whether the syntax is valid
3.design ast node classes in c++
4.build a symbol table which will store the variables and functions during execution 
5.create an interpreter or evaluator (kinda the core part)
6.add scope handling 
7.handle errors properly
8.add advanced features gradually (which includes 
Lists and dictionaries
Classes and objects
Inheritance
File handling
Modules
Exception handling
Lambda functions)
9.Make a simple REPL.A REPL stands for Read, Evaluate, Print, Loop. It lets users type code line by line like the real Python shell.

q3:was confused what is the difference between the cpp file and h file ?
yes, .h (header) files and .cpp (C++) files are different and serve distinct purposes in C++ programming: 
.h files (Header Files): These files typically contain declarations, class definitions, function prototypes, and other interface details. They describe the architecture of a program. A single header file is intended to be included by many different .cpp files.
.cpp files (Source/Implementation Files): These files contain the actual implementation of the functions and methods declared in the corresponding header files. They define the functionality that the header files describe.
During compilation, the preprocessor effectively copies the entire content of the .h file into every .cpp file that uses an #include directive for it.

#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H
#endif  what does this mean?
In C/C++, this is called an include guard. It prevents a header file from being included multiple times in the same program. 
#ifndef TOKEN_TYPE_H means "if TOKEN_TYPE_H is not defined" 
#define TOKEN_TYPE_H defines that name
#endif closes the condition


