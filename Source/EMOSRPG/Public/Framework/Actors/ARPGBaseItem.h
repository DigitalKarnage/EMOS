/* 
	All rights reserved. Copyright (c) 2015-2016, DigitalKarnage	

	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in 
	the documentation and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
	THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
	BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
	GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <Core.h>
#include <Engine.h>
#include <Enumerations/ERPGItemRarity.h>
#include <Structures/FRPGItemIcon.h>

#include "ARPGBaseItem.generated.h"

UCLASS(Blueprintable, NotPlaceable, HideCategories=("Actor Tick", "Rendering", "Replication", "Input", "Actor"), META = (DisplayName = "RPG Base Item") )
class EMOSRPG_API ARPGBaseItem : public AActor
{
	GENERATED_BODY()

	public:
		/** A string value representing a user friendly name */
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Properties")
		FString Name;

		/** A value describing this object in detail for the player */
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Properties")
		FString Description;

		/** A value indicating the rarity of this item within the world */
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Properties")
		ERPGItemRarity ItemRarity;

		/** A value indicting the timespan this object is available to be consumable / equipable */
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Properties")
		FTimespan Lifetime;

		/** A value indicating the expiration date of this object */
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Properties")
		FDateTime ExpirationDate;

		/** A value indicting the minimum level the player must obtain before this item is consumable / equipable */
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Properties")
		uint8 LevelRequirement;

		/** A value indicating the current enchantment level of this object */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		uint8 EnchantmentLevel;

		/** A value indicating the maximum allowable enchantment on this item, if this item is enchantable */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		uint8 MaxEnchantmentLevel;

		/** A value indicating the sell amount of this item when sold to an NPC */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 SellWorth;

		/** A value indicating the cost of this item within the cash shop */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 CashPrice;

		/** A value indicating the current amount of these items in a stored inventory slot */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 StackSize;

		/** A value indicating the maximum amount of these items which can be stored in a single inventory slot */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 MaxStackSize = 1;

		/** A value indicating the rank of the item when considered for being lost when a player is killed */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 ReputationLoseRank;

		/** A value indicating the minimum moral value of the player at which this item can be lost when killed */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 MinimumLoseReputation = 0;

		/** A value indicating the maximum moral value of the player at which this item can be lost when killed */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 MaximumLoseReputation = -51200;

		/** A value indicating whether this object can be lost when killed by an NPC (Monster / Boss / Gaurd) */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bCanLoseToNPC = true;

		/** A value indicating whether this object can be droped out of the players inventory if the player has low moral */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsLosable = true;

		/** A value indicating whether this objects lifetime has expired */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsExpired;

		/** A value indicating whether this object can be consumed by the player */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsConsumable;

		/** A value indicating whether this object can be droped out of the players inventory */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsDropable;

		/** A value indicating whether this object can be traded between players */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsTradeable;

		/** A value indicating whether this object can be sold through the in-game consignment system */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsConsignable;

		/** A value indicating whether this object can be stored in a players personal storage */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsStorable;

		/** A value indicating whether this object can be stored in a guild vault */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsBankable;

		/** A value indicating whether this object can be sent through the in-game mail system to other players */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsMailable;
		
		/** A value indicating whether this object can be enchanted by the player */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsEnchantable;
		
		/** A value indicating whether this object is equipable by the player */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsEquipable;

		/** A value indicating whether this object is only droped during quests */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsQuestItem;

		/** A value indicating whether this object is an item which can be purchased in the cash shop */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsCashItem;

		/** A value indicating whether this object is an item which allows items to be stored within */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		bool bIsInventory;
		
		/** A value indicating the mesh for this object if this object is dropped in the world */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Visuals")
		UStaticMesh* DropVisual;

		/** A value indicating the texture to use for the Icon within the inventory */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Visuals", META = (ShowInnerPropertiesOnly = "true") )
		FRPGItemIcon Icon;

	public:
		ARPGBaseItem(const FObjectInitializer& objectInitializer = FObjectInitializer::Get());

	private:
		HIDE_ACTOR_TRANSFORM_FUNCTIONS();
};
