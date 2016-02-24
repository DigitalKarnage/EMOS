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
#include <Engine/DataAsset.h>

#include <Framework/Enumerations/ERPGCharacterType.h>
#include <Framework/Structures/FRPGCharacterStats.h>
#include <Framework/Structures/FRPGCombatStats.h>

#include "URPGCharacterData.generated.h"

UCLASS(Blueprintable, META = (DisplayName = "RPG Character Stats Data") )
class EMOSRPG_API URPGCharacterData : public UDataAsset
{
	GENERATED_BODY()

	public:
		/** The type of character */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Stats")
		ERPGCharacterType CharacterType = ERPGCharacterType::None;

		/** The amount of progression within the game */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Stats", META = (ClampMin = 0, UIMin = 0) )
		uint8 CurrentLevel = 1;

		/** The amount of health */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 CurrentHealth = 0;

		/** The maximum allowable health */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumHealth = 0;

		/** The amount of magical consumption available */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 CurrentMana = 0;

		/** The maximum allowable magic consumption available */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumMana = 0;
		
		/** A value indicating whether we can be inspected */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Stats")
		bool bCanBeInspected = false;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float AttackAgility = 1.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 AttackRating = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 BlockRate = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float CastingAgility = 1.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f))
		float CriticalChance = 0.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float CriticalMultiplier = 1.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float CriticalReduction = 0.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float CriticalResistance = 0.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 DefenseRating = 0;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 EvadeRate = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float HPRegenRate = 0.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 HPRegenRateAmount = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MagicalDefense = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumMagicalAttack = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumPhysicalAttack = 0;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MinimumMagicalAttack = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MinimumPhysicalAttack = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float MovementAgility = 1.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float MPRegenRate = 0.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MPRegenRateAmount = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 PhysicalDefense = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 Strength = 0;
};
