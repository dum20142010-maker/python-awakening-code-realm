// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#include "TestCaseRunner.h"

bool UTestCaseRunner::RunTestCase(const FString& Code, const FString& Input, const FString& ExpectedOutput, FString& OutActualOutput)
{
    // TODO: Execute code with input and capture output
    OutActualOutput = TEXT("");
    return OutActualOutput.Equals(ExpectedOutput);
}

int32 UTestCaseRunner::RunTestCases(const FString& Code, const TArray<FString>& TestCases, TArray<bool>& OutResults)
{
    int32 PassedCount = 0;
    OutResults.Empty();

    for (const FString& TestCase : TestCases)
    {
        FString ActualOutput;
        bool bPassed = RunTestCase(Code, TEXT(""), TestCase, ActualOutput);
        OutResults.Add(bPassed);
        if (bPassed)
        {
            PassedCount++;
        }
    }

    return PassedCount;
}

FString UTestCaseRunner::GetTestFeedback(bool bPassed, const FString& Expected, const FString& Actual)
{
    if (bPassed)
    {
        return TEXT("✓ Test passed!");
    }
    else
    {
        return FString::Printf(
            TEXT("✗ Test failed!\nExpected: %s\nActual: %s"),
            *Expected, *Actual
        );
    }
}