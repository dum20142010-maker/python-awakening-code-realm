// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Quest.h"
#include "QuestSystem.generated.h"

class UQuest;

/**
 * Quest management system
 * Handles quest creation, tracking, and completion
 */
UCLASS()
class PYTHONAWAKENING_API UQuestSystem : public UObject
{
    GENERATED_BODY()

public:
    UQuestSystem();

    // Initialize quest system
    UFUNCTION(BlueprintCallable, Category = "Quest System")
    void Initialize();

    // Create and add quest
    UFUNCTION(BlueprintCallable, Category = "Quest System")
    UQuest* CreateQuest(const FQuestData& QuestData);

    // Get active quests
    UFUNCTION(BlueprintCallable, Category = "Quest System")
    TArray<UQuest*> GetActiveQuests() const;

    // Get quest by ID
    UFUNCTION(BlueprintCallable, Category = "Quest System")
    UQuest* GetQuestByID(const FString& QuestID) const;

    // Get completed quests count
    UFUNCTION(BlueprintCallable, Category = "Quest System")
    int32 GetCompletedQuestCount() const;

    // Get all quests
    UFUNCTION(BlueprintCallable, Category = "Quest System")
    TArray<UQuest*> GetAllQuests() const { return AllQuests; }

    // Update quest objective
    UFUNCTION(BlueprintCallable, Category = "Quest System")
    void UpdateQuestObjective(const FString& QuestID, const FString& ObjectiveID, int32 ValueChange);

    // Complete quest
    UFUNCTION(BlueprintCallable, Category = "Quest System")
    void CompleteQuest(const FString& QuestID);

    // Track specific quest
    UFUNCTION(BlueprintCallable, Category = "Quest System")
    void SetQuestTracked(const FString& QuestID, bool bTracked);

private:
    UPROPERTY()
    TArray<UQuest*> AllQuests;

    UPROPERTY()
    int32 CompletedQuestCount;
};