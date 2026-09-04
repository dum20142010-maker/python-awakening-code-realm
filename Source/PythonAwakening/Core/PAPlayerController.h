// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PAPlayerController.generated.h"

class UInputComponent;
class APACharacter;

/**
 * Main player controller for Python Awakening
 * Handles input, HUD, and player interaction
 */
UCLASS()
class PYTHONAWAKENING_API APAPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    APAPlayerController();

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;
    virtual void Tick(float DeltaTime) override;

    // Reference to player character
    UPROPERTY(BlueprintReadOnly, Category = "Character")
    APACharacter* PlayerCharacter;

    // HUD visibility
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ToggleHUD();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowPauseMenu();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void HidePauseMenu();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void OpenCodingTerminal();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void CloseCodingTerminal();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void OpenInventory();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void OpenMap();

private:
    // UI state
    UPROPERTY()
    bool bHUDVisible;

    UPROPERTY()
    bool bPauseMenuVisible;

    UPROPERTY()
    bool bCodingTerminalOpen;

    UPROPERTY()
    bool bInventoryOpen;

    UPROPERTY()
    bool bMapOpen;

    // Input callbacks
    void OnPausePressed();
    void OnCodingTerminalPressed();
    void OnInventoryPressed();
    void OnMapPressed();
};