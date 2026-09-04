// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Quest.generated.h"

class UQuestSystem;

/**
 * Quest type enumeration
 */
UEUM_ENUM()
enum class EQuestType : uint8
{
    MainQuest = 0,
    SideQuest = 1,
    GuildQuest = 2,
    TavernQuest = 3,
    PythonChallenge = 4
};

/**
 * Quest status enumeration
 */
UEUM_ENUM()
enum class EQuestStatus : uint8
{
    NotStarted = 0,
    Active = 1,
    Completed = 2,
    Failed = 3,
    Abandoned = 4
};

/**
 * Individual quest data structure
 */
USTRUCT(BlueprintType)
struct FQuestObjective
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    FString ObjectiveID;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    FString Description;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    int32 TargetValue;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    int32 CurrentValue;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    bool bCompleted;
};

/**
 * Quest data structure
 */
USTRUCT(BlueprintType)
struct FQuestData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    FString QuestID;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    FString QuestTitle;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    FString QuestDescription;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    EQuestType QuestType;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    EQuestStatus Status;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    FString GiverNPCID;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    int32 RewardXP;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    int32 RewardCurrency;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    TArray<FQuestObjective> Objectives;

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    float TimeLimit; // In minutes, 0 = no limit

    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    bool bTracked;
};

/**
 * Quest class
 */
UCLASS()
class PYTHONAWAKENING_API UQuest : public UObject
{
    GENERATED_BODY()

public:
    UQuest();

    // Initialize quest
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void Initialize(const FQuestData& QuestData);

    // Get quest data
    UFUNCTION(BlueprintCallable, Category = "Quest")
    FQuestData GetQuestData() const { return Data; }

    // Update objective progress
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void UpdateObjective(const FString& ObjectiveID, int32 ValueChange);

    // Check if all objectives completed
    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool AreObjectivesComplete() const;

    // Mark quest as complete
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void CompleteQuest();

    // Mark quest as failed
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void FailQuest();

    // Abandon quest
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void AbandonQuest();

    // Toggle quest tracking
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void SetTracked(bool bTracked);

private:
    UPROPERTY()
    FQuestData Data;
};