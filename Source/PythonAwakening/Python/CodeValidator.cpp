// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#include "CodeValidator.h"

bool UCodeValidator::ValidateSyntax(const FString& Code, FString& OutErrorMessage)
{
    if (!CheckBracketBalance(Code, OutErrorMessage))
    {
        return false;
    }

    if (!CheckIndentation(Code, OutErrorMessage))
    {
        return false;
    }

    if (!CheckKeywordUsage(Code, OutErrorMessage))
    {
        return false;
    }

    OutErrorMessage = TEXT("");
    return true;
}

bool UCodeValidator::CheckInfiniteLoops(const FString& Code, FString& OutWarning)
{
    // Check for while True without break
    if (Code.Contains(TEXT("while True")) && !Code.Contains(TEXT("break")))
    {
        OutWarning = TEXT("Warning: Potential infinite loop detected");
        return false;
    }

    return true;
}

int32 UCodeValidator::CalculateCodeComplexity(const FString& Code)
{
    int32 Complexity = 0;
    
    // Count conditionals
    Complexity += Code.Contains(TEXT("if")) ? 1 : 0;
    Complexity += Code.Contains(TEXT("elif")) ? 1 : 0;
    Complexity += Code.Contains(TEXT("else")) ? 1 : 0;
    
    // Count loops
    Complexity += Code.Contains(TEXT("for")) ? 2 : 0;
    Complexity += Code.Contains(TEXT("while")) ? 2 : 0;
    
    // Count functions
    Complexity += Code.Contains(TEXT("def")) ? 3 : 0;

    return Complexity;
}

FString UCodeValidator::AnalyzeCodeStructure(const FString& Code)
{
    FString Analysis = TEXT("Code Analysis:\n");
    
    int32 Lines = 1;
    for (int32 i = 0; i < Code.Len(); ++i)
    {
        if (Code[i] == '\n')
        {
            Lines++;
        }
    }
    
    Analysis += FString::Printf(TEXT("- Lines: %d\n"), Lines);
    Analysis += FString::Printf(TEXT("- Complexity: %d\n"), CalculateCodeComplexity(Code));
    Analysis += FString::Printf(TEXT("- Contains functions: %s\n"), Code.Contains(TEXT("def")) ? TEXT("Yes") : TEXT("No"));
    Analysis += FString::Printf(TEXT("- Contains loops: %s\n"), (Code.Contains(TEXT("for")) || Code.Contains(TEXT("while"))) ? TEXT("Yes") : TEXT("No"));
    Analysis += FString::Printf(TEXT("- Contains conditionals: %s"), (Code.Contains(TEXT("if")) || Code.Contains(TEXT("else"))) ? TEXT("Yes") : TEXT("No"));

    return Analysis;
}

bool UCodeValidator::CheckBracketBalance(const FString& Code, FString& OutError)
{
    int32 ParenCount = 0;
    int32 BraceCount = 0;
    int32 BracketCount = 0;

    for (int32 i = 0; i < Code.Len(); ++i)
    {
        switch (Code[i])
        {
            case '(':
                ParenCount++;
                break;
            case ')':
                ParenCount--;
                break;
            case '{':
                BraceCount++;
                break;
            case '}':
                BraceCount--;
                break;
            case '[':
                BracketCount++;
                break;
            case ']':
                BracketCount--;
                break;
        }

        if (ParenCount < 0 || BraceCount < 0 || BracketCount < 0)
        {
            OutError = TEXT("Bracket mismatch detected");
            return false;
        }
    }

    if (ParenCount != 0 || BraceCount != 0 || BracketCount != 0)
    {
        OutError = TEXT("Unclosed brackets detected");
        return false;
    }

    return true;
}

bool UCodeValidator::CheckIndentation(const FString& Code, FString& OutError)
{
    // TODO: Implement proper Python indentation checking
    OutError = TEXT("");
    return true;
}

bool UCodeValidator::CheckKeywordUsage(const FString& Code, FString& OutError)
{
    // TODO: Implement keyword validation
    OutError = TEXT("");
    return true;
}