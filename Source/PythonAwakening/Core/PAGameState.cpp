// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#include "PAGameState.h"

APAGameState::APAGameState()
    : CurrentRegion(0),
      CompletedQuests(0),
      WorldCorruptionLevel(1.0f),
      TimeOfDay(6.0f),
      bIsNight(false),
      CurrentWeather(0)
{
    bReplicates = true;
}

void APAGameState::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("[PAGameState] Game state initialized"));
}

void APAGameState::AddDiscoveredLocation(int32 LocationID)
{
    if (!DiscoveredLocations.Contains(LocationID))
    {
        DiscoveredLocations.Add(LocationID);
        UE_LOG(LogTemp, Warning, TEXT("[PAGameState] Location discovered: %d"), LocationID);
    }
}

void APAGameState::AddUnlockedMemory(int32 MemoryID)
{
    if (!UnlockedMemories.Contains(MemoryID))
    {
        UnlockedMemories.Add(MemoryID);
        UE_LOG(LogTemp, Warning, TEXT("[PAGameState] Memory unlocked: %d"), MemoryID);
    }
}

bool APAGameState::IsLocationDiscovered(int32 LocationID) const
{
    return DiscoveredLocations.Contains(LocationID);
}

bool APAGameState::IsMemoryUnlocked(int32 MemoryID) const
{
    return UnlockedMemories.Contains(MemoryID);
}