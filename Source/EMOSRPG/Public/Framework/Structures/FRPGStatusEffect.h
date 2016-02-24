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

#include <Engine.h>
#include <Structures/FRPGItemIcon.h>

#include "FRPGStatusEffect.generated.h"

USTRUCT(BlueprintType, META = (DisplayName = "RPG Status Effect") )
struct EMOSRPG_API FPRPGStatusEffect
{
	GENERATED_USTRUCT_BODY()

	public:
		/** A value indicating the length in seconds this effect lasts */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float Duration;

		/** A value which represents this object out of many */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FString Name;

		/** A value describing this object in further detail */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FString Description;

		/** An icon object which can be used on the UI to display this effect */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FRPGItemIcon Visual;
};