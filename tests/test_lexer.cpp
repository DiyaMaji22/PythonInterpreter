#include "../lexer/Lexer.h"
#include <cassert>
#include <iostream>

using namespace std;

void printTokens(const vector<Token>& tokens) {
    for (const auto& token : tokens) {
        cout << token.toString() << endl;
    }
}

// Test 1: Simple keywords and identifiers
void testKeywordsAndIdentifiers() {
    cout << "\n=== Test 1: Keywords and Identifiers ===" << endl;
    string code = "if x else y def foo print";
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    
    assert(tokens[0].type == TokenType::KW_IF);
    assert(tokens[1].type == TokenType::IDENTIFIER);
    assert(tokens[2].type == TokenType::KW_ELSE);
    cout << "[PASS]" << endl;
}

// Test 2: Arithmetic operators
void testArithmeticOperators() {
    cout << "\n=== Test 2: Arithmetic Operators ===" << endl;
    string code = "1 + 2 * 3 / 4 % 5 ** 2 // 3";
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    
    assert(tokens[0].type == TokenType::INTEGER);
    assert(tokens[1].type == TokenType::PLUS);
    assert(tokens[2].type == TokenType::INTEGER);
    assert(tokens[3].type == TokenType::STAR);
    assert(tokens[6].type == TokenType::DOUBLE_STAR);
    cout << "[PASS]" << endl;
}

// Test 3: Comparison operators
void testComparisonOperators() {
    cout << "\n=== Test 3: Comparison Operators ===" << endl;
    string code = "x == y != z < a <= b > c >= d";
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    
    assert(tokens[1].type == TokenType::EQ_EQ);
    assert(tokens[3].type == TokenType::BANG_EQ);
    assert(tokens[5].type == TokenType::LESS);
    assert(tokens[8].type == TokenType::GREATER_EQ);
    cout << "[PASS]" << endl;
}

// Test 4: Numbers (integers and floats)
void testNumbers() {
    cout << "\n=== Test 4: Numbers ===" << endl;
    string code = "42 3.14 100 2.5";
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    
    assert(tokens[0].type == TokenType::INTEGER);
    assert(tokens[1].type == TokenType::FLOAT);
    assert(tokens[2].type == TokenType::INTEGER);
    assert(tokens[3].type == TokenType::FLOAT);
    cout << "✓ Passed" << endl;
}

// Test 5: Strings
void testStrings() {
    cout << "\n=== Test 5: Strings ===" << endl;
    string code = R"(message = "hello world" text = 'single quote')";
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    
    // Check for STRING tokens
    int stringCount = 0;
    for (const auto& token : tokens) {
        if (token.type == TokenType::STRING) stringCount++;
    }
    assert(stringCount >= 2);
    cout << "[PASS]" << endl;
}

// Test 6: Booleans and None
void testBooleansAndNone() {
    cout << "\n=== Test 6: Booleans and None ===" << endl;
    string code = "True False None and or not";
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    
    assert(tokens[0].type == TokenType::BOOLEAN);
    assert(tokens[1].type == TokenType::BOOLEAN);
    assert(tokens[2].type == TokenType::KW_NONE);
    assert(tokens[3].type == TokenType::KW_AND);
    cout << "[PASS]" << endl;
}

// Test 7: Punctuation
void testPunctuation() {
    cout << "\n=== Test 7: Punctuation ===" << endl;
    string code = "( ) : , = [ ]";
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    
    assert(tokens[0].type == TokenType::LPAREN);
    assert(tokens[1].type == TokenType::RPAREN);
    assert(tokens[2].type == TokenType::COLON);
    assert(tokens[3].type == TokenType::COMMA);
    cout << "[PASS]" << endl;
}

// Test 8: Simple function definition
void testFunctionDefinition() {
    cout << "\n=== Test 8: Function Definition ===" << endl;
    string code = "def add(a, b):\n    return a + b";
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    
    assert(tokens[0].type == TokenType::KW_DEF);
    assert(tokens[1].type == TokenType::IDENTIFIER);
    assert(tokens[2].type == TokenType::LPAREN);
    cout << "[PASS]" << endl;
}

// Test 9: If statement
void testIfStatement() {
    cout << "\n=== Test 9: If Statement ===" << endl;
    string code = "if x > 5:\n    print(x)\nelif x < 0:\n    print(-x)\nelse:\n    print(0)";
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    
    int ifCount = 0, elifCount = 0, elseCount = 0;
    for (const auto& token : tokens) {
        if (token.type == TokenType::KW_IF) ifCount++;
        if (token.type == TokenType::KW_ELIF) elifCount++;
        if (token.type == TokenType::KW_ELSE) elseCount++;
    }
    assert(ifCount >= 1);
    assert(elifCount >= 1);
    assert(elseCount >= 1);
    cout << "[PASS]" << endl;
}

// Test 10: Assignment
void testAssignment() {
    cout << "\n=== Test 10: Assignment ===" << endl;
    string code = "x = 10\ny = 20\nz = x + y";
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    
    int assignCount = 0;
    for (const auto& token : tokens) {
        if (token.type == TokenType::EQUAL) assignCount++;
    }
    assert(assignCount >= 3);
    cout << "[PASS]" << endl;
}

// Test 11: Comments are skipped
void testComments() {
    cout << "\n=== Test 11: Comments ===" << endl;
    string code = "x = 5  # this is a comment\ny = 10";
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    
    // Comments should be skipped, not appear as tokens
    for (const auto& token : tokens) {
        assert(token.lexeme.find("#") == string::npos);
    }
    cout << "[PASS]" << endl;
}

int main() {
    try {
        testKeywordsAndIdentifiers();
        testArithmeticOperators();
        testComparisonOperators();
        testNumbers();
        testStrings();
        testBooleansAndNone();
        testPunctuation();
        testFunctionDefinition();
        testIfStatement();
        testAssignment();
        testComments();
        
        cout << "\n" << string(50, '=') << endl;
        cout << "[SUCCESS] All tests passed!" << endl;
        cout << string(50, '=') << endl;
        return 0;
    } catch (const exception& e) {
        cerr << "[ERROR] Test failed: " << e.what() << endl;
        return 1;
    }
}
