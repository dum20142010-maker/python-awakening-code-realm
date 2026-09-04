// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CodeValidator.generated.h"

/**
 * Code validation system for Python code
 * Checks syntax and sandbox compliance
 */
UCLASS()
class PYTHONAWAKENING_API UCodeValidator : public UObject
{
    GENERATED_BODY()

public:
    // Validate Python syntax
    UFUNCTION(BlueprintCallable, Category = "Code Validation")
    static bool ValidateSyntax(const FString& Code, FString& OutErrorMessage);

    // Check for infinite loops
    UFUNCTION(BlueprintCallable, Category = "Code Validation")
    static bool CheckInfiniteLoops(const FString& Code, FString& OutWarning);

    // Check code complexity
    UFUNCTION(BlueprintCallable, Category = "Code Validation")
    static int32 CalculateCodeComplexity(const FString& Code);

    // Analyze code structure
    UFUNCTION(BlueprintCallable, Category = "Code Validation")
    static FString AnalyzeCodeStructure(const FString& Code);

private:
    // Helper functions
    static bool CheckBracketBalance(const FString& Code, FString& OutError);
    static bool CheckIndentation(const FString& Code, FString& OutError);
    static bool CheckKeywordUsage(const FString& Code, FString& OutError);
};