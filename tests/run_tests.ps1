# Compile and run lexer unit tests
Push-Location $PSScriptRoot

Write-Host "Compiling unit tests..." -ForegroundColor Cyan
g++ -std=c++17 -Wall -Wextra test_lexer.cpp ../lexer/Lexer.cpp -o test_lexer.exe

if ($LASTEXITCODE -eq 0) {
    Write-Host "[SUCCESS] Compilation successful!" -ForegroundColor Green
    Write-Host ""
    Write-Host "Running unit tests..." -ForegroundColor Cyan
    Write-Host "================================" -ForegroundColor Gray
    ./test_lexer.exe
    exit $LASTEXITCODE
} else {
    Write-Host "[ERROR] Compilation failed!" -ForegroundColor Red
    exit 1
}

Pop-Location
