// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PAGameState.generated.h"

/**
 * Replicated game state information
 * Tracks global game progression and world state
 */
UCLASS()
class PYTHONAWAKENING_API APAGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    APAGameState();

    virtual void BeginPlay() override;

    // Game progression
    UPROPERTY(BlueprintReadWrite, Category = "Progression")
    int32 CurrentRegion;

    UPROPERTY(BlueprintReadWrite, Category = "Progression")
    int32 CompletedQuests;

    UPROPERTY(BlueprintReadWrite, Category = "Progression")
    float WorldCorruptionLevel; // 0.0 - 1.0 (0 = restored, 1 = fully corrupted)

    // Time of day
    UPROPERTY(BlueprintReadWrite, Category = "World")
    float TimeOfDay; // 0.0 - 24.0 (24-hour cycle)

    UPROPERTY(BlueprintReadWrite, Category = "World")
    bool bIsNight;

    // Weather
    UPROPERTY(BlueprintReadWrite, Category = "World")
    int32 CurrentWeather; // 0=Sunny, 1=Cloudy, 2=Rain, 3=Storm, etc.

    // Discovery tracking
    UPROPERTY(BlueprintReadWrite, Category = "Discovery")
    TArray<int32> DiscoveredLocations;

    UPROPERTY(BlueprintReadWrite, Category = "Discovery")
    TArray<int32> UnlockedMemories;

    // Add a discovered location
    UFUNCTION(BlueprintCallable, Category = "Discovery")
    void AddDiscoveredLocation(int32 LocationID);

    // Add an unlocked memory
    UFUNCTION(BlueprintCallable, Category = "Discovery")
    void AddUnlockedMemory(int32 MemoryID);

    // Check if location is discovered
    UFUNCTION(BlueprintCallable, Category = "Discovery")
    bool IsLocationDiscovered(int32 LocationID) const;

    // Check if memory is unlocked
    UFUNCTION(BlueprintCallable, Category = "Discovery")
    bool IsMemoryUnlocked(int32 MemoryID) const;
};