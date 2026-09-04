// Copyright 2026 Python Awakening Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventorySystem.generated.h"

class AItem;

/**
 * Inventory system for managing player items, equipment, and resources
 */
UCLASS()
class PYTHONAWAKENING_API UInventorySystem : public UObject
{
    GENERATED_BODY()

public:
    UInventorySystem();

    // Initialize the inventory
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void Initialize();

    // Add item to inventory
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(AItem* Item, int32 Quantity = 1);

    // Remove item from inventory
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool RemoveItem(AItem* Item, int32 Quantity = 1);

    // Get item quantity
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetItemQuantity(AItem* Item) const;

    // Check if inventory has space
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool HasSpace(int32 SlotsNeeded = 1) const;

    // Get inventory size
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetInventorySize() const;

    // Get max inventory size
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetMaxInventorySize() const { return MaxInventorySlots; }

private:
    UPROPERTY()
    TMap<AItem*, int32> InventoryItems;

    UPROPERTY()
    int32 MaxInventorySlots;
};