// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#include "WorldSystem.h"

UWorldSystem::UWorldSystem()
    : TimeOfDay(6.0f),
      bIsNight(false),
      DayNightCycleSpeed(48.0f), // 48 minutes = 1 full day/night cycle
      CurrentWeather(0),
      WeatherChangeTimer(0.0f),
      CorruptionLevel(1.0f),
      RestoredRegions(0)
{
}

void UWorldSystem::Initialize()
{
    TimeOfDay = 6.0f; // Start at 6 AM
    bIsNight = false;
    CurrentWeather = 0; // Start sunny
    CorruptionLevel = 1.0f;
    RestoredRegions = 0;
    RestoredRegionIDs.Empty();
    UE_LOG(LogTemp, Warning, TEXT("[WorldSystem] Initialized"));
}

void UWorldSystem::Update(float DeltaTime)
{
    UpdateTimeOfDay(DeltaTime);
    UpdateWeather(DeltaTime);
    UpdateWorldState(DeltaTime);
}

void UWorldSystem::ChangeWeather(int32 WeatherType)
{
    CurrentWeather = WeatherType;
    UE_LOG(LogTemp, Warning, TEXT("[WorldSystem] Weather changed to: %d"), WeatherType);
}

void UWorldSystem::RestoreRegion(int32 RegionID)
{
    if (!RestoredRegionIDs.Contains(RegionID))
    {
        RestoredRegionIDs.Add(RegionID);
        RestoredRegions++;
        CorruptionLevel = FMath::Max(0.0f, CorruptionLevel - (1.0f / 8.0f)); // 8 regions total
        UE_LOG(LogTemp, Warning, TEXT("[WorldSystem] Region restored: %d (Total: %d, Corruption: %.2f%%)"), 
                RegionID, RestoredRegions, CorruptionLevel * 100.0f);
    }
}

void UWorldSystem::UpdateTimeOfDay(float DeltaTime)
{
    // Advance time
    TimeOfDay += (DeltaTime / DayNightCycleSpeed);
    if (TimeOfDay >= 24.0f)
    {
        TimeOfDay -= 24.0f;
    }

    // Determine if night
    bIsNight = (TimeOfDay >= 18.0f || TimeOfDay < 6.0f);
}

void UWorldSystem::UpdateWeather(float DeltaTime)
{
    WeatherChangeTimer += DeltaTime;

    // Change weather every 300 seconds (5 minutes)
    if (WeatherChangeTimer >= 300.0f)
    {
        WeatherChangeTimer = 0.0f;
        // Random weather change
        int32 NewWeather = FMath::RandRange(0, 3);
        if (NewWeather != CurrentWeather)
        {
            ChangeWeather(NewWeather);
        }
    }
}

void UWorldSystem::UpdateWorldState(float DeltaTime)
{
    // Update world events and state based on time and corruption
    // TODO: Implement world event system
}