// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#include "PythonRuntime.h"
#include "PythonAwakening/Python/CodeValidator.h"
#include "PythonAwakening/Python/TestCaseRunner.h"
#include "Misc/DateTime.h"

UPythonRuntime::UPythonRuntime()
    : ExecutionTimeoutMs(5000),
      MemoryLimitMB(256),
      TotalExecutions(0),
      SuccessfulExecutions(0),
      FailedExecutions(0)
{
}

void UPythonRuntime::Initialize()
{
    SetupSandbox();
    UE_LOG(LogTemp, Warning, TEXT("[PythonRuntime] Initialized with %dms timeout and %dMB memory limit"), ExecutionTimeoutMs, MemoryLimitMB);
}

FPythonExecutionOutput UPythonRuntime::ExecuteCode(const FString& Code)
{
    FPythonExecutionOutput Output;
    Output.ExecutionResult = EPythonExecutionResult::UnknownError;
    Output.Output = TEXT("");
    Output.ErrorMessage = TEXT("");
    Output.ExecutionTime = 0.0f;
    Output.bTestCasesPass = false;
    Output.PassedTestCases = 0;
    Output.TotalTestCases = 0;

    TotalExecutions++;

    // Validate code syntax
    FString ValidationError;
    if (!ValidateCodeSyntax(Code, ValidationError))
    {
        Output.ExecutionResult = EPythonExecutionResult::SyntaxError;
        Output.ErrorMessage = ValidationError;
        FailedExecutions++;
        UE_LOG(LogTemp, Error, TEXT("[PythonRuntime] Syntax error: %s"), *ValidationError);
        return Output;
    }

    // Validate sandbox restrictions
    if (!Code.IsEmpty())
    {
        FString SandboxError;
        ValidateSandbox(Code, SandboxError);
        if (!SandboxError.IsEmpty())
        {
            Output.ExecutionResult = EPythonExecutionResult::ValidationError;
            Output.ErrorMessage = SandboxError;
            FailedExecutions++;
            UE_LOG(LogTemp, Error, TEXT("[PythonRuntime] Sandbox violation: %s"), *SandboxError);
            return Output;
        }
    }

    // Execute code
    double StartTime = FPlatformTime::Seconds();
    Output = ExecuteInternal(Code);
    Output.ExecutionTime = (FPlatformTime::Seconds() - StartTime) * 1000.0; // Convert to milliseconds

    if (Output.ExecutionResult == EPythonExecutionResult::Success)
    {
        SuccessfulExecutions++;
    }
    else
    {
        FailedExecutions++;
    }

    UE_LOG(LogTemp, Warning, TEXT("[PythonRuntime] Execution completed: %s (%.2fms)"), 
            Output.ExecutionResult == EPythonExecutionResult::Success ? TEXT("Success") : TEXT("Failed"),
            Output.ExecutionTime);

    return Output;
}

FPythonExecutionOutput UPythonRuntime::ExecuteCodeWithTests(const FString& Code, const TArray<FString>& TestCases)
{
    FPythonExecutionOutput Output = ExecuteCode(Code);

    if (Output.ExecutionResult != EPythonExecutionResult::Success)
    {
        return Output;
    }

    // Run test cases
    Output.TotalTestCases = TestCases.Num();
    Output.PassedTestCases = 0;

    for (const FString& TestCase : TestCases)
    {
        // TODO: Implement test case validation
        // For now, assume all tests pass
        Output.PassedTestCases++;
    }

    Output.bTestCasesPass = (Output.PassedTestCases == Output.TotalTestCases);

    UE_LOG(LogTemp, Warning, TEXT("[PythonRuntime] Test cases: %d/%d passed"), 
            Output.PassedTestCases, Output.TotalTestCases);

    return Output;
}

bool UPythonRuntime::ValidateCodeSyntax(const FString& Code, FString& OutErrorMessage)
{
    if (Code.IsEmpty())
    {
        OutErrorMessage = TEXT("Code is empty");
        return false;
    }

    // TODO: Integrate with actual Python parser
    // For now, do basic syntax checks
    UE_LOG(LogTemp, Warning, TEXT("[PythonRuntime] Validating code syntax..."));
    return true;
}

FString UPythonRuntime::GetSandboxInfo() const
{
    FString Info = FString::Printf(
        TEXT("Python Sandbox Configuration:\n")
        TEXT("- Timeout: %dms\n")
        TEXT("- Memory Limit: %dMB\n")
        TEXT("- Banned Modules: %d\n")
        TEXT("- Banned Functions: %d\n")
        TEXT("- Allowed Builtins: %d"),
        ExecutionTimeoutMs, MemoryLimitMB, BannedModules.Num(), BannedFunctions.Num(), AllowedBuiltins.Num()
    );
    return Info;
}

void UPythonRuntime::SetExecutionTimeout(int32 TimeoutMs)
{
    ExecutionTimeoutMs = FMath::Max(100, TimeoutMs); // Minimum 100ms
    UE_LOG(LogTemp, Warning, TEXT("[PythonRuntime] Execution timeout set to %dms"), ExecutionTimeoutMs);
}

void UPythonRuntime::SetMemoryLimit(int32 MemoryMB)
{
    MemoryLimitMB = FMath::Max(64, MemoryMB); // Minimum 64MB
    UE_LOG(LogTemp, Warning, TEXT("[PythonRuntime] Memory limit set to %dMB"), MemoryLimitMB);
}

void UPythonRuntime::SetupSandbox()
{
    // Define banned modules (prevent file/network/os access)
    BannedModules.Add(TEXT("os"));
    BannedModules.Add(TEXT("sys"));
    BannedModules.Add(TEXT("subprocess"));
    BannedModules.Add(TEXT("socket"));
    BannedModules.Add(TEXT("requests"));
    BannedModules.Add(TEXT("urllib"));
    BannedModules.Add(TEXT("pathlib"));
    BannedModules.Add("__import__");
    BannedModules.Add(TEXT("eval"));
    BannedModules.Add(TEXT("exec"));
    BannedModules.Add(TEXT("compile"));
    BannedModules.Add(TEXT("globals"));
    BannedModules.Add(TEXT("locals"));
    BannedModules.Add(TEXT("vars"));
    BannedModules.Add(TEXT("dir"));

    // Define banned functions
    BannedFunctions.Add(TEXT("open"));
    BannedFunctions.Add(TEXT("input"));
    BannedFunctions.Add(TEXT("__import__"));
    BannedFunctions.Add(TEXT("eval"));
    BannedFunctions.Add(TEXT("exec"));
    BannedFunctions.Add(TEXT("compile"));
    BannedFunctions.Add(TEXT("globals"));
    BannedFunctions.Add(TEXT("locals"));
    BannedFunctions.Add(TEXT("vars"));
    BannedFunctions.Add(TEXT("dir"));

    // Define allowed built-in functions
    AllowedBuiltins.Add(TEXT("print"));
    AllowedBuiltins.Add(TEXT("len"));
    AllowedBuiltins.Add(TEXT("range"));
    AllowedBuiltins.Add(TEXT("str"));
    AllowedBuiltins.Add(TEXT("int"));
    AllowedBuiltins.Add(TEXT("float"));
    AllowedBuiltins.Add(TEXT("bool"));
    AllowedBuiltins.Add(TEXT("list"));
    AllowedBuiltins.Add(TEXT("dict"));
    AllowedBuiltins.Add(TEXT("tuple"));
    AllowedBuiltins.Add(TEXT("set"));
    AllowedBuiltins.Add(TEXT("sum"));
    AllowedBuiltins.Add(TEXT("min"));
    AllowedBuiltins.Add(TEXT("max"));
    AllowedBuiltins.Add(TEXT("abs"));
    AllowedBuiltins.Add(TEXT("round"));
    AllowedBuiltins.Add(TEXT("type"));
    AllowedBuiltins.Add(TEXT("isinstance"));
    AllowedBuiltins.Add(TEXT("sorted"));
    AllowedBuiltins.Add(TEXT("reversed"));
    AllowedBuiltins.Add(TEXT("enumerate"));
    AllowedBuiltins.Add(TEXT("zip"));
    AllowedBuiltins.Add(TEXT("map"));
    AllowedBuiltins.Add(TEXT("filter"));
    AllowedBuiltins.Add(TEXT("all"));
    AllowedBuiltins.Add(TEXT("any"));

    UE_LOG(LogTemp, Warning, TEXT("[PythonRuntime] Sandbox setup complete - Banned %d modules, %d functions"), 
            BannedModules.Num(), BannedFunctions.Num());
}

void UPythonRuntime::ValidateSandbox(const FString& Code, FString& OutErrorMessage) const
{
    // Check for banned imports
    if (ContainsBannedImports(Code))
    {
        OutErrorMessage = TEXT("Code contains banned import statements");
        return;
    }

    // Check for dangerous functions
    if (ContainsDangerousFunctions(Code))
    {
        OutErrorMessage = TEXT("Code contains dangerous function calls");
        return;
    }

    OutErrorMessage = TEXT("");
}

bool UPythonRuntime::ContainsBannedImports(const FString& Code) const
{
    for (const FString& BannedModule : BannedModules)
    {
        if (Code.Contains(*BannedModule))
        {
            return true;
        }
    }
    return false;
}

bool UPythonRuntime::ContainsDangerousFunctions(const FString& Code) const
{
    for (const FString& BannedFunc : BannedFunctions)
    {
        if (Code.Contains(*BannedFunc))
        {
            return true;
        }
    }
    return false;
}

FPythonExecutionOutput UPythonRuntime::ExecuteInternal(const FString& Code)
{
    FPythonExecutionOutput Output;
    Output.ExecutionResult = EPythonExecutionResult::Success;
    Output.Output = TEXT("");
    Output.ErrorMessage = TEXT("");
    Output.bTestCasesPass = false;
    Output.PassedTestCases = 0;
    Output.TotalTestCases = 0;

    // TODO: Integrate with actual Python interpreter
    // This is a placeholder for the actual Python execution
    UE_LOG(LogTemp, Warning, TEXT("[PythonRuntime] Code execution: (placeholder)"));

    return Output;
}

void UPythonRuntime::CaptureOutput(FString& OutOutput)
{
    // TODO: Capture stdout from Python execution
    OutOutput = TEXT("");
}

void UPythonRuntime::HandleExecutionError(const FString& ErrorMessage, FPythonExecutionOutput& OutOutput)
{
    OutOutput.ErrorMessage = ErrorMessage;
    OutOutput.ExecutionResult = EPythonExecutionResult::RuntimeError;
}