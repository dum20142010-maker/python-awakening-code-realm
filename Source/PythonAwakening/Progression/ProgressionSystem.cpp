// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#include "ProgressionSystem.h"

UProgressionSystem::UProgressionSystem()
{
}

void UProgressionSystem::Initialize()
{
    InitializeSkills();
    UnlockedAchievements.Empty();
    UE_LOG(LogTemp, Warning, TEXT("[ProgressionSystem] Initialized with %d skill categories"), Skills.Num());
}

void UProgressionSystem::InitializeSkills()
{
    Skills.Empty();

    for (int32 i = 0; i < 8; ++i)
    {
        FPythonSkill Skill;
        Skill.Category = (EPythonSkillCategory)i;
        Skill.Level = 0;
        Skill.Experience = 0;
        Skill.bUnlocked = (i == 0); // Start with Foundations unlocked
        Skills.Add(Skill);
    }
}

void UProgressionSystem::AddSkillXP(EPythonSkillCategory Category, int32 XPAmount)
{
    for (FPythonSkill& Skill : Skills)
    {
        if (Skill.Category == Category)
        {
            Skill.Experience += XPAmount;
            // Level up every 1000 XP
            while (Skill.Experience >= 1000)
            {
                Skill.Level++;
                Skill.Experience -= 1000;
                UE_LOG(LogTemp, Warning, TEXT("[ProgressionSystem] Skill leveled up! Category: %d, Level: %d"), (int32)Category, Skill.Level);
            }
            return;
        }
    }
}

int32 UProgressionSystem::GetSkillLevel(EPythonSkillCategory Category) const
{
    for (const FPythonSkill& Skill : Skills)
    {
        if (Skill.Category == Category)
        {
            return Skill.Level;
        }
    }
    return 0;
}

void UProgressionSystem::UnlockAchievement(const FString& AchievementID)
{
    if (!UnlockedAchievements.Contains(AchievementID))
    {
        UnlockedAchievements.Add(AchievementID);
        UE_LOG(LogTemp, Warning, TEXT("[ProgressionSystem] Achievement unlocked: %s"), *AchievementID);
    }
}

bool UProgressionSystem::IsAchievementUnlocked(const FString& AchievementID) const
{
    return UnlockedAchievements.Contains(AchievementID);
}

float UProgressionSystem::GetProgressionPercentage() const
{
    // Calculate based on skill levels and achievements
    int32 TotalSkillLevel = 0;
    for (const FPythonSkill& Skill : Skills)
    {
        TotalSkillLevel += Skill.Level;
    }

    int32 MaxSkillLevel = 8 * 50; // Assume max 50 levels per skill
    float SkillProgression = (float)TotalSkillLevel / MaxSkillLevel;

    float AchievementProgression = (float)UnlockedAchievements.Num() / 50.0f; // Assume 50 achievements total

    return ((SkillProgression + AchievementProgression) / 2.0f) * 100.0f;
}