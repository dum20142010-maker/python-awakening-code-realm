// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PACharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UInventorySystem;
class UProgressionSystem;

/**
 * Main player character for Python Awakening: The Code Realm
 * Handles movement, combat, Python-based abilities, and character state
 */
UCLASS()
class PYTHONAWAKENING_API APACharacter : public ACharacter
{
    GENERATED_BODY()

public:
    APACharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Character stats
    UPROPERTY(BlueprintReadWrite, Category = "Character|Stats")
    float Health;

    UPROPERTY(BlueprintReadWrite, Category = "Character|Stats")
    float MaxHealth;

    UPROPERTY(BlueprintReadWrite, Category = "Character|Stats")
    float Stamina;

    UPROPERTY(BlueprintReadWrite, Category = "Character|Stats")
    float MaxStamina;

    UPROPERTY(BlueprintReadWrite, Category = "Character|Stats")
    float CodingEnergy; // Used for Python-based abilities

    UPROPERTY(BlueprintReadWrite, Category = "Character|Stats")
    float MaxCodingEnergy;

    UPROPERTY(BlueprintReadWrite, Category = "Character|Stats")
    int32 Level;

    UPROPERTY(BlueprintReadWrite, Category = "Character|Stats")
    int32 Experience;

    UPROPERTY(BlueprintReadWrite, Category = "Character|Stats")
    int32 ExperienceNeededForNextLevel;

    // Character customization
    UPROPERTY(BlueprintReadWrite, Category = "Character|Customization")
    FString CharacterName;

    UPROPERTY(BlueprintReadWrite, Category = "Character|Customization")
    int32 FacePreset; // 0-10

    UPROPERTY(BlueprintReadWrite, Category = "Character|Customization")
    int32 HairStyle; // 0-15

    UPROPERTY(BlueprintReadWrite, Category = "Character|Customization")
    FLinearColor HairColor;

    UPROPERTY(BlueprintReadWrite, Category = "Character|Customization")
    FLinearColor SkinColor;

    UPROPERTY(BlueprintReadWrite, Category = "Character|Customization")
    int32 OutfitPreset; // 0-20

    // Systems
    UPROPERTY(BlueprintReadOnly, Category = "Systems")
    UInventorySystem* InventorySystem;

    UPROPERTY(BlueprintReadOnly, Category = "Systems")
    UProgressionSystem* ProgressionSystem;

    // Camera
    UPROPERTY(BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* CameraBoom;

    UPROPERTY(BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FollowCamera;

    // Movement
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void MoveForward(float Value);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void MoveRight(float Value);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void LookUp(float Value);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void LookRight(float Value);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Sprint();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void StopSprinting();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Jump() override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Crouch();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void StopCrouching();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Dodge();

    // Combat
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void BasicAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void HeavyAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Block();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void TakeDamage(float DamageAmount, AActor* DamageInstigator);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Heal(float HealAmount);

    // Stat management
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void GainExperience(int32 XPAmount);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void LevelUp();

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void RestoreCodingEnergy(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void RestoreStamina(float Amount);

    // Customization
    UFUNCTION(BlueprintCallable, Category = "Customization")
    void SetCharacterCustomization(int32 Face, int32 Hair, FLinearColor HColor, FLinearColor SColor, int32 Outfit);

    UFUNCTION(BlueprintCallable, Category = "Customization")
    void ApplyCustomizationToMesh();

    // Combat state
    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bIsInCombat;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bIsBlocking;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bIsSprinting;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    AActor* CurrentCombatTarget;

private:
    // Movement input
    FVector MovementInput;
    FVector LookInput;
    bool bIsCrouching;

    // Initialization
    void InitializeSystems();
    void SetupCharacterMesh();

    // Stat update
    void UpdateStats(float DeltaTime);
    void RegenerateStamina();
    void RegenerateCodingEnergy();
};