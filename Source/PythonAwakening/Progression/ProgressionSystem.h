// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProgressionSystem.generated.h"

/**
 * Python skill categories
 */
UEUM_ENUM()
enum class EPythonSkillCategory : uint8
{
    Foundations = 0,    // Variables, data types
    Logic = 1,          // Conditions
    Iteration = 2,      // Loops
    Functions = 3,      // Functions, parameters
    Data = 4,           // Lists, dicts, sets
    Reliability = 5,    // Exceptions
    Architecture = 6,   // Classes, objects
    Advanced = 7        // Algorithms
};

/**
 * Skill level data
 */
USTRUCT(BlueprintType)
struct FPythonSkill
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Progression")
    EPythonSkillCategory Category;

    UPROPERTY(BlueprintReadWrite, Category = "Progression")
    int32 Level;

    UPROPERTY(BlueprintReadWrite, Category = "Progression")
    int32 Experience;

    UPROPERTY(BlueprintReadWrite, Category = "Progression")
    bool bUnlocked;
};

/**
 * Player progression and achievement system
 */
UCLASS()
class PYTHONAWAKENING_API UProgressionSystem : public UObject
{
    GENERATED_BODY()

public:
    UProgressionSystem();

    // Initialize progression system
    UFUNCTION(BlueprintCallable, Category = "Progression")
    void Initialize();

    // Add XP to skill
    UFUNCTION(BlueprintCallable, Category = "Progression")
    void AddSkillXP(EPythonSkillCategory Category, int32 XPAmount);

    // Get skill level
    UFUNCTION(BlueprintCallable, Category = "Progression")
    int32 GetSkillLevel(EPythonSkillCategory Category) const;

    // Get all skills
    UFUNCTION(BlueprintCallable, Category = "Progression")
    TArray<FPythonSkill> GetAllSkills() const { return Skills; }

    // Unlock achievement/title
    UFUNCTION(BlueprintCallable, Category = "Progression")
    void UnlockAchievement(const FString& AchievementID);

    // Get unlocked achievements
    UFUNCTION(BlueprintCallable, Category = "Progression")
    TArray<FString> GetUnlockedAchievements() const { return UnlockedAchievements; }

    // Check if achievement unlocked
    UFUNCTION(BlueprintCallable, Category = "Progression")
    bool IsAchievementUnlocked(const FString& AchievementID) const;

    // Get total progression percentage
    UFUNCTION(BlueprintCallable, Category = "Progression")
    float GetProgressionPercentage() const;

private:
    UPROPERTY()
    TArray<FPythonSkill> Skills;

    UPROPERTY()
    TArray<FString> UnlockedAchievements;

    void InitializeSkills();
};