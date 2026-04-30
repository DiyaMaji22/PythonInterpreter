#ifndef TOKEN_H
#define TOKEN_H

#include <cstddef>
#include <string>
#include <vector>
#include <variant>
#include "TokenType.h"

using namespace std;

// Helper function to convert TokenType to string
inline string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::INTEGER: return "INTEGER";
        case TokenType::FLOAT: return "FLOAT";
        case TokenType::STRING: return "STRING";
        case TokenType::BOOLEAN: return "BOOLEAN";
        case TokenType::NONE_VAL: return "NONE_VAL";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::KW_IF: return "KW_IF";
        case TokenType::KW_ELSE: return "KW_ELSE";
        case TokenType::KW_ELIF: return "KW_ELIF";
        case TokenType::KW_WHILE: return "KW_WHILE";
        case TokenType::KW_DEF: return "KW_DEF";
        case TokenType::KW_RETURN: return "KW_RETURN";
        case TokenType::KW_PRINT: return "KW_PRINT";
        case TokenType::KW_TRUE: return "KW_TRUE";
        case TokenType::KW_FALSE: return "KW_FALSE";
        case TokenType::KW_NONE: return "KW_NONE";
        case TokenType::KW_AND: return "KW_AND";
        case TokenType::KW_OR: return "KW_OR";
        case TokenType::KW_NOT: return "KW_NOT";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::STAR: return "STAR";
        case TokenType::SLASH: return "SLASH";
        case TokenType::PERCENT: return "PERCENT";
        case TokenType::DOUBLE_STAR: return "DOUBLE_STAR";
        case TokenType::DOUBLE_SLASH: return "DOUBLE_SLASH";
        case TokenType::EQ_EQ: return "EQ_EQ";
        case TokenType::BANG_EQ: return "BANG_EQ";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQ: return "LESS_EQ";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQ: return "GREATER_EQ";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::LPAREN: return "LPAREN";
        case TokenType::RPAREN: return "RPAREN";
        case TokenType::COLON: return "COLON";
        case TokenType::COMMA: return "COMMA";
        case TokenType::NEWLINE: return "NEWLINE";
        case TokenType::INDENT: return "INDENT";
        case TokenType::DEDENT: return "DEDENT";
        case TokenType::END_OF_FILE: return "EOF";
        default: return "UNKNOWN";
    }
}

// LiteralValue can be int, double, string, bool, or empty (monostate)
using LiteralValue = std::variant<std::monostate, int, double, std::string, bool>;

struct Token{
    TokenType type;
    string lexeme;
    LiteralValue value;  //parsed value (e.g., int, float, string content)
    int line;
    int col;

    Token(TokenType type,string lexeme,int line,int col) 
    {
        this->type=type;
        this->lexeme=lexeme;
        this->line=line;
        this->col=col;
    }
    Token (TokenType type,string lexeme,LiteralValue value,int line,int col)
    {
        this->type=type;
        this->lexeme=lexeme;
        this->value=value;
        this->line=line;
        this->col=col;
    }
     bool isLiteral() const{
        return type==TokenType::INTEGER || type==TokenType::FLOAT || type==TokenType::STRING || type==TokenType::BOOLEAN || type==TokenType::NONE_VAL;
     }
     string toString() const{
        return "Token("+tokenTypeToString(type)+", '"+lexeme+"', line "+to_string(line)+", col "+to_string(col)+")";
     }

    
};

#endif