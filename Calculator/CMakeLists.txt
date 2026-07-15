cmake_minimum_required(VERSION 3.10)
project(Calculator C)

set(CMAKE_C_STANDARD 11)

add_executable(Calculator 
        main.c
        Lexer/Lexer.c
        Lexer/NumberTokenProcessor.c
        Lexer/Symbol.c
        Lexer/SymbolBlock.c
        Lexer/SymbolHandlers.c
        Parser/ASTNode.c
        Parser/ASTNodeStack.c
        Parser/ASTPool.c
        Parser/Parser.c
        Parser/Priority.c
        Parser/TokenHandlers.c
        LexerParserShared/Token.c
        Utils/ErrorPrinter.c
        Calculate/Calculate.c
        Calculate/Math.c
        Calculate/Number.c
)

target_link_libraries(Calculator PRIVATE m)