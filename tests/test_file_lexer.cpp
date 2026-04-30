#include "../lexer/Lexer.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

string readFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filePath);
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void testPythonFile(const string& filePath) {
    cout << "\n" << string(60, '=') << endl;
    cout << "Testing: " << filePath << endl;
    cout << string(60, '=') << endl;
    
    string code = readFile(filePath);
    cout << "\nSource code:" << endl;
    cout << code << endl;
    cout << "\nTokens:" << endl;
    cout << string(60, '-') << endl;
    
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    
    for (size_t i = 0; i < tokens.size(); i++) {
        cout << "[" << i << "] " << tokens[i].toString() << endl;
    }
    
    cout << "\nTotal tokens: " << tokens.size() << endl;
}

int main() {
    try {
        testPythonFile("programs/hello.py");
        testPythonFile("programs/factorial.py");
        testPythonFile("programs/fibonacci.py");
        
        cout << "\n" << string(60, '=') << endl;
        cout << "[SUCCESS] All files tokenized successfully!" << endl;
        cout << string(60, '=') << endl;
        return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
