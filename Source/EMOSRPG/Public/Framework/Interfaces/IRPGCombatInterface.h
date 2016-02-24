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

#include <Framework/Structures/FRPGCharacterStats.h>
#include <Framework/Structures/FRPGCombatStats.h>
#include <Framework/Components/URPGCombatComponent.h>

#include "IRPGCombatInterface.generated.h"



UINTERFACE(BlueprintType, META = (DisplayName = "RPG Combat Interface") )
class URPGCombatInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class IRPGCombatInterface
{
	GENERATED_IINTERFACE_BODY()

	public:
		/**
			Returns the RPG Chracter Stats of the RPG Combat Component Implemented by this object
			@param result A structure representing the character stats of the RPG Combat Component
		*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface Implementations")
		void GetCharacterStats(FRPGCharacterStats& result);

		/**
			Returns the RPG Combat Stats of the RPG Combat Component Implemented by this object
			@param result A structure representing the combat stats of the RPG Combat Component
		*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface Implementations")
		void GetCombatStats(FRPGCombatStats& result);

		/** 
			Returns the RPG Combat Stats of the Opponent targeted by the implementer of this object
			@param index The index of the opponent who's character stats to retrieve
			@param result The results of the opponents stats
		*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface Implementations")
		void GetTargetStatsAtIndex(const int32 index, FRPGCharacterStats& result);

		/** 
			Returns the RPG Combat Component Implemented by this object
			@return Result
		*/
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface Implementations")
		URPGCombatComponent* GetCombatComponent();
};


