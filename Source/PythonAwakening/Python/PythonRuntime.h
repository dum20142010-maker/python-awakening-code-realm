// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PythonRuntime.generated.h"

class UCodeValidator;
class UTestCaseRunner;

/**
 * Python Runtime Execution System
 * Handles safe, sandboxed Python code execution for gameplay
 * 
 * Features:
 * - Syntax validation
 * - Safe execution (no file/network/OS access)
 * - Output capture
 * - Test case validation
 * - Error reporting
 * - Execution timeout
 * - Memory limits
 */
UEUM_ENUM()
enum class EPythonExecutionResult : uint8
{
    Success = 0,
    SyntaxError = 1,
    RuntimeError = 2,
    TimeoutError = 3,
    MemoryError = 4,
    ValidationError = 5,
    UnknownError = 6
};

USTRUCT(BlueprintType)
struct FPythonExecutionOutput
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Python")
    EPythonExecutionResult ExecutionResult;

    UPROPERTY(BlueprintReadOnly, Category = "Python")
    FString Output;

    UPROPERTY(BlueprintReadOnly, Category = "Python")
    FString ErrorMessage;

    UPROPERTY(BlueprintReadOnly, Category = "Python")
    float ExecutionTime;

    UPROPERTY(BlueprintReadOnly, Category = "Python")
    bool bTestCasesPass;

    UPROPERTY(BlueprintReadOnly, Category = "Python")
    int32 PassedTestCases;

    UPROPERTY(BlueprintReadOnly, Category = "Python")
    int32 TotalTestCases;
};

UCLASS()
class PYTHONAWAKENING_API UPythonRuntime : public UObject
{
    GENERATED_BODY()

public:
    UPythonRuntime();

    // Initialize the runtime
    UFUNCTION(BlueprintCallable, Category = "Python")
    void Initialize();

    // Execute Python code
    UFUNCTION(BlueprintCallable, Category = "Python")
    FPythonExecutionOutput ExecuteCode(const FString& Code);

    // Execute code with test cases
    UFUNCTION(BlueprintCallable, Category = "Python")
    FPythonExecutionOutput ExecuteCodeWithTests(const FString& Code, const TArray<FString>& TestCases);

    // Validate code syntax only
    UFUNCTION(BlueprintCallable, Category = "Python")
    bool ValidateCodeSyntax(const FString& Code, FString& OutErrorMessage);

    // Get sandbox restrictions
    UFUNCTION(BlueprintCallable, Category = "Python")
    FString GetSandboxInfo() const;

    // Set execution timeout (in milliseconds)
    UFUNCTION(BlueprintCallable, Category = "Python")
    void SetExecutionTimeout(int32 TimeoutMs);

    // Set memory limit (in MB)
    UFUNCTION(BlueprintCallable, Category = "Python")
    void SetMemoryLimit(int32 MemoryMB);

    // Get execution statistics
    UFUNCTION(BlueprintCallable, Category = "Python")
    int32 GetTotalExecutions() const { return TotalExecutions; }

    UFUNCTION(BlueprintCallable, Category = "Python")
    int32 GetSuccessfulExecutions() const { return SuccessfulExecutions; }

    UFUNCTION(BlueprintCallable, Category = "Python")
    int32 GetFailedExecutions() const { return FailedExecutions; }

private:
    // Sandbox security
    void SetupSandbox();
    void ValidateSandbox(const FString& Code, FString& OutErrorMessage) const;
    bool ContainsBannedImports(const FString& Code) const;
    bool ContainsDangerousFunctions(const FString& Code) const;

    // Execution helpers
    FPythonExecutionOutput ExecuteInternal(const FString& Code);
    void CaptureOutput(FString& OutOutput);
    void HandleExecutionError(const FString& ErrorMessage, FPythonExecutionOutput& OutOutput);

    // Configuration
    UPROPERTY()
    int32 ExecutionTimeoutMs;

    UPROPERTY()
    int32 MemoryLimitMB;

    // Statistics
    UPROPERTY()
    int32 TotalExecutions;

    UPROPERTY()
    int32 SuccessfulExecutions;

    UPROPERTY()
    int32 FailedExecutions;

    // Banned modules (security)
    UPROPERTY()
    TArray<FString> BannedModules;

    // Banned functions (security)
    UPROPERTY()
    TArray<FString> BannedFunctions;

    // Allowed built-in functions
    UPROPERTY()
    TArray<FString> AllowedBuiltins;
};