// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#include "QuestSystem.h"
#include "Quest.h"

UQuestSystem::UQuestSystem()
    : CompletedQuestCount(0)
{
}

void UQuestSystem::Initialize()
{
    AllQuests.Empty();
    CompletedQuestCount = 0;
    UE_LOG(LogTemp, Warning, TEXT("[QuestSystem] Initialized"));
}

UQuest* UQuestSystem::CreateQuest(const FQuestData& QuestData)
{
    UQuest* NewQuest = NewObject<UQuest>(this);
    if (NewQuest)
    {
        NewQuest->Initialize(QuestData);
        AllQuests.Add(NewQuest);
        UE_LOG(LogTemp, Warning, TEXT("[QuestSystem] Quest created: %s"), *QuestData.QuestTitle);
    }
    return NewQuest;
}

TArray<UQuest*> UQuestSystem::GetActiveQuests() const
{
    TArray<UQuest*> ActiveQuests;
    for (UQuest* Quest : AllQuests)
    {
        if (Quest && Quest->GetQuestData().Status == EQuestStatus::Active)
        {
            ActiveQuests.Add(Quest);
        }
    }
    return ActiveQuests;
}

UQuest* UQuestSystem::GetQuestByID(const FString& QuestID) const
{
    for (UQuest* Quest : AllQuests)
    {
        if (Quest && Quest->GetQuestData().QuestID == QuestID)
        {
            return Quest;
        }
    }
    return nullptr;
}

int32 UQuestSystem::GetCompletedQuestCount() const
{
    int32 Count = 0;
    for (UQuest* Quest : AllQuests)
    {
        if (Quest && Quest->GetQuestData().Status == EQuestStatus::Completed)
        {
            Count++;
        }
    }
    return Count;
}

void UQuestSystem::UpdateQuestObjective(const FString& QuestID, const FString& ObjectiveID, int32 ValueChange)
{
    UQuest* Quest = GetQuestByID(QuestID);
    if (Quest)
    {
        Quest->UpdateObjective(ObjectiveID, ValueChange);
        if (Quest->AreObjectivesComplete())
        {
            CompleteQuest(QuestID);
        }
    }
}

void UQuestSystem::CompleteQuest(const FString& QuestID)
{
    UQuest* Quest = GetQuestByID(QuestID);
    if (Quest)
    {
        Quest->CompleteQuest();
        CompletedQuestCount++;
    }
}

void UQuestSystem::SetQuestTracked(const FString& QuestID, bool bTracked)
{
    UQuest* Quest = GetQuestByID(QuestID);
    if (Quest)
    {
        Quest->SetTracked(bTracked);
    }
}