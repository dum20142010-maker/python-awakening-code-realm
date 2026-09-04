// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PAGameMode.generated.h"

class UPythonRuntime;
class UQuestSystem;
class UProgressionSystem;
class UWorldSystem;

/**
 * Main game mode for Python Awakening: The Code Realm
 * Manages core game loop, world state, and system initialization
 */
UCLASS()
class PYTHONAWAKENING_API APAGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    APAGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Game state queries
    UFUNCTION(BlueprintCallable, Category = "Game State")
    bool IsGamePaused() const;

    UFUNCTION(BlueprintCallable, Category = "Game State")
    void SetGamePaused(bool bPaused);

    // System getters
    UFUNCTION(BlueprintCallable, Category = "Systems")
    UPythonRuntime* GetPythonRuntime() const { return PythonRuntime; }

    UFUNCTION(BlueprintCallable, Category = "Systems")
    UQuestSystem* GetQuestSystem() const { return QuestSystem; }

    UFUNCTION(BlueprintCallable, Category = "Systems")
    UProgressionSystem* GetProgressionSystem() const { return ProgressionSystem; }

    UFUNCTION(BlueprintCallable, Category = "Systems")
    UWorldSystem* GetWorldSystem() const { return WorldSystem; }

    // Game initialization
    UFUNCTION(BlueprintCallable, Category = "Game")
    void InitializeGame(const FString& PlayerName);

    UFUNCTION(BlueprintCallable, Category = "Game")
    void EndGame();

private:
    // Core systems
    UPROPERTY()
    UPythonRuntime* PythonRuntime;

    UPROPERTY()
    UQuestSystem* QuestSystem;

    UPROPERTY()
    UProgressionSystem* ProgressionSystem;

    UPROPERTY()
    UWorldSystem* WorldSystem;

    // Game state
    UPROPERTY()
    bool bGamePaused;

    UPROPERTY()
    FString CurrentPlayerName;

    // Initialize all systems
    void InitializeSystems();
};