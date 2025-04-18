#include "Symbol.h"
#include <string.h>

const char* Symbols[SymbolsCount] = {
#define SYMBOL(SymbolName, SymbolCharacters, SymbolBlockMax, tokenType) \
    [SymbolName##Symbol] = SymbolCharacters,
    SymbolsList
#undef SYMBOL
    /*Expands to :
            [UnknownSymbol] = "" ,
            [NumberSymbol] = "0123456789",
            ...etc
    */
};

const char* SymbolNameTable[SymbolsCount] = {
#define SYMBOL(SymbolName, CharacterSet, MaxLength, tokenType) \
    [SymbolName##Symbol] = #SymbolName,
    SymbolsList
#undef SYMBOL
};

const TokenType SymbolTokenTable[SymbolsCount] = {
#define SYMBOL(SymbolName, CharacterSet, MaxLength, tokenType) \
    [SymbolName##Symbol] = tokenType,
    SymbolsList
#undef SYMBOL
};

const TokenType GetSymbolTokenType(Symbol symbol)
{
    return SymbolTokenTable[symbol];
}

const char* GetSymbolName(Symbol symbol)
{
    return SymbolNameTable[symbol];
}

void InitSymbolsTable()
{
    // The table is initialized by mapping each character (using its unicode value as an index) to its corresponding Symbol.

    // All characters are unknown by default
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        SymbolsTable[i] = UnknownSymbol;
    }

    // Using the Symbols array to initialize the SymbolsTable.
    // Symbols array is a mapping from each Symbol to its corresponding character set.
    for (int symbolIdx = 0; symbolIdx < SymbolsCount; symbolIdx++) {
        const char* Characters = Symbols[symbolIdx];
        size_t CharactersCount = strlen(Characters);
        for (int i = 0; i < CharactersCount; i++) {
            char Character = Characters[i];
            SymbolsTable[Character] = symbolIdx;
        }
    }
}

Symbol GetSymbol(char Character)
{
    if (Character >= SYMBOL_TABLE_SIZE) {
        return UnknownSymbol;
    }

    return SymbolsTable[Character];
}