// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#include "Quest.h"

UQuest::UQuest()
{
}

void UQuest::Initialize(const FQuestData& QuestData)
{
    Data = QuestData;
    Data.Status = EQuestStatus::Active;
    UE_LOG(LogTemp, Warning, TEXT("[Quest] Initialized: %s"), *Data.QuestTitle);
}

void UQuest::UpdateObjective(const FString& ObjectiveID, int32 ValueChange)
{
    for (FQuestObjective& Objective : Data.Objectives)
    {
        if (Objective.ObjectiveID == ObjectiveID)
        {
            Objective.CurrentValue = FMath::Min(Objective.CurrentValue + ValueChange, Objective.TargetValue);
            if (Objective.CurrentValue >= Objective.TargetValue)
            {
                Objective.bCompleted = true;
            }
            UE_LOG(LogTemp, Warning, TEXT("[Quest] Objective updated: %s (%d/%d)"), *ObjectiveID, Objective.CurrentValue, Objective.TargetValue);
            return;
        }
    }
}

bool UQuest::AreObjectivesComplete() const
{
    for (const FQuestObjective& Objective : Data.Objectives)
    {
        if (!Objective.bCompleted)
        {
            return false;
        }
    }
    return true;
}

void UQuest::CompleteQuest()
{
    Data.Status = EQuestStatus::Completed;
    UE_LOG(LogTemp, Warning, TEXT("[Quest] Completed: %s (Reward: %d XP, %d Gold)"), *Data.QuestTitle, Data.RewardXP, Data.RewardCurrency);
}

void UQuest::FailQuest()
{
    Data.Status = EQuestStatus::Failed;
    UE_LOG(LogTemp, Warning, TEXT("[Quest] Failed: %s"), *Data.QuestTitle);
}

void UQuest::AbandonQuest()
{
    Data.Status = EQuestStatus::Abandoned;
    UE_LOG(LogTemp, Warning, TEXT("[Quest] Abandoned: %s"), *Data.QuestTitle);
}

void UQuest::SetTracked(bool bTracked)
{
    Data.bTracked = bTracked;
    UE_LOG(LogTemp, Warning, TEXT("[Quest] Tracking: %s - %s"), *Data.QuestTitle, bTracked ? TEXT("ON") : TEXT("OFF"));
}