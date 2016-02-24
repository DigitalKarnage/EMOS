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
#include <Engine/DataTable.h>

#include <Framework/Enumerations/ERPGCharacterType.h>

#include "FRPGCombatStats.generated.h"

USTRUCT(Blueprintable, META = (DisplayName = "RPG Combat Stats"))
struct EMOSRPG_API FRPGCombatStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	public:
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
		int32 Dexterity = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 EvadeRate = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float HPRegenRate = 0.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 HPRegenRateAmount = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 Intelligence = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MagicalDefense = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumMagicalAttack = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumPhysicalAttack = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 Mentality = 0;

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

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 Vitality = 0;

		/** An additional bonus to the players current Character's Critical Chance stat during combat with other players */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PK Combat Stats", META = (DisplayName = "PK Critical Chance", ClampMin = 0.0f, UIMin = 0.0f))
		float PKCriticalChance = 0.0f;

		/** An additional bonus to the players current Character's Critical Reduction stat during combat with other players */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PK Combat Stats", META = (DisplayName = "PK Critical Reduction", ClampMin = 0.0f, UIMin = 0.0f))
		float PKCriticalReduction = 0.0f;

		/** An additional bonus to the players current Character's Critical Resistance stat during combat with other players */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PK Combat Stats", META = (DisplayName = "PK Critical Resistance", ClampMin = 0.0f, UIMin = 0.0f))
		float PKCriticalResistance = 0.0f;

		/** An additional bonus to the players current Character's Magical Defense stat during combat with other players */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PK Combat Stats", META = (DisplayName = "PK Magical Defense", ClampMin = 0, UIMin = 0))
		int32 PKMagicalDefense = 0;

		/** An additional bonus to the players current Character's Maximum Magical Attack stat during combat with other players */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PK Combat Stats", META = (DisplayName = "PK Maximum Magical Attack", ClampMin = 0, UIMin = 0))
		int32 PKMaximumMagicalAttack = 0;

		/** An additional bonus to the players current Character's Maximum Physical Attack stat during combat with other players */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PK Combat Stats", META = (DisplayName = "PK Maximum Physical Attack", ClampMin = 0, UIMin = 0))
		int32 PKMaximumPhysicalAttack = 0;

		/** An additional bonus to the players current Character's Minimum Magical Attack stat during combat with other players */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PK Combat Stats", META = (DisplayName = "PK Minimum Magical Attack", ClampMin = 0, UIMin = 0))
		int32 PKMinimumMagicalAttack = 0;

		/** An additional bonus to the players current Character's Minimum Physical Attack stat during combat with other players */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PK Combat Stats", META = (DisplayName = "PK Minimum Physical Attack", ClampMin = 0, UIMin = 0))
		int32 PKMinimumPhysicalAttack = 0;

		/** An additional bonus to the players current Character's Physical Defense stat during combat with other players */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PK Combat Stats", META = (DisplayName = "PK Physical Defense", ClampMin = 0, UIMin = 0))
		int32 PKPhysicalDefense = 0;
};