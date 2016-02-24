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

#include "FRPGPlayerStats.generated.h"

USTRUCT(BlueprintType, META = (DisplayName = "RPG Player Stats") )
struct EMOSRPG_API FRPGPlayerStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	public:
		/** Indicates the amount of xp needed to progress to the next level */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (DisplayName = "XP To Level", ClampMin = 0.0f, UIMin = 0.0f) )
		float XPToLevel = 162.0f;

		/** The maximum allowable health */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (ClampMin = 0, UIMin = 0))
		int32 MaximumHealth = 124;

		/** The maximum allowable magic consumption available */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (ClampMin = 0, UIMin = 0))
		int32 MaximumMana = 78;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float AttackAgility = 1.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 AttackRating = 1;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 BlockRate = 2;

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
		int32 DefenseRating = 1;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 Dexterity = 0;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 EvadeRate = 1;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float HPRegenRate = 3.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 HPRegenRateAmount = 3;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 Intelligence = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MagicalDefense = 22;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumMagicalAttack = 24;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumPhysicalAttack = 8;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0))
		int32 Mentality = 0;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MinimumMagicalAttack = 16;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MinimumPhysicalAttack = 3;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float MovementAgility = 1.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float MPRegenRate = 3.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MPRegenRateAmount = 2;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 PhysicalDefense = 18;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 Strength = 6;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Stats", META = (ClampMin = 0, UIMin = 0))
		int32 Vitality = 0;
};
