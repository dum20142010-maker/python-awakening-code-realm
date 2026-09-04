// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#include "InventorySystem.h"

UInventorySystem::UInventorySystem()
    : MaxInventorySlots(20)
{
}

void UInventorySystem::Initialize()
{
    InventoryItems.Empty();
    UE_LOG(LogTemp, Warning, TEXT("[InventorySystem] Initialized with %d slots"), MaxInventorySlots);
}

bool UInventorySystem::AddItem(AItem* Item, int32 Quantity)
{
    if (!Item || Quantity <= 0)
    {
        return false;
    }

    if (!HasSpace())
    {
        UE_LOG(LogTemp, Warning, TEXT("[InventorySystem] No space for item"));
        return false;
    }

    if (InventoryItems.Contains(Item))
    {
        InventoryItems[Item] += Quantity;
    }
    else
    {
        InventoryItems.Add(Item, Quantity);
    }

    UE_LOG(LogTemp, Warning, TEXT("[InventorySystem] Added item (Quantity: %d)"), Quantity);
    return true;
}

bool UInventorySystem::RemoveItem(AItem* Item, int32 Quantity)
{
    if (!Item || Quantity <= 0)
    {
        return false;
    }

    if (!InventoryItems.Contains(Item))
    {
        return false;
    }

    int32 CurrentQuantity = InventoryItems[Item];
    if (CurrentQuantity < Quantity)
    {
        return false;
    }

    CurrentQuantity -= Quantity;
    if (CurrentQuantity <= 0)
    {
        InventoryItems.Remove(Item);
    }
    else
    {
        InventoryItems[Item] = CurrentQuantity;
    }

    UE_LOG(LogTemp, Warning, TEXT("[InventorySystem] Removed item (Quantity: %d)"), Quantity);
    return true;
}

int32 UInventorySystem::GetItemQuantity(AItem* Item) const
{
    if (!Item || !InventoryItems.Contains(Item))
    {
        return 0;
    }

    return InventoryItems[Item];
}

bool UInventorySystem::HasSpace(int32 SlotsNeeded) const
{
    return (InventoryItems.Num() + SlotsNeeded) <= MaxInventorySlots;
}

int32 UInventorySystem::GetInventorySize() const
{
    return InventoryItems.Num();
}