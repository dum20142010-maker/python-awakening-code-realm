// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TestCaseRunner.generated.h"

/**
 * Test case runner for validating Python code against expected outputs
 */
UCLASS()
class PYTHONAWAKENING_API UTestCaseRunner : public UObject
{
    GENERATED_BODY()

public:
    // Run a single test case
    UFUNCTION(BlueprintCallable, Category = "Testing")
    static bool RunTestCase(const FString& Code, const FString& Input, const FString& ExpectedOutput, FString& OutActualOutput);

    // Run multiple test cases
    UFUNCTION(BlueprintCallable, Category = "Testing")
    static int32 RunTestCases(const FString& Code, const TArray<FString>& TestCases, TArray<bool>& OutResults);

    // Get test case feedback
    UFUNCTION(BlueprintCallable, Category = "Testing")
    static FString GetTestFeedback(bool bPassed, const FString& Expected, const FString& Actual);
};