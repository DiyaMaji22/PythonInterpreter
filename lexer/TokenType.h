#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H


enum class TokenType{
    INTEGER,        // 42
    FLOAT,          // 3.14
    STRING,         // "hello"
    BOOLEAN,        // True / False
    NONE_VAL,       // None (reserved for future use)
 
    //  Identifiers & Keywords 
    IDENTIFIER,     // variable / function names
 
    KW_IF,          // if
    KW_ELSE,        // else
    KW_ELIF,        // elif
    KW_WHILE,       // while
    KW_DEF,         // def
    KW_RETURN,      // return
    KW_PRINT,       // print  (treated as keyword in v1)
    KW_TRUE,        // True
    KW_FALSE,       // False
    KW_NONE,        // None
    KW_AND,         // and
    KW_OR,          // or
    KW_NOT,         // not
 
    //  Arithmetic Operators 
    PLUS,           // +
    MINUS,          // -
    STAR,           // *
    SLASH,          // /
    PERCENT,        // %
    DOUBLE_STAR,    // **  (power)
    DOUBLE_SLASH,   // //  (floor division)
 
    //  Comparison Operators 
    EQ_EQ,          // ==
    BANG_EQ,        // !=
    LESS,           // <
    LESS_EQ,        // <=
    GREATER,        // >
    GREATER_EQ,     // >=
 
    //  Assignment 
    EQUAL,          // =
 

    LPAREN,         // (
    RPAREN,         // )
    COLON,          // :
    COMMA,          // ,
 
    // Structure 
    NEWLINE,        // \n  (Python is newline-sensitive)
    INDENT,         // increased indentation
    DEDENT,         // decreased indentation
    END_OF_FILE     // EOF sentinel
};

#endif
