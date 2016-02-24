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
#include <Framework/Structures/FRPGPlayerStats.h>

#include "URPGPlayerProgressionData.generated.h"

UCLASS(Blueprintable, META = (DisplayName = "RPG Player Progression Data"))
class EMOSRPG_API URPGPlayerProgressionData : public UDataAsset
{
	GENERATED_BODY()

	public:
		/** 
			Defines a collection of progression steps. Each Item represents the data for specific levels. Every Player Starts at level 1,
			and therefore index 0 corresponds to level 1. If a players level is higher than the amount of Items within the progression table,
			the combat system will take the last index within the collection and apply those as base stats for the character.
		*/
		UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Properties")
		TArray< struct FRPGPlayerStats > ProgressionTable;
};