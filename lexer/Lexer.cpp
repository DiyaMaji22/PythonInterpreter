#include "Lexer.h"
#include <cctype>
#include <iostream>

// Keyword map definition
const unordered_map<string, TokenType> Lexer::keywords = {
    {"if", TokenType::KW_IF},
    {"else", TokenType::KW_ELSE},
    {"elif", TokenType::KW_ELIF},
    {"while", TokenType::KW_WHILE},
    {"def", TokenType::KW_DEF},
    {"return", TokenType::KW_RETURN},
    {"print", TokenType::KW_PRINT},
    {"True", TokenType::KW_TRUE},
    {"False", TokenType::KW_FALSE},
    {"None", TokenType::KW_NONE},
    {"and", TokenType::KW_AND},
    {"or", TokenType::KW_OR},
    {"not", TokenType::KW_NOT},
};

// Constructor
Lexer::Lexer(const string& src) : source(src) {}

// Main tokenization entry point
vector<Token> Lexer::tokenize() {
    while (!isAtEnd()) {
        if (atLineStart) {
            handleIndentation();
            atLineStart = false;
        }
        scanToken();
    }

    // Emit remaining DEDENT tokens
    while (indentStack.size() > 1) {
        indentStack.pop_back();
        addToken(TokenType::DEDENT);
    }

    addToken(TokenType::END_OF_FILE);
    return tokens;
}

// Utility methods
char Lexer::advance() {
    if (isAtEnd()) return '\0';
    char c = source[current++];
    if (c == '\n') {
        line++;
        col = 1;
    } else {
        col++;
    }
    return c;
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Lexer::peekNext() const {
    if (current + 1 >= source.size()) return '\0';
    return source[current + 1];
}

bool Lexer::isAtEnd() const {
    return current >= source.size();
}

bool Lexer::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;
    advance();
    return true;
}

string Lexer::currentLexeme() const {
    return source.substr(start, current - start);
}

// Character classification
bool Lexer::isDigit(char c) {
    return isdigit(c);
}

bool Lexer::isAlpha(char c) {
    return isalpha(c) || c == '_';
}

bool Lexer::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

// Token management
void Lexer::addToken(TokenType type) {
    string lexeme = currentLexeme();
    int tokenCol = col - (int)lexeme.length();
    tokens.emplace_back(type, lexeme, line, tokenCol);
}

void Lexer::addToken(TokenType type, LiteralValue value) {
    string lexeme = currentLexeme();
    int tokenCol = col - (int)lexeme.length();
    tokens.emplace_back(type, lexeme, value, line, tokenCol);
}

// Handle indentation (Python-specific)
void Lexer::handleIndentation() {
    if (peek() == '\n' || isAtEnd() || peek() == '#') {
        // Skip blank lines and comments
        if (peek() == '#') {
            while (!isAtEnd() && peek() != '\n') advance();
        }
        if (!isAtEnd() && peek() == '\n') {
            advance();
            addToken(TokenType::NEWLINE);
            atLineStart = true;
        }
        return;
    }

    int spaces = 0;
    while (!isAtEnd() && peek() == ' ') {
        spaces++;
        advance();
    }

    // Ignore indentation on empty lines
    if (isAtEnd() || peek() == '\n' || peek() == '#') {
        return;
    }

    int currentIndent = indentStack.back();

    if (spaces > currentIndent) {
        indentStack.push_back(spaces);
        addToken(TokenType::INDENT);
    } else if (spaces < currentIndent) {
        emitDedentTokens(spaces);
    }
}

void Lexer::emitDedentTokens(int targetIndent) {
    while (indentStack.size() > 1 && indentStack.back() > targetIndent) {
        indentStack.pop_back();
        addToken(TokenType::DEDENT);
    }
}

// Main scanning dispatch
void Lexer::scanToken() {
    start = current;
    char c = advance();

    switch (c) {
        case '(': addToken(TokenType::LPAREN); break;
        case ')': addToken(TokenType::RPAREN); break;
        case ':': addToken(TokenType::COLON); break;
        case ',': addToken(TokenType::COMMA); break;
        case '%': addToken(TokenType::PERCENT); break;
        case '+': addToken(TokenType::PLUS); break;
        case '-': addToken(TokenType::MINUS); break;

        case '*':
            if (match('*')) {
                addToken(TokenType::DOUBLE_STAR);
            } else {
                addToken(TokenType::STAR);
            }
            break;

        case '/':
            if (match('/')) {
                addToken(TokenType::DOUBLE_SLASH);
            } else {
                addToken(TokenType::SLASH);
            }
            break;

        case '=':
            if (match('=')) {
                addToken(TokenType::EQ_EQ);
            } else {
                addToken(TokenType::EQUAL);
            }
            break;

        case '!':
            if (match('=')) {
                addToken(TokenType::BANG_EQ);
            }
            break;

        case '<':
            if (match('=')) {
                addToken(TokenType::LESS_EQ);
            } else {
                addToken(TokenType::LESS);
            }
            break;

        case '>':
            if (match('=')) {
                addToken(TokenType::GREATER_EQ);
            } else {
                addToken(TokenType::GREATER);
            }
            break;

        case '#':
            // Comment - skip to end of line
            while (!isAtEnd() && peek() != '\n') advance();
            break;

        case ' ':
        case '\r':
        case '\t':
            // Whitespace (ignore outside of indentation)
            break;

        case '\n':
            addToken(TokenType::NEWLINE);
            atLineStart = true;
            break;

        case '"':
        case '\'':
            scanString(c);
            break;

        default:
            if (isDigit(c)) {
                current--;  // Back up to re-process the digit
                col--;
                scanNumber();
            } else if (isAlpha(c)) {
                current--;  // Back up to re-process the letter
                col--;
                scanIdentifierOrKeyword();
            }
            break;
    }
}

// Scan string literals
void Lexer::scanString(char quote) {
    string value;
    while (!isAtEnd() && peek() != quote) {
        if (peek() == '\\') {
            advance();
            if (!isAtEnd()) {
                char escaped = advance();
                switch (escaped) {
                    case 'n': value += '\n'; break;
                    case 't': value += '\t'; break;
                    case 'r': value += '\r'; break;
                    case '\\': value += '\\'; break;
                    case '"': value += '"'; break;
                    case '\'': value += '\''; break;
                    default: value += escaped; break;
                }
            }
        } else {
            value += advance();
        }
    }

    if (isAtEnd()) {
        // Unterminated string - could emit error
        return;
    }

    advance();  // Closing quote
    addToken(TokenType::STRING, LiteralValue(value));
}

// Scan numeric literals
void Lexer::scanNumber() {
    start = current;
    while (isDigit(peek())) advance();

    // Check for float
    if (peek() == '.' && isDigit(peekNext())) {
        advance();  // Consume '.'
        while (isDigit(peek())) advance();

        double value = stod(currentLexeme());
        addToken(TokenType::FLOAT, LiteralValue(value));
    } else {
        int value = stoi(currentLexeme());
        addToken(TokenType::INTEGER, LiteralValue(value));
    }
}

// Scan identifiers and keywords
void Lexer::scanIdentifierOrKeyword() {
    start = current;
    while (isAlphaNumeric(peek())) advance();

    string text = currentLexeme();

    // Check if it's a keyword
    auto it = keywords.find(text);
    if (it != keywords.end()) {
        TokenType type = it->second;
        // Special handling for boolean keywords
        if (type == TokenType::KW_TRUE) {
            addToken(TokenType::BOOLEAN, LiteralValue(true));
        } else if (type == TokenType::KW_FALSE) {
            addToken(TokenType::BOOLEAN, LiteralValue(false));
        } else {
            addToken(type);
        }
    } else {
        addToken(TokenType::IDENTIFIER);
    }
}

