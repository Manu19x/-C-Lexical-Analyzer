# -C-Lexical-Analyzer

Certainly! Below is a project description for your lexical analyzer implemented in C, formatted to resemble a project description on a CV:

Lexical Analyzer for C Source Code
#Overview:
Implemented a lexical analyzer in C for scanning C source code, identifying and categorizing various lexical symbols. The program employs state machines to recognize identifiers, arithmetic operators, special characters, keywords, and handle lexical errors.

Key Achievements:

# Token Types:

Defined an enumeration, TipToken, to represent distinct lexical symbol types, including IDENTIFIER, ARITHMETIC_OPERATOR, SPECIAL_CHAR, KEYWORD, LEXICAL_ERROR, and EOF_TOKEN.
Structured a Token to encapsulate the token type and associated value.

# Keyword Recognition:

Created an array of keywords (cuvinteCheie) for the identification of reserved words within the C language.
#Validation Functions:

Implemented functions to check if a word is a keyword (esteCuvantCheie), if a character is an arithmetic operator (esteOperatorAritmetic), if a character is valid for an identifier (esteCaracterValidPentruIdentificator), if a character is special (esteCaracterSpecial), and if a character is a separator (esteSeparator).

# Lexical Analysis:

Developed the analizaLexicala function, which processes a source file and returns tokens iteratively.
Employed a state machine to analyze each character, identifying the appropriate token type and value.
#Main Function:

Opened a source file for lexical analysis.
Utilized a loop to repeatedly call analizaLexicala until an EOF_TOKEN is encountered or a lexical error is detected.
Displayed the type and value of each identified token.
# Error Handling:

Implemented a mechanism to generate a LEXICAL_ERROR token if unexpected situations occurred during analysis.
# File Closure:

Ensured proper closure of the source file after lexical analysis.
# Conclusion:
This lexical analyzer effectively recognizes identifiers, arithmetic operators, special characters, and keywords within C source code. It is designed to be a crucial component in the compilation process, transforming source code into a sequence of easily manageable lexical symbols for subsequent compilation phases.
