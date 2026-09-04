// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldSystem.generated.h"

/**
 * World state management system
 * Handles day/night cycle, weather, world events
 */
UCLASS()
class PYTHONAWAKENING_API UWorldSystem : public UObject
{
    GENERATED_BODY()

public:
    UWorldSystem();

    // Initialize world system
    UFUNCTION(BlueprintCallable, Category = "World")
    void Initialize();

    // Update world state
    UFUNCTION(BlueprintCallable, Category = "World")
    void Update(float DeltaTime);

    // Get current time of day (0.0 - 24.0)
    UFUNCTION(BlueprintCallable, Category = "World")
    float GetTimeOfDay() const { return TimeOfDay; }

    // Check if is night
    UFUNCTION(BlueprintCallable, Category = "World")
    bool IsNight() const { return bIsNight; }

    // Get current weather
    UFUNCTION(BlueprintCallable, Category = "World")
    int32 GetCurrentWeather() const { return CurrentWeather; }

    // Change weather
    UFUNCTION(BlueprintCallable, Category = "World")
    void ChangeWeather(int32 WeatherType);

    // Get world corruption level (0.0 - 1.0)
    UFUNCTION(BlueprintCallable, Category = "World")
    float GetWorldCorruptionLevel() const { return CorruptionLevel; }

    // Restore world region
    UFUNCTION(BlueprintCallable, Category = "World")
    void RestoreRegion(int32 RegionID);

    // Get restored regions count
    UFUNCTION(BlueprintCallable, Category = "World")
    int32 GetRestoredRegionsCount() const { return RestoredRegions; }

private:
    // Time system
    UPROPERTY()
    float TimeOfDay;

    UPROPERTY()
    bool bIsNight;

    UPROPERTY()
    float DayNightCycleSpeed; // Minutes per second

    // Weather system
    UPROPERTY()
    int32 CurrentWeather;

    UPROPERTY()
    float WeatherChangeTimer;

    // World state
    UPROPERTY()
    float CorruptionLevel; // 0.0 = restored, 1.0 = fully corrupted

    UPROPERTY()
    int32 RestoredRegions;

    UPROPERTY()
    TArray<int32> RestoredRegionIDs;

    // Update time
    void UpdateTimeOfDay(float DeltaTime);

    // Update weather
    void UpdateWeather(float DeltaTime);

    // Update world state
    void UpdateWorldState(float DeltaTime);
};