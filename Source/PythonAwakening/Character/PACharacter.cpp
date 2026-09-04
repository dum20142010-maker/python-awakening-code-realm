// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#include "PACharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "PythonAwakening/Inventory/InventorySystem.h"
#include "PythonAwakening/Progression/ProgressionSystem.h"
#include "Kismet/GameplayStatics.h"

APACharacter::APACharacter()
    : Health(100.0f),
      MaxHealth(100.0f),
      Stamina(100.0f),
      MaxStamina(100.0f),
      CodingEnergy(100.0f),
      MaxCodingEnergy(100.0f),
      Level(1),
      Experience(0),
      ExperienceNeededForNextLevel(1000),
      FacePreset(0),
      HairStyle(0),
      HairColor(FLinearColor::White),
      SkinColor(FLinearColor(0.9f, 0.8f, 0.7f, 1.0f)),
      OutfitPreset(0),
      bIsInCombat(false),
      bIsBlocking(false),
      bIsSprinting(false),
      bIsCrouching(false)
{
    // Don't rotate character with camera
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    GetCharacterMovement()->MaxWalkSpeedCrouched = 300.0f;

    // Create camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // Create follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    PrimaryActorTick.TickInterval = 0.016f; // 60 FPS
}

void APACharacter::BeginPlay()
{
    Super::BeginPlay();

    SetupCharacterMesh();
    InitializeSystems();
    ApplyCustomizationToMesh();

    UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Character initialized: %s (Level %d)"), *CharacterName, Level);
}

void APACharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateStats(DeltaTime);
}

void APACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (!PlayerInputComponent) return;

    // Movement
    PlayerInputComponent->BindAxis("MoveForward", this, &APACharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APACharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &APACharacter::LookUp);
    PlayerInputComponent->BindAxis("LookRight", this, &APACharacter::LookRight);

    // Actions
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APACharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APACharacter::Sprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APACharacter::StopSprinting);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APACharacter::Crouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APACharacter::StopCrouching);
    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APACharacter::BasicAttack);
    PlayerInputComponent->BindAction("Block", IE_Pressed, this, &APACharacter::Block);

    UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Input component setup complete"));
}

void APACharacter::MoveForward(float Value)
{
    if (!Controller) return;

    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);
    const FVector Direction = FRotMatrix(YawRotation).GetUnitAxis(EAxis::X);

    AddMovementInput(Direction, Value);
}

void APACharacter::MoveRight(float Value)
{
    if (!Controller) return;

    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);
    const FVector Direction = FRotMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    AddMovementInput(Direction, Value);
}

void APACharacter::LookUp(float Value)
{
    if (Controller)
    {
        AddControllerPitchInput(Value);
    }
}

void APACharacter::LookRight(float Value)
{
    if (Controller)
    {
        AddControllerYawInput(Value);
    }
}

void APACharacter::Sprint()
{
    if (GetCharacterMovement() && !bIsCrouching)
    {
        bIsSprinting = true;
        GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
        UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Sprinting started"));
    }
}

void APACharacter::StopSprinting()
{
    if (GetCharacterMovement())
    {
        bIsSprinting = false;
        GetCharacterMovement()->MaxWalkSpeed = 600.0f;
        UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Sprinting stopped"));
    }
}

void APACharacter::Jump()
{
    if (CanJump())
    {
        ACharacter::Jump();
        UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Jumped"));
    }
}

void APACharacter::Crouch()
{
    if (GetCharacterMovement() && !bIsSprinting)
    {
        bIsCrouching = true;
        GetCharacterMovement()->MaxWalkSpeed = 300.0f;
        ACharacter::Crouch();
        UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Crouching"));
    }
}

void APACharacter::StopCrouching()
{
    if (GetCharacterMovement())
    {
        bIsCrouching = false;
        GetCharacterMovement()->MaxWalkSpeed = 600.0f;
        ACharacter::UnCrouch();
        UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Stopped crouching"));
    }
}

void APACharacter::Dodge()
{
    if (Stamina >= 20.0f)
    {
        Stamina -= 20.0f;
        // TODO: Add dodge animation and invulnerability frames
        UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Dodged (Stamina: %.0f)"), Stamina);
    }
}

void APACharacter::BasicAttack()
{
    if (bIsInCombat)
    {
        if (Stamina >= 10.0f)
        {
            Stamina -= 10.0f;
            // TODO: Add attack animation and damage calculation
            UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Basic attack (Stamina: %.0f)"), Stamina);
        }
    }
}

void APACharacter::HeavyAttack()
{
    if (bIsInCombat)
    {
        if (Stamina >= 30.0f)
        {
            Stamina -= 30.0f;
            // TODO: Add heavy attack animation and damage calculation
            UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Heavy attack (Stamina: %.0f)"), Stamina);
        }
    }
}

void APACharacter::Block()
{
    if (bIsInCombat)
    {
        bIsBlocking = !bIsBlocking;
        UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Blocking: %s"), bIsBlocking ? TEXT("true") : TEXT("false"));
    }
}

void APACharacter::TakeDamage(float DamageAmount, AActor* DamageInstigator)
{
    if (bIsBlocking)
    {
        DamageAmount *= 0.5f; // Reduce damage while blocking
    }

    Health -= DamageAmount;
    if (Health <= 0.0f)
    {
        Health = 0.0f;
        UE_LOG(LogTemp, Error, TEXT("[PACharacter] Character died!"));
        // TODO: Handle death
    }

    UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Took %.0f damage (Health: %.0f)"), DamageAmount, Health);
}

void APACharacter::Heal(float HealAmount)
{
    Health = FMath::Min(Health + HealAmount, MaxHealth);
    UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Healed %.0f (Health: %.0f)"), HealAmount, Health);
}

void APACharacter::GainExperience(int32 XPAmount)
{
    Experience += XPAmount;

    if (Experience >= ExperienceNeededForNextLevel)
    {
        LevelUp();
    }

    UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Gained %d XP (Total: %d/%d)"), XPAmount, Experience, ExperienceNeededForNextLevel);
}

void APACharacter::LevelUp()
{
    Level++;
    Experience = 0;
    ExperienceNeededForNextLevel = Level * 1000;
    MaxHealth += 20.0f;
    Health = MaxHealth;
    MaxStamina += 10.0f;
    Stamina = MaxStamina;
    MaxCodingEnergy += 10.0f;
    CodingEnergy = MaxCodingEnergy;

    UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Leveled up to %d!"), Level);
}

void APACharacter::RestoreCodingEnergy(float Amount)
{
    CodingEnergy = FMath::Min(CodingEnergy + Amount, MaxCodingEnergy);
}

void APACharacter::RestoreStamina(float Amount)
{
    Stamina = FMath::Min(Stamina + Amount, MaxStamina);
}

void APACharacter::SetCharacterCustomization(int32 Face, int32 Hair, FLinearColor HColor, FLinearColor SColor, int32 Outfit)
{
    FacePreset = Face;
    HairStyle = Hair;
    HairColor = HColor;
    SkinColor = SColor;
    OutfitPreset = Outfit;
}

void APACharacter::ApplyCustomizationToMesh()
{
    // TODO: Apply customization to skeletal mesh using material parameters
    UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Customization applied"));
}

void APACharacter::InitializeSystems()
{
    InventorySystem = NewObject<UInventorySystem>(this);
    if (InventorySystem)
    {
        InventorySystem->Initialize();
        UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Inventory system initialized"));
    }

    ProgressionSystem = NewObject<UProgressionSystem>(this);
    if (ProgressionSystem)
    {
        ProgressionSystem->Initialize();
        UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Progression system initialized"));
    }
}

void APACharacter::SetupCharacterMesh()
{
    // TODO: Setup skeletal mesh and materials
    UE_LOG(LogTemp, Warning, TEXT("[PACharacter] Character mesh setup complete"));
}

void APACharacter::UpdateStats(float DeltaTime)
{
    RegenerateStamina();
    RegenerateCodingEnergy();
}

void APACharacter::RegenerateStamina()
{
    if (!bIsSprinting && !bIsInCombat)
    {
        RestoreStamina(5.0f); // Regenerate 5 stamina per tick
    }
}

void APACharacter::RegenerateCodingEnergy()
{
    RestoreCodingEnergy(2.0f); // Regenerate 2 coding energy per tick
}