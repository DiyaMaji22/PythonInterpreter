#!/bin/bash
# Compile and run lexer unit tests

cd "$(dirname "$0")"

echo "Compiling unit tests..."
g++ -std=c++17 -Wall -Wextra test_lexer.cpp ../lexer/Lexer.cpp -o test_lexer

if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo ""
    echo "Running unit tests..."
    echo "================================"
    ./test_lexer
else
    echo "✗ Compilation failed!"
    exit 1
fi
