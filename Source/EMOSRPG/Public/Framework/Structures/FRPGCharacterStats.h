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

#include "FRPGCharacterStats.generated.h"

USTRUCT(Blueprintable, META = (DisplayName = "RPG Character Stats") )
struct EMOSRPG_API FRPGCharacterStats
{
	GENERATED_USTRUCT_BODY()

	public:
		/** The name given to the character which owns these stats */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
		FString Name = FString("Default Character");

		/** The type of character */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
		ERPGCharacterType CharacterType = ERPGCharacterType::None;

		/** The amount of progression */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (ClampMin = 0.0f, UIMin = 0.0f) )
		float CurrentExperience = 0.0f;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (ClampMin = 0.0f, UIMin = 0.0f))
		float MaximumExperience = 0.0f;

		/** The amount of progression within the game */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (ClampMin = 0, UIMin = 0) )
		uint8 CurrentLevel = 1;

		/** The amount of health */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 CurrentHealth = 0;

		/** The maximum allowable health */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumHealth = 0;

		/** The amount of magical consumption available */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 CurrentMana = 0;

		/** The maximum allowable magic consumption available */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (ClampMin = 0, UIMin = 0) )
		int32 MaximumMana = 0;

		/** The value given to the player for good and bad choices */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
		int32 Reputation = 0;
				
		/** The value given to the player for doing reputable actions */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (ClampMin = 0.0f, UIMin = 0.0f))
		float DivinePower;
		
		/** Do we want players to be able to inspect this characters equipment stats */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (DisplayName = "Allows Inspection?") )
		bool bAllowsInspection = false;

		/** Are we targeting ourselves */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (DisplayName = "Is Targeting Self?") )
		bool bIsTargetingSelf = false;
				
		/** Are we in PK Mode */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (DisplayName = "Is In PK Mode?") )
		bool bIsInPKMode = false;

		/** Are we flagged for pk, but not immoral in our reputation */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (DisplayName = "Is Flagged?") )
		bool bIsFlagged = false;

		/** Are we currently in combat mode */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats", META = (DisplayName = "Is In Combat?"))
		bool bIsInCombat = false;

		/** A value indicating whether we can be inspected */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats")
		bool bCanBeInspected = false;
};