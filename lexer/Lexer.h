#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include "TokenType.h"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Lexer{
    public:
        Lexer(const string& src);
        vector<Token> tokenize();

    private:
        // Member variables
        string source;
        size_t current = 0;
        size_t start = 0;
        int line = 1;
        int col = 1;
        vector<Token> tokens;
        vector<int> indentStack = {0};
        bool atLineStart = true;

        // Helper methods
        char advance();
        char peek() const;
        char peekNext() const;
        bool isAtEnd() const;
        bool match(char expected);

        void scanToken();
        void addToken(TokenType type);
        void addToken(TokenType type, LiteralValue value);

        void scanString(char quote);
        void scanNumber();
        void scanIdentifierOrKeyword();

        void handleIndentation();
        void emitDedentTokens(int targetIndent);

        static bool isDigit(char c);
        static bool isAlpha(char c);
        static bool isAlphaNumeric(char c);
        string currentLexeme() const;

        static const unordered_map<string, TokenType> keywords;
};

#endif