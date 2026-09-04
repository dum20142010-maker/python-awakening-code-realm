// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#include "PAPlayerController.h"
#include "PythonAwakening/Character/PACharacter.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

APAPlayerController::APAPlayerController()
    : bHUDVisible(true),
      bPauseMenuVisible(false),
      bCodingTerminalOpen(false),
      bInventoryOpen(false),
      bMapOpen(false)
{
}

void APAPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Get player character reference
    PlayerCharacter = Cast<APACharacter>(GetPawn());
    
    if (PlayerCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("[PAPlayerController] Player character found"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[PAPlayerController] Player character not found!"));
    }
}

void APAPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        UE_LOG(LogTemp, Warning, TEXT("[PAPlayerController] Setting up enhanced input"));
    }
}

void APAPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APAPlayerController::ToggleHUD()
{
    bHUDVisible = !bHUDVisible;
    UE_LOG(LogTemp, Warning, TEXT("[PAPlayerController] HUD visibility toggled: %s"), bHUDVisible ? TEXT("visible") : TEXT("hidden"));
}

void APAPlayerController::ShowPauseMenu()
{
    bPauseMenuVisible = true;
    UGameplayStatics::SetGamePaused(GetWorld(), true);
    UE_LOG(LogTemp, Warning, TEXT("[PAPlayerController] Pause menu opened"));
}

void APAPlayerController::HidePauseMenu()
{
    bPauseMenuVisible = false;
    UGameplayStatics::SetGamePaused(GetWorld(), false);
    UE_LOG(LogTemp, Warning, TEXT("[PAPlayerController] Pause menu closed"));
}

void APAPlayerController::OpenCodingTerminal()
{
    if (!bCodingTerminalOpen)
    {
        bCodingTerminalOpen = true;
        UGameplayStatics::SetGamePaused(GetWorld(), true);
        UE_LOG(LogTemp, Warning, TEXT("[PAPlayerController] Coding terminal opened"));
    }
}

void APAPlayerController::CloseCodingTerminal()
{
    if (bCodingTerminalOpen)
    {
        bCodingTerminalOpen = false;
        UGameplayStatics::SetGamePaused(GetWorld(), false);
        UE_LOG(LogTemp, Warning, TEXT("[PAPlayerController] Coding terminal closed"));
    }
}

void APAPlayerController::OpenInventory()
{
    bInventoryOpen = !bInventoryOpen;
    UE_LOG(LogTemp, Warning, TEXT("[PAPlayerController] Inventory toggled: %s"), bInventoryOpen ? TEXT("open") : TEXT("closed"));
}

void APAPlayerController::OpenMap()
{
    bMapOpen = !bMapOpen;
    UE_LOG(LogTemp, Warning, TEXT("[PAPlayerController] Map toggled: %s"), bMapOpen ? TEXT("open") : TEXT("closed"));
}

void APAPlayerController::OnPausePressed()
{
    if (bPauseMenuVisible)
    {
        HidePauseMenu();
    }
    else
    {
        ShowPauseMenu();
    }
}

void APAPlayerController::OnCodingTerminalPressed()
{
    if (bCodingTerminalOpen)
    {
        CloseCodingTerminal();
    }
    else
    {
        OpenCodingTerminal();
    }
}

void APAPlayerController::OnInventoryPressed()
{
    OpenInventory();
}

void APAPlayerController::OnMapPressed()
{
    OpenMap();
}