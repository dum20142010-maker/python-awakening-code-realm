// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#include "PAGameMode.h"
#include "PythonAwakening/Python/PythonRuntime.h"
#include "PythonAwakening/Quest/QuestSystem.h"
#include "PythonAwakening/Progression/ProgressionSystem.h"
#include "PythonAwakening/World/WorldSystem.h"
#include "Kismet/GameplayStatics.h"

APAGameMode::APAGameMode()
    : bGamePaused(false)
{
    // Use realistic tick rate for smooth gameplay
    PrimaryActorTick.TickInterval = 0.016f; // ~60 FPS
}

void APAGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    UE_LOG(LogTemp, Warning, TEXT("[PAGameMode] Game started - Initializing systems..."));
    
    InitializeSystems();
}

void APAGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (bGamePaused)
    {
        return; // Don't update systems while paused
    }

    // Update world state
    if (WorldSystem)
    {
        WorldSystem->Update(DeltaTime);
    }
}

bool APAGameMode::IsGamePaused() const
{
    return bGamePaused;
}

void APAGameMode::SetGamePaused(bool bPaused)
{
    bGamePaused = bPaused;
    
    if (bPaused)
    {
        UE_LOG(LogTemp, Warning, TEXT("[PAGameMode] Game paused"));
        UGameplayStatics::SetGamePaused(GetWorld(), true);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[PAGameMode] Game resumed"));
        UGameplayStatics::SetGamePaused(GetWorld(), false);
    }
}

void APAGameMode::InitializeGame(const FString& PlayerName)
{
    CurrentPlayerName = PlayerName;
    UE_LOG(LogTemp, Warning, TEXT("[PAGameMode] Initializing game for player: %s"), *PlayerName);
}

void APAGameMode::EndGame()
{
    UE_LOG(LogTemp, Warning, TEXT("[PAGameMode] Game ended"));
}

void APAGameMode::InitializeSystems()
{
    // Create Python Runtime
    PythonRuntime = NewObject<UPythonRuntime>(this);
    if (PythonRuntime)
    {
        PythonRuntime->Initialize();
        UE_LOG(LogTemp, Warning, TEXT("[PAGameMode] Python Runtime initialized"));
    }

    // Create Quest System
    QuestSystem = NewObject<UQuestSystem>(this);
    if (QuestSystem)
    {
        QuestSystem->Initialize();
        UE_LOG(LogTemp, Warning, TEXT("[PAGameMode] Quest System initialized"));
    }

    // Create Progression System
    ProgressionSystem = NewObject<UProgressionSystem>(this);
    if (ProgressionSystem)
    {
        ProgressionSystem->Initialize();
        UE_LOG(LogTemp, Warning, TEXT("[PAGameMode] Progression System initialized"));
    }

    // Create World System
    WorldSystem = NewObject<UWorldSystem>(this);
    if (WorldSystem)
    {
        WorldSystem->Initialize();
        UE_LOG(LogTemp, Warning, TEXT("[PAGameMode] World System initialized"));
    }
}